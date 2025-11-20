#include "usbhidhandler.h"
#include "hid_structs.h"

#include <thread>
#include <chrono>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#if defined(__linux__) || defined(linux)
#include <hidapi/hidapi.h>
#include <endian.h>
#endif

#include <cstddef>

#include <locale>
#include <cwchar>
#include <vector>

#define USB_VID 0x0000
#define USB_PID 0x0002

static std::string wstr_to_utf8(const wchar_t *wstr) {
    if (!wstr) return std::string();
    std::size_t len = std::wcslen(wstr);
    if (len == 0) return std::string();
    std::vector<char> buf((len + 1) * 4);
    std::size_t out = std::wcstombs(buf.data(), wstr, buf.size());
    if (out == static_cast<std::size_t>(-1)) {
        return std::string();
    }
    return std::string(buf.data());
}

USBHIDHandler::USBHIDHandler()
: run_(false), h_(nullptr)
{
    int res = hid_init();
    if (res == -1) {
        printf("hid_init failed\n");
        throw std::string("failed to init hid library");
    }
    
    printf("initially opening hidraw device\n");
    openDevice();
}

USBHIDHandler::~USBHIDHandler()
{
    terminate();
    if (worker_.joinable()) worker_.join();
    if (h_ != NULL) {hid_close((hid_device*)h_); h_ = NULL;}
}

void USBHIDHandler::start()
{
    run_ = true;
    worker_ = std::thread(&USBHIDHandler::run, this);
}

void USBHIDHandler::terminate()
{
    run_ = false;
}

bool USBHIDHandler::setDialPositions( unsigned mux_setting, unsigned dial_nr,char mode, unsigned nr_positions, float zero_offset, float mag_pressed_threshold)
{
    hid_device *h = (hid_device *)h_;

    if (h == NULL) return false;

    printf("configuration dial position for dial %i with %i steps and offset %f\n", dial_nr, nr_positions, zero_offset);
    uint16_t zo = zero_offset / 360.0 * HID_INPUT_NR_RAW_VALUE;

    mode = 0;
    struct hid_feature_1_report fr;
    fr.id = HID_FEATURE_ID_1;
    fr.mux_setting = mux_setting;
    fr.dial_id = dial_nr;
    fr.mode = mode;
    fr.nr_dial_pos = nr_positions;
    fr.raw_zero_offset = htobe16(zo);
    fr.mag_pressed_threshold = htobe16(mag_pressed_threshold);

    int r = hid_send_feature_report((hid_device*)h, (const unsigned char*)&fr, sizeof(fr));

    return (r == sizeof(fr));
}

void USBHIDHandler::run()
{
    while (true) {
        for (;;) {
            if (!run_ || !h_) break;

            uint8_t buffer[HID_USB_MAX_REPORT_SZ];
            int res = hid_read((hid_device*)h_, buffer, sizeof(buffer));

            if (res == -1) {
                perror("failed to read from device");
                break;
            } else if (res == 0) {
                continue;
            } else {
                switch (buffer[0]) {
                case HID_REPORT_ID_1: {
                    struct hid_input_report *hi = (struct hid_input_report *)buffer;
                    uint16_t rab = be16toh(hi->raw_and_button);
                    uint16_t raw = rab & HID_INPUT_RAW_MASK;
                    bool button_pressed = rab & HID_INPUT_BUTTON_MASK;
                    bool moved_pos = ((rab & HID_INPUT_DIRECTION_MASK) >> HID_INPUT_DIRECTION_SHIFT) & HID_INPUT_DIRECTION_POS;
                    bool moved_neg = ((rab & HID_INPUT_DIRECTION_MASK) >> HID_INPUT_DIRECTION_SHIFT) & HID_INPUT_DIRECTION_NEG;
                    int dial_nr = hi->dial_id;
                    uint8_t nr_pos = hi->nr_dial_pos;

                    if (onDialChanged) onDialChanged((unsigned)dial_nr, (unsigned)raw, (unsigned)nr_pos, button_pressed, moved_pos, moved_neg);
                    break;
                }
                default:
                    printf("unknown report id 0x%02x\n", buffer[0]);
                    break;
                }
            }
        }

        if (h_ != NULL) {hid_close((hid_device*)h_); h_ = NULL;}
        if (onStateChanged) onStateChanged(USBHIDHandlerState::STATE_DISCONNECT);

        if (!run_) break;
        printf("re-opening hidraw device\n");
        openDevice();

        if (!run_) break;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    printf("terminating usb-hid loop\n");
}

bool USBHIDHandler::openDevice()
{
    h_ = hid_open(HID_USB_VID, HID_USB_PID, NULL);

    if (h_ == NULL) {
        perror("could not open a device\n");
        if (onStateChanged) onStateChanged(USBHIDHandlerState::STATE_DISCONNECT);
        return false;
    } else {
        wchar_t serial[200];
        hid_get_serial_number_string((hid_device*)h_, serial, 200);
        serial_ = wstr_to_utf8(serial);
        printf("Successfully opened device with serial # %s\n", serial_.c_str());

        uint8_t fw_version[HID_FIRMWARE_STRING_SZ+1];
        fw_version[0] = HID_FEATURE_ID_3;
        int r = hid_get_feature_report((hid_device*)h_, fw_version, sizeof(fw_version));
        fw_version[25] = 0;

        if (r) {
            serial_ += "@";
            serial_ += reinterpret_cast<char*>(&fw_version[1]);
        }

        if (onStateChanged) onStateChanged(USBHIDHandlerState::STATE_CONNECTED);
        return true;
    }
}