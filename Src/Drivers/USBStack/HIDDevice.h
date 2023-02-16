/**
 * @file HIDDevice.h
 * @author Ian Ress
 * @brief USB descriptor declarations and macros for HID Keyboard devices. This is 
 * separated out from the standard descriptor declarations for cleaner organization.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* TODO: Major cleanup and work */
#ifndef HIDDEVICE_H
#define HIDDEVICE_H

#include <stdint.h>
#include "Attributes.h"

/* Short Items */
#define BTYPE_MAIN_ITEM                     ((0b00) << 2)   //0b00xx
#define BTAG_MAIN_INPUT                     ((0b1000) << 4) //0b1000xxxx
#define BTAG_MAIN_OUTPUT                    ((0b1001) << 4) //0b1001xxxx
#define BTAG_MAIN_FEATURE                   ((0b1011) << 4) //0b1011xxxx
#define BTAG_MAIN_COLLECTION                ((0b1010) << 4) //0b1010xxxx
#define BTAG_MAIN_END_COLLECTION            ((0b1100) << 4) //0b1100xxxx

#define BTYPE_GLOBAL_ITEM                   ((0b01) << 2)   //0b01xx
#define BTAG_GLOBAL_USAGE_PAGE              ((0b0000) << 4) //0b0000xxxx            
#define BTAG_GLOBAL_LOGICAL_MIN             ((0b0001) << 4) //0b0001xxxx
#define BTAG_GLOBAL_LOGICAL_MAX             ((0b0010) << 4) //0b0010xxxx
#define BTAG_GLOBAL_PHYSICAL_MIN            ((0b0011) << 4) //0b0011xxxx
#define BTAG_GLOBAL_PHYSICAL_MAX            ((0b0100) << 4) //0b0100xxxx
#define BTAG_GLOBAL_UNIT_EXPONENT           ((0b0101) << 4) //0b0101xxxx
#define BTAG_GLOBAL_UNIT                    ((0b0110) << 4) //0b0110xxxx
#define BTAG_GLOBAL_REPORT_SIZE             ((0b0111) << 4) //0b0111xxxx
#define BTAG_GLOBAL_REPORT_ID               ((0b1000) << 4) //0b1000xxxx
#define BTAG_GLOBAL_REPORT_COUNT            ((0b1001) << 4) //0b1001xxxx

#define BTYPE_LOCAL_ITEM                    ((0b10) << 2)    //0b10xx



typedef struct
{
    uint8_t     bLength;                /*  Size of the descriptor in bytes. */

    uint8_t     bDescriptorHIDType;     /*  Type of HID Descriptor */

    uint16_t    bcdHID;                 /*  HID Class Version Release to follow.
                                            The value is in the form 0xJJMN where JJ is the major version number, M is the 
                                            minor verion number, and N is the subminor version number. For example, HID 1.1 is 0x0110 */

    uint8_t     bCountryCode;           /*  Target Country. U.S. = 0x21. */

    uint8_t     bNumDescriptors;        /*  Number of HID Class Descriptors to follow (e.g. Report Descriptors) */

    uint8_t     bDescriptorClassType;   /*  Type of Class Descriptor to first follow (Report Descriptor in this case) */

    uint16_t    wDescriptorLength;      /*  Total length of the Class Descriptor specified in bDescriptorClassType */

    /*  If there's any additional Class Descriptors, set bNumDescriptors accordingly and add the additional
        Class Descriptors in this format: */

    // uint8_t bDescriptorTypeOptional;
    // uint16_t wDescriptorLengthOptional;

    /* Add additional class descriptors below*/
} GCCATTRIBUTE_PACKED HID_Descriptor_t;

// extern uint8_t Keyboard_ReportDescriptor[37];
// extern uint8_t Keyboard_Boot_ReportDescriptor[]; /* TODO: */



// typedef struct
// {
//     uint8_t Modifier; /**< Keyboard modifier byte, indicating pressed modifier keys (a combination of
//                         *   \c HID_KEYBOARD_MODIFER_* masks).
//                         */
//     uint8_t Reserved; /**< Reserved for OEM use, always set to 0. */
//     uint8_t KeyCode[6]; /**< Key codes of the currently pressed keys. */
// } ATTR_PACKED USB_KeyboardReport_Data_t;



#endif /* HIDDEVICE_H */