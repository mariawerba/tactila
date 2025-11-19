#include <iostream>
#include <vector>
#include <memory>
#include <csignal>
#include <atomic>
#include <thread>
#include <chrono>

#include "halldial.h"
#include "usbhidhandler.h"

#define MAX_DIALS 16

static std::atomic<bool> stopRequested(false);

static void sigintHandler(int)
{
    stopRequested = true;
}

int main(int argc, char *argv[])
{
    (void)argc; (void)argv;

    std::signal(SIGINT, sigintHandler);

    // construct handlers (they will open devices in ctor)
    USBHIDHandler hidHandler(false);
    USBHIDHandler hidHandlert(true);

    // create dials and set identity (two boards share identities 0..7)
    std::vector<HallDial> dials(MAX_DIALS);
    for (int i = 0; i < MAX_DIALS; ++i) {
        dials[i].setDialIdentity(i % 8);
    }

    // connect dial callbacks to print to stdout
    for (int i = 0; i < MAX_DIALS; ++i) {
        dials[i].onPositionChanged = [i](int pos){ std::cout << "Dial " << i << " position: " << pos << std::endl; };
        dials[i].onPositionIncremented = [i](int inc){ std::cout << "Dial " << i << " incremented by " << inc << std::endl; };
        dials[i].onPositionDecremented = [i](int dec){ std::cout << "Dial " << i << " decremented by " << dec << std::endl; };
        dials[i].onButtonPressed = [i](){ std::cout << "Dial " << i << " button pressed" << std::endl; };
        dials[i].onButtonReleased = [i](){ std::cout << "Dial " << i << " button released" << std::endl; };
    }

    // set HID handler callbacks to forward events to the corresponding HallDial
    hidHandler.onDialChanged = [&dials](unsigned dial_nr, unsigned val, unsigned nr_pos, bool button_pressed, bool moved_pos, bool moved_neg){
        if (dial_nr < 8) {
            dials[dial_nr].dialChanged(dial_nr, val, nr_pos, button_pressed);
        }
    };
    hidHandlert.onDialChanged = [&dials](unsigned dial_nr, unsigned val, unsigned nr_pos, bool button_pressed, bool moved_pos, bool moved_neg){
        if (dial_nr < 8) {
            dials[dial_nr + 8].dialChanged(dial_nr, val, nr_pos, button_pressed);
        }
    };

    // start background threads
    hidHandler.start();
    hidHandlert.start();

    // device-specific preset positions (use first handler serial)
    const std::string &serial = hidHandler.getSerial();
    if (serial == "4730501500500035") {
        std::cout << "device SERIAL 4730501500500035 is 27 Vertical" << std::endl;
        hidHandler.setDialPositions(0, 0, 'n', 24, 118, 12941);
        hidHandler.setDialPositions(1, 1, 'n', 24, 21, 12941);
        hidHandler.setDialPositions(2, 2, 'n', 24, 66, 12941);
        hidHandler.setDialPositions(3, 3, 'n', 24, 3, 12941);
        hidHandler.setDialPositions(4, 4, 'n', 24, 96, 12941);
        hidHandler.setDialPositions(5, 5, 'n', 24, 53, 12941);
        hidHandler.setDialPositions(6, 6, 'n', 24, 168, 12941);
        hidHandler.setDialPositions(7, 7, 'n', 24, 137, 12941);
        hidHandler.setDialPositions(8, 8, 'n', 24, 45, 12941);
        hidHandler.setDialPositions(9, 9, 'n', 24, 57, 12941);
        hidHandler.setDialPositions(10, 10, 'n', 24, 44, 12941);
        hidHandler.setDialPositions(11, 11, 'n', 24, 10, 12941);
        hidHandler.setDialPositions(12, 12, 'n', 24, 54, 12941);
        hidHandler.setDialPositions(13, 13, 'n', 24, 10, 12941);
        hidHandler.setDialPositions(14, 14, 'n', 24, 128, 12941);
        hidHandler.setDialPositions(15, 15, 'n', 24, 144, 12941);
    }
    else if(serial == "303150040043004A") {
        std::cout << "device SERIAL 303150040043004A is 27 Horizontal" << std::endl;
        hidHandler.setDialPositions(0, 0, 'n', 24, 42, 12941);
        hidHandler.setDialPositions(1, 1, 'n', 24, 151, 12941);
        hidHandler.setDialPositions(2, 2, 'n', 24, 13, 12941);
        hidHandler.setDialPositions(3, 3, 'n', 24, 164, 12941);
        hidHandler.setDialPositions(4, 4, 'n', 24, 133, 12941);
        hidHandler.setDialPositions(5, 5, 'n', 24, 56, 12941);
        hidHandler.setDialPositions(6, 6, 'n', 24, 43, 12941);
        hidHandler.setDialPositions(7, 7, 'n', 24, 99, 12941);
        hidHandler.setDialPositions(8, 8, 'n', 24, 41, 12941);
        hidHandler.setDialPositions(9, 9, 'n', 24, 9, 12941);
        hidHandler.setDialPositions(10, 10, 'n', 24, 76, 12941);
        hidHandler.setDialPositions(11, 11, 'n', 24, 72, 12941);
        hidHandler.setDialPositions(12, 12, 'n', 1, 4095, 12941);
        hidHandler.setDialPositions(13, 13, 'n', 1, 4095, 12941);
        hidHandler.setDialPositions(14, 14, 'n', 24, 117, 12941);
        hidHandler.setDialPositions(15, 15, 'n', 1, 4095, 12941);
    }
    else if (serial == "30315004003C004B") {
        std::cout << "device SERIAL 430315004003C004B is 15.6" << std::endl;
        hidHandler.setDialPositions(0, 0, 'n', 24, 128, 12941);
        hidHandler.setDialPositions(1, 1, 'n', 24, 105, 12964);
        hidHandler.setDialPositions(2, 2, 'n', 24, 160, 12929);
        hidHandler.setDialPositions(3, 3, 'n', 24, 82, 12966);
    }
    else {
        std::cout << "device SERIAL " << serial << " not known, all dials off!" << std::endl;
    }

    // main wait loop until SIGINT
    while (!stopRequested) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::cout << "shutting down..." << std::endl;
    hidHandler.terminate();
    hidHandlert.terminate();
    // give threads time to exit
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    return 0;
}
