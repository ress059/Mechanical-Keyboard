/**
 * @file USBStdDescriptors.h
 * @author Ian Ress
 * @brief Standard descriptor headers defined by the USB spec.
 * @date 2023-02-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef USBSTDDESCRIPTORS_H
#define USBSTDDESCRIPTORS_H

#include <stdint.h>
#include "Attributes.h"

typedef struct
{
    uint8_t bLength;                            /*  Size of descriptor in bytes. Set to 18 since device descriptor is 18 bytes long. */
    uint8_t bDescriptionType;                   /*  Descriptor type. Set to 0x01 since this is a Device Descriptor. */

    uint16_t bcdUSB;                            /*  USB Specification Number.
                                                    bcdUSB is the highest version of USB the device supports. The value is in the form 0xJJMN 
                                                    where JJ is the major version number, M is the minor verion number, and N is the 
                                                    subminor version number. For example, USB 2.0 is 0x0200 and USB 1.1 is 0x0110 */
                                
    uint8_t  bDeviceClass;                      /*  USB device class. */
    uint8_t  bDeviceSubClass;                   /*  USB device subclass (Assigned by USB org) */
    uint8_t  bDeviceProtocol;                   /*  Protocol Code (Assigned by USB org) */
                                                /*  bDeviceClass, bDeviceSubclass, and bDeviceProtocol are used by the operating system to 
                                                    find a class driver for the device. Typically only the bDeviceClass is set at the device 
                                                    level. Most class specifications choose to identify itself at the interface level and as 
                                                    a result set the bDeviceClass as 0x00. This allows for the one device to support 
                                                    multiple classes. */

    uint8_t  bMaxPacketSize0;                   /*  Max data packet size in bytes for Endpoint0. Valid sizes = 8, 16, 32, 64 */

    uint16_t idVendor;                          /*  Vendor ID for the USB product (Assigned by USB org) */
    uint16_t idProduct;                         /*  Unique manufacturer product ID for keyboard */
                                                /*  idVendor and idProduct are used by the operating system to find a driver for the device. 
                                                    The Vendor ID is assigned by USB org. */

    uint16_t bcdDevice;                         /*  Device Release Number */
                                                /*  bcdDevice has the same form as bcdUSB (0xJJMN). This is assigned by the developer. */

    uint8_t  iManufacturer;                     /*  Index of Manufacturer String Descriptor */
    uint8_t  iProduct;                          /*  Index of Product String Descriptor */
    uint8_t  iSerialNumber;                     /*  Index of Serial Number String Descriptor */
                                                /*  iManufacturer, iProduct, and iSerialNumber exist to provide details of the 
                                                    manufacturer, product, and serial number. There is no requirement to have string 
                                                    descriptors. If no string descriptor is present, a index of zero should be used. */

    uint8_t  bNumConfigurations;                /*  Number of possible configurations */
} GCCATTRIBUTE_PACKED USB_Device_Descriptor_t;


typedef struct
{
    uint8_t bLength;                            /*  Size of descriptor in bytes. */
    uint8_t bDescriptionType;                   /*  Descriptor type. Set to 0x02 since this is a Configuration Descriptor. */

    uint16_t wTotalLength;                      /*  Total length in bytes of data returned */
                                                /*  wTotalLength is the size of the entire configuration hierarchy. So the configuration 
                                                    descriptor, all interface descriptors, and all endpoint descriptors.*/

    uint8_t  bNumInterfaces;                    /*  Total number of interfaces in the configuration. */
    uint8_t  bConfigurationValue;               /*  Value to use to as an argument to select this configuration. (Index) */
    uint8_t  iConfiguration;                    /*  Index of a string descriptor describing the configuration. */

    uint8_t  bmAttributes;                      /*  Bitfield. */
                                                /*  Bit 7 = Reserved, set to 1 (USB 1.0 Bus Powered)
                                                    Bit 6 = Device is self powered if set to 1. (set to 0 for keyboard since it's bus powered)
                                                    Bit 5 = Remote wakeup if set to 1. (set to 0 for keyboard)
                                                    Bits 4 to 0 = Reserved, set to 0. */

    uint8_t  bMaxPower;                         /*  Max power consumption in 2mA units. For example, bMaxPower = 100 means 200mA max consumption. */
} GCCATTRIBUTE_PACKED USB_Configuration_Descriptor_t;


