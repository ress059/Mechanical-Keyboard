/**
 * @file USBHIDDescriptors.h
 * @author Ian Ress
 * @brief HID descriptor headers defined by USB HID v1.11 spec.
 * @date 2023-02-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef USBHIDDESCRIPTORS_H
#define USBHIDDESCRIPTORS_H

#include <stdint.h>
#include "Attributes.h"

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

#endif