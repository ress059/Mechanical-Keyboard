/**
 * @file USBDescriptors.c
 * @author Ian Ress
 * @brief Defines the USB descriptors for the keyboard.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* TODO: Major cleanup and work */
#include "Endian.h"
#include "USBDescriptors.h"
#include "USBConfig.h"

/* TODO: 
0) Define Boot Report Descriptor for Keyboard. Fill out Keyboard_Boot_ReportDescriptor[] in usb_HID.c using
descriptor defined in Appendix B of USB HID Spec v1.1. Add to interface / endpoint descriptors accordingly.

1) bMaxPacketSize0 in Device Descriptor is currently set to 8 bytes. This could be increased if
we are using a Full or High Speed USB device. 

2) bMaxPacketSize in Endpoint Descriptor is currently set to 8 bytes. This could be increased
..make portable way to do this.

3) Create iProduct string descriptor 

4) Create portable way to calculate wTotalLength field in Configuration Descriptor.
This value is the size of the Configuration Descriptor, and all Interface and Endpoint Descriptors
under it. The size of the Interface descriptors depends on the number of Interfaces used for the
Configuration. The size of the Endpoint Descriptors depends both on the number of Endpoints used
for all the Interfaces, bMaxPacketSize0 specified in the Device Descriptor, AND the HID descriptors

ORDER OF DESCRIPTORS when replying to GET_DESCRIPTOR(CONFIGURATION) request 
    1) Configuration Descriptor
    2) Interface Descriptor (specifying HID Class)
    3) HID Descriptor
    4) Endpoint Descriptor (HID Interrupt IN Endpoint) */

const USB_Device_Descriptor_t Keyboard_Device_Descriptor =
{
    .bLength                        = sizeof(USB_Device_Descriptor_t),

    .bDescriptionType               = DEVICE_DESCRIPTOR_TYPE,

    .bcdUSB                         = LE16_TO_OS_COMPILETIME(USB_VERSION),  

    .bDeviceClass                   = 0x00,                                 /*  Setting to 0 means each Interface Descriptor will specify its own class. 
                                                                                In this case HID class is specified in the Interface Descriptor. */

    .bDeviceSubClass                = 0x00,                                 /*  Set to 0 because bDeviceClass is 0. */

    .bDeviceProtocol                = 0x00,                                 /*  We don't use class-specific protocols on the Device Level since 
                                                                                we specify HID class in the Interface Descriptor. */

    .bMaxPacketSize0                = CONTROL_ENDPOINT_SIZE,                /*  Make sure Endpoint0 registers of microcontroller are programmed so max size is 
                                                                                set to this value. */

    .idVendor                       = LE16_TO_OS_COMPILETIME(0xFF00),       /*  Use 0xFF00 to 0xFFFF for development */

    .idProduct                      = LE16_TO_OS_COMPILETIME(0x6969),

    .bcdDevice                      = LE16_TO_OS_COMPILETIME(0x0100),       /*  Release Version 1.0 */

    .iManufacturer                  = 0,                                    /*  No Manufacturer String Descriptor used */

    .iProduct                       = 1,                                    /*  Product String Descriptor Index (Ian Ress's Keyboard) */

    .iSerialNumber                  = 0,                                    /*  No Serial Number String Descriptor used */

    .bNumConfigurations             = 1
};


const USB_Configuration_Descriptor_t Keyboard_Configuration_Descriptor = 
{
    .bLength                        = sizeof(USB_Configuration_Descriptor_t),

    .bDescriptionType               = CONFIGURATION_DESCRIPTOR_TYPE,

    .wTotalLength                   = LE16_TO_OS_COMPILETIME(sizeof(USB_Configuration_Descriptor_t) +   // Total size in bytes of this Configuration Descriptor,
                                        (NUMBER_OF_INTERFACES * sizeof(USB_Interface_Descriptor_t)) +   // and all Interface and Endpoint descriptors under it (including Endpoint 0 max buffer size).
                                        (NUMBER_OF_ENDPOINTS * sizeof(USB_Endpoint_Descriptor_t))
                                        + ENDPOINT0_MAX_BUFFER_SIZE), 

    .bNumInterfaces                 = NUMBER_OF_INTERFACES,

    .bConfigurationValue            = 1,                                                                /* First index = 1. */

    .iConfiguration                 = 0,                                                                /* No String Descriptor used to describe this configuration. */               

    .bmAttributes                   = CONFIGURATION_RESERVED | CONFIGURATION_REMOTE_WAKEUP,             /* Must always be set to at least CONFIGURATION_RESERVED. Also allow device to wakeup host from sleep. */

    .bMaxPower                      = CONFIG_MAX_CURRENT_MA(USB_DEVICE_MAX_CURRENT) 
};


const USB_Interface_Descriptor_t Keyboard_Interface_Descriptor = 
{
    .bLength                        = sizeof(USB_Interface_Descriptor_t),

    .bDescriptorType                = INTERFACE_DESCRIPTOR_TYPE,

    .bInterfaceNumber               = 0,                                        /*  Zero-indexed. */

    .bAlternateSetting              = 0,                                        /*  Zero-indexed. */

    .bNumEndpoints                  = 1,                                        /*  Does not include Endpoint Zero*/

    .bInterfaceClass                = 0x03,                                     /*  HID Class */

    /* TODO: Add support for Boot Device. Set bInterfaceSubClass and bInterface protocol equal to 0x01.
        Then have two interface descriptors: one for Boot and one for normal operation. Do this after
        you get keyboard main functionality working. */
    .bInterfaceSubClass             = 0x00,                                     /*  Boot Device. Allow keyboard to be used in UEFI/BIOS. Need two Report Descriptors:
                                                                                    A Boot Report Descriptor (see Appendix B of USB HID spec v1.1) and a normal 
                                                                                    Report Descriptor. */

    .bInterfaceProtocol             = 0x00,                                     /*  Only set if device supports UEFI/BIOS. 0x01 = Keyboard. See Section 4.3 USB HID spec v1.1. */

    .iInterface                     = 0                                         /*  No Interface String Descriptor used */
};

const USB_Endpoint_Descriptor_t Keyboard_Endpoint_Descriptor = 
{
    .bLength                        = sizeof(USB_Endpoint_Descriptor_t),

    .bDescriptorType                = ENDPOINT_DESCRIPTOR_TYPE,

    .bEndpointAddress               = 0b10000001,                               /*  Endpoint #1, Endpoint IN (send data to host) */

    .bmAttributes                   = ENDPOINT_INTERRUPT_TRANSFER_TYPE,

    .wMaxPacketSize                 = LE16_TO_OS_COMPILETIME(0x08),

    .bInterval                      = ENDPOINT_INTERRUPT_INTERVAL
};
