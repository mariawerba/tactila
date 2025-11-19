/*
 * Eberwein Backend AS5600
 * Copyright (c) 2025 Embedded Solutions GmbH <office@embedded-solutions.at>
 * Authors: Roland Lezuo <roland.lezuo@embedded-solutions.at>
 * All rights reserved.
 */


/* ABOUT THIS FILE *********************************************************
 *
 * this file is part of the QTDemo application (not shipped in source)
 * and demonstrates usage and parsing of the HID events
 *
 * please carefully read the comments in this file to understand the HID events
 */

#include "usbhidhandler.h"
#include "hid_structs.h"

#include <qthread.h>
#include <cstring>

#if defined(linux)
#include <hidapi/hidapi.h>
#include <endian.h>
#else
// this is win64
#include <hidapi.h>
#include <winsock.h>
#define be16toh ntohs
#endif

#include <cstddef>
#include <QDebug>

/* this include contains a number of macro definitions and also some comments about the HID structs
 * not all HID reports defined in hid_structs.h are publicly documented
 */
#include <hid_structs.h>
#define USB_VID 0x0000
#define USB_PID 0x0002

USBHIDHandler::USBHIDHandler(QObject *parent, bool boardNo)
    : QObject{parent}, QRunnable()
{
    run_ = true;
    qRegisterMetaType<USBHIDHandler::USBHIDHandlerState>("USBHIDHandler::USBHIDHandlerState");

    int res = hid_init();

    if (res == -1) {
        printf("hid_init failed\n");
        throw std::string("failed to init hid library");
    }

    printf("initially opening hidraw device\n");

    wchar_t serialo[17]= L"4146500700320003";
    wchar_t serialot[17] = L"41465007003A0003";




    //serialNo.toWCharArray(serialto);

    //L before "" indicates the string to be in unicode


    //qDebug() << "serialNo:" << serialNo;
    //qDebug() << "serialo:" << serialo;
    //qDebug() << "serialto" << serialto;

    if(boardNo)
    h_ = hid_open(HID_USB_VID, HID_USB_PID, serialo);
    else
        h_ = hid_open(HID_USB_VID, HID_USB_PID, serialot);
    if (h_ != NULL)
    {
        wchar_t serial[200];
        hid_get_serial_number_string((hid_device *)h_, serial, 200);

        serial_ = QString::fromWCharArray(serial);
    }
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

    mode = 0;                       //Not implemented yet to force to be 0
    struct hid_feature_1_report fr;
    fr.id = HID_FEATURE_ID_1;
    fr.mux_setting = mux_setting;
    fr.dial_id = dial_nr;
    fr.mode = mode; //to_mode(dial_nr, mode); right now make 0
    fr.nr_dial_pos = nr_positions;
    fr.raw_zero_offset = htobe16(zo);
    //fr.raw_zero_offset = htobe16(0x4000 /*hyst-setting*/ | (zero_offset & HID_INPUT_RAW_MASK));
    fr.mag_pressed_threshold = htobe16(mag_pressed_threshold);

    int r = hid_send_feature_report(h, (const unsigned char*)&fr, sizeof(fr));

    return (r == sizeof(fr));
}

void USBHIDHandler::run()
{

    while (true) {        
        for (;;) {
            if (!run_ || !h_) break;

            /* retrieve next HID event */
            uint8_t buffer[HID_USB_MAX_REPORT_SZ];
            int res = hid_read((hid_device*)h_, buffer, sizeof(buffer));

            if (res == -1) {
                perror("failed to read from device\n");
                break;
            } else {
                switch (buffer[0]) {
                    /* this is the primary report, containing position of the dials and information on button press events and
                   and directionial information */
                case HID_REPORT_ID_1:
                {
                    struct hid_input_report *hi = (struct hid_input_report *)buffer;
                    uint16_t rab = be16toh(hi->raw_and_button);

                    /* raw holds positional information of dial */
                    uint16_t raw = rab & HID_INPUT_RAW_MASK;
                    /* this bit is true if the button is pressed, false otherwise */
                    bool button_pressed = rab & HID_INPUT_BUTTON_MASK;
                    /* this bit is true if the dial's raw value has changed and increased its value (handles wrap-arount at when change from max -> 0) */
                    bool moved_pos = ((rab & HID_INPUT_DIRECTION_MASK) >> HID_INPUT_DIRECTION_SHIFT) & HID_INPUT_DIRECTION_POS;
                    /* this bit is true if the dial's raw value has changed and decreased its value (handles wrap-arount at when change from 0 -> max) */
                    bool moved_neg = ((rab & HID_INPUT_DIRECTION_MASK) >> HID_INPUT_DIRECTION_SHIFT) & HID_INPUT_DIRECTION_NEG;
                    /* dial_id is the user-visible number for the button */
                    int dial_nr = hi->dial_id;
                    /* nr_pos contains the number of position the dial will "click into", actual value reported are 0 <= x < nr_dial_pos */
                    uint8_t nr_pos = hi->nr_dial_pos;

                    printf("got change report for dial %i to position %i\n", dial_nr, raw);
                    float val;

                    if (nr_pos == 0) {
                        val = 360.0 * ((float)raw / HID_INPUT_NR_RAW_VALUE);
                    } else {
                        val = raw;
                    }
                    emit dialChanged(dial_nr, val, nr_pos,
                                     button_pressed, moved_pos, moved_neg);
                    break;
                }
                default:
                    printf("unknown report id 0x%02x\n", buffer[0]);
                    break;
                }
            }

        }
        // try to re-open device
        if (h_ != NULL) hid_close((hid_device*)h_);
        emit stateChanged(USBHIDHandlerState::STATE_DISCONNECT);

        printf("opening hidraw device\n");
        /* connect to the device using the given vendor and product IDs */
        h_ = hid_open(HID_USB_VID, HID_USB_PID, NULL);

        if (h_ == NULL) {
            perror("could not open a device");
            emit stateChanged(USBHIDHandlerState::STATE_DISCONNECT);
        } else {
            wchar_t serial[200];

            /* retrieve serial number from HID descriptor, this is provided by usbhid library and needed */
            hid_get_serial_number_string((hid_device*)h_, serial, 200);
            serial_ = QString::fromWCharArray(serial);

            /* retrieve device's firmware version string, leave place for \0 */
            uint8_t fw_version[HID_FIRMWARE_STRING_SZ+1];

            fw_version[0] = HID_FEATURE_ID_3;
            int r = hid_get_feature_report((hid_device*)h_, fw_version, sizeof(fw_version));
            fw_version[25] = 0;

            if (r) {
                serial_ += QString("@%1").arg((const char*)(&fw_version[1]));
            }

            emit stateChanged(USBHIDHandlerState::STATE_CONNECTED);
        }

        if (!run_) break;
        QThread::sleep(1);
    }

    printf("terminating usb-hid loop\n");
}
