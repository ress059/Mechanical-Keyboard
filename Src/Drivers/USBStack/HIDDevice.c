/**
 * @file HIDDevice.c
 * @author Ian Ress
 * @brief TODO: Description
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* TODO: Major cleanup and work */
#include "Endian.h"
#include "HIDDevice.h"

/* TODO: Each element should be in Little Endian. E.g. Usage Page is 16-bits so 
LE16_RUNTIME(0x0501). */
const uint8_t Keyboard_ReportDescriptor[37] = 
{
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xA1, 0x01,                    // COLLECTION (Application)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0xE0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xE7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x15, 0x01,                    //   LOGICAL_MINIMUM (1)
    0x25, 0x63,                    //   LOGICAL_MAXIMUM (99)
    0x19, 0x01,                    //   USAGE_MINIMUM (Keyboard ErrorRollOver)
    0x29, 0x63,                    //   USAGE_MAXIMUM (Keypad . and Delete)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xC0                           // END_COLLECTION
};


const HID_Descriptor_t Keyboard_HID_Descriptor = 
{
    .bLength                = sizeof(HID_Descriptor_t),

    .bDescriptorHIDType     = 0x21, 

    .bcdHID                 = LE16_TO_OS_COMPILETIME(0x0110),                               /* As of 1/8/2023 most recent HID Spec is v1.1 */

    .bCountryCode           = 0x21,                                                         /* 0x21 = US. See Section 6.2.1 pg. 23 of USB HID spec v1.1 for full list of codes. */

    .bNumDescriptors        = 0x01,                                                         /* Currently only using one HID Class-specific descriptor for this HID Device (the Report Descriptor) */
    
    .bDescriptorClassType   = 0x22,                                                         /* Report Descriptor will follow. */

    .wDescriptorLength      = LE16_TO_OS_COMPILETIME(sizeof(Keyboard_ReportDescriptor))     /* Size in bytes of the report descriptor. */
};



/* TODO: */
const uint8_t Keyboard_Boot_ReportDescriptor[] =
{

};