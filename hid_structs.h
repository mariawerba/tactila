/*
 * Eberwein Backend AS5600
 * Copyright (c) 2024 Embedded Solutions GmbH <office@embedded-solutions.at>
 * Authors: Roland Lezuo <roland.lezuo@embedded-solutions.at>
 * All rights reserved.
 */
#ifndef APPLICATION_INCLUDE_HID_STRUCTS_H_
#define APPLICATION_INCLUDE_HID_STRUCTS_H_

#include <stdint.h>

/* vendor and product ID, reported via I2C and USB */
#define HID_USB_VID (0x0000)
#define HID_USB_PID (0x0002)

/* maximum number of dials supported by the backend */
#define HID_MAX_DIAL_NR (16)

/* maximum size of HID reports */
#define HID_USB_MAX_REPORT_SZ (64)

/*****************************************************************************/
/*************************************************************** REPORT 0x42 */
/*****************************************************************************/

// standard report issues by the device, will be delivered in a fixed interval
// and whenever an event took place
// each (enabled) dial will created an own report
#define HID_REPORT_ID_1 (0x42)

// the first 4 bits are not used by the value itself
#define HID_INPUT_RAW_MASK (0x0FFF)

// the number of raw values
#define HID_INPUT_NR_RAW_VALUE (4096)

// buttons pressed or not
#define HID_INPUT_BUTTON_MASK (0x8000)

// direction since last update
// pos: dial has been moved in positive direction, neg otherweise
// none will be reported of the dial was never moved other values are forbidden
#define HID_INPUT_DIRECTION_MASK (0x6000)
#define HID_INPUT_DIRECTION_SHIFT (13)
#define HID_INPUT_DIRECTION_NONE (0x0)
#define HID_INPUT_DIRECTION_POS (0x1)
#define HID_INPUT_DIRECTION_NEG (0x2)
#define HID_INPUT_DIRECTION_RESERVED (0x3)

// the data struct making up the report
struct __attribute__((__packed__)) hid_input_report {
  // HID_REPORT_ID_1
  uint8_t id;

  // either raw value (nr_dial_pos == 0) or position (0 .. nr_dial_pos-1), mask
  // with HID_INPUT_RAW_MASK
  uint16_t raw_and_button;

  // which dial the report belong to
  uint8_t dial_id;

  // configured number of positions for this dial
  uint8_t nr_dial_pos;
};
/*****************************************************************************/
/*********************************************************** SET REPORT 0xAA */
/*****************************************************************************/

#define HID_FEATURE_ID_1 (0xAA)

struct __attribute__((__packed__)) hid_feature_1_report {
  // HID_FEATURE_ID_1
  uint8_t id;

  // which mux setting selects this dial
  uint8_t mux_setting;

  // it's dial number
  uint8_t dial_id;

  // dial mode
  uint8_t mode;

  // it's number of positions, 0 ... report RAW values, 1 ... turns off
  // reporting
  uint8_t nr_dial_pos;

  // which raw value corresponds to buttons absolute zero position, mask with
  // HID_INPUT_RAW_AND_BUTTON_MASK, contains HID_DIALPOS_HYST_MASK field
  uint16_t raw_zero_offset;

  // for dial with integrated buttons, the threshold when the button is pressed
  // mask with MAG_PRESSED_THRESHOLD_TH_MASK, contains MAG_PRESSED_THRESHOLD_HYST_MASK field
  uint16_t mag_pressed_threshold;
};


/*****************************************************************************/
/*********************************************************** SET REPORT 0xAB */
/*****************************************************************************/

// this report is used for device management like entering bootloader
// and configuring device's I2C address
#define HID_FEATURE_ID_2 (0xAB)

// the feature report to configure a dial
#define HID_DUMMY_REBOOT_DFU (1)
#define HID_DUMMY_I2C_ADDR_RANGE_START (0x42)
#define HID_DUMMY_I2C_ADDR_RANGE_END (0x4F)

// the feature report save config to EEPROM
struct __attribute__((__packed__)) hid_feature_2_report {
  // HID_FEATURE_ID_2
  uint8_t id;

  uint8_t dummy;
};

/*****************************************************************************/
/*********************************************************** GET REPORT 0xAC */
/*****************************************************************************/

// ID to query version info
#define HID_FEATURE_ID_3 (0xAC)

// max size of firmware version string, 200 bits according to HID descriptor
#define HID_FIRMWARE_STRING_SZ (200/8)

#endif