typedef struct
{
    uint8_t bLength;                            /*  Size of the descriptor in bytes. */
    uint8_t bDescriptorType;                    /*  Descriptor type. Set to 0x04 since this is an Interface Descriptor. */
    
    uint8_t bInterfaceNumber;                   /*  Value to use to as an argument to select this configuration. */
                                                /*  bInterfaceNumber indicates the index of the interface descriptor. This should be 
                                                    zero based, and incremented once for each new interface descriptor. */

    uint8_t bAlternateSetting;                  /*  Value used to select alternative setting. */
                                                /*  Alternate setting for the interface number. The same interface number can 
                                                    have multiple alternate settings with different endpoint configurations, 
                                                    which can be selected by the host. */

    uint8_t bNumEndpoints;                      /*  Total number of endpoints used for this interface. */
                                                /*  bNumEndpoints should exclude endpoint zero from the count. bNumEndpoints is used 
                                                    to indicate the number of endpoint descriptors to follow after endpoint zero. */

    uint8_t bInterfaceClass;                    /*  Interface class code. Assigned by USB org. */
    uint8_t bInterfaceSubClass;                 /*  Interface subclass code. Assigned by USB org. */
    uint8_t bInterfaceProtocol;                 /*  Interface protocol code. Assigned by USB org. */
                                                /*  bInterfaceClass, bInterfaceSubClass and bInterfaceProtocol can be used to specify 
                                                    supported classes (e.g. HID, communications, mass storage etc.) This allows many 
                                                    devices to use class drivers preventing the need to write specific drivers for your device.*/

    uint8_t iInterface;                         /*  Index of the string descriptor describing this interface. Allows for string descriptor of interface. */
} USB_Interface_Descriptor_t;


typedef struct
{
    uint8_t  bLength;                           /*  Size of the descriptor in bytes. */
    uint8_t  bDescriptorType;                   /*  Descriptor type. Set to 0x05 since this is an Endpoint Descriptor. */
    uint8_t  bEndpointAddress;                  /*  See bit description below: */
                                                /*  Bits 0 to 3 = Endpoint Number
                                                    Bits 4 to 6 = Reserved, set to 0.
                                                    Bit 7 = Endpoint Direction: 
                                                        0 = Endpoint OUT (receive data from host)
                                                        1 = Endpoint IN (send data to host) */

    uint8_t  bmAttributes;                      /*  Bitfield. */
                                                /*  Bits 0 to 1 = Transfer Type:
                                                        00 = Control
                                                        01 = Isochronous
                                                        10 = Bulk
                                                        11 = Interrupt

                                                    Bits 2 to 7 = Reserved unless Isochronous Transfer Type. Set to zero?

                                                    ONLY FOR ISOCHRONOUS TRANSFER TYPE
                                                    Bits 2 to 3 =  Synchronisation Type:
                                                        00 = No Synchronisation
                                                        01 = Adaptive
                                                        10 = Asynchronous
                                                        11 = Synchronous

                                                    ONLY FOR ISOCHRONOUS TRANSFER TYPE
                                                    Bits 4 to 5 = Usage Type:
                                                        00 = Data Endpoint
                                                        01 = Explicit Feedback Data Endpoint
                                                        10 = Feedback Endpoint
                                                        11 = Reserved */

    uint16_t wMaxPacketSize;                    /*  Max packet size in bytes this endpoint is capable of sending/receiving. */
                                                /*  wMaxPacketSize only applies to the actual data payload. */

    uint8_t  bInterval;                         /*  Interval for polling endpoint data transfers if it is an INTERRUPT or ISOCHRONOUS type. */
                                                /*  bInterval is ignored for Bulk or Control endpoints. This value is the number of frame counts! 
                                                    So bInterval = 5 means every 5 frames. bInterval must be set to 1 for Isochronous and can
                                                    range from 1 to 255 for Interrupt transfers. Since the value equates to frame counts,
                                                    this equates to either 1ms for low/full speed devices or 125us for high speed devices */
} GCCATTRIBUTE_PACKED USB_Endpoint_Descriptor_t;


typedef struct
{
    uint8_t  bLength;                           /*  Size of the descriptor in bytes. */
    uint8_t  bDescriptorType;                   /*  Descriptor type. Set to 0x03 since this is a String Descriptor. */
    uint16_t wLANGID;                           /*  Supported Language Code Zero. Set to 0x0409 for English. */
                                                /*  The keyboard only supports English so this should be the only entry.
                                                    If more languages are supported in the future, successive wLANDID members should be
                                                    added with the corresponding Language ID unicode value. */
} GCCATTRIBUTE_PACKED USB_String_Descriptor_Zero_t;


typedef struct
{
    uint8_t  bLength;                           /*  Size of the descriptor in bytes. */
    uint8_t  bDescriptorType;                   /*  Descriptor type. Set to 0x03 since this is a String Descriptor. */

    uint16_t bString[];                         /*  Unicode encoded string. */
                                                /*  If normal ASCII characters are to be used, they must be added as an array
                                                    of characters rather than a normal C string so that they are widened to Unicode size.
                                                    Under GCC, strings prefixed with the "L" character (before the opening string quotation mark) 
                                                    are considered to be Unicode strings, and may be used instead of an explicit array of ASCII 
                                                    characters. */
} GCCATTRIBUTE_PACKED USB_String_Descriptor_t;

#endif
