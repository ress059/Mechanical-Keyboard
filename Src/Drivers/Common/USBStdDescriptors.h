/**
 * @file USBStdDescriptors.h
 * @author Ian Ress
 * @brief Standard descriptor headers defined by the USB spec. Currently follows USB Spec v2.0
 * @date 2023-02-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef USBSTDDESCRIPTORS_H
#define USBSTDDESCRIPTORS_H

#include <stdint.h>
#include "Attributes.h"

enum /* bDescriptorType */
{
    DEVICE_DESCRIPTOR_TYPE = 0x01,
    CONFIGURATION_DESCRIPTOR_TYPE = 0x02,
    STRING_DESCRIPTOR_TYPE = 0x03,
    INTERFACE_DESCRIPTOR_TYPE = 0x04,
    ENDPOINT_DESCRIPTOR_TYPE = 0x05
};


/**
 * Standard Descriptors defined by the USB Spec. 
 * See USB 2.0 Spec - Chapter 9.6 "Standard USBDescriptor Definitions"
 */
typedef struct
{
    const uint8_t  bLength;
    const uint8_t  bDescriptionType;
    const uint16_t bcdUSB;        
    const uint8_t  bDeviceClass;
    const uint8_t  bDeviceSubClass;
    const uint8_t  bDeviceProtocol;
    const uint8_t  bMaxPacketSize0;
    const uint16_t idVendor;
    const uint16_t idProduct;
    const uint16_t bcdDevice;
    const uint8_t  iManufacturer;
    const uint8_t  iProduct;
    const uint8_t  iSerialNumber;
    const uint8_t  bNumConfigurations;
} GCC_ATTRIBUTE_PACKED USB_Std_Device_Descriptor_t;


typedef struct
{
    const uint8_t  bLength;
    const uint8_t  bDescriptionType;
    const uint16_t wTotalLength;
    const uint8_t  bNumInterfaces;
    const uint8_t  bConfigurationValue;
    const uint8_t  iConfiguration;
    const uint8_t  bmAttributes;
    const uint8_t  bMaxPower;
} GCC_ATTRIBUTE_PACKED USB_Std_Configuration_Descriptor_t;


typedef struct
{
    const uint8_t bLength;
    const uint8_t bDescriptorType;
    const uint8_t bInterfaceNumber;
    const uint8_t bAlternateSetting;
    const uint8_t bNumEndpoints;
    const uint8_t bInterfaceClass;
    const uint8_t bInterfaceSubClass;
    const uint8_t bInterfaceProtocol;
    const uint8_t iInterface;
} GCC_ATTRIBUTE_PACKED USB_Std_Interface_Descriptor_t;


typedef struct
{
    const uint8_t  bLength;
    const uint8_t  bDescriptorType;
    const uint8_t  bEndpointAddress;
    const uint8_t  bmAttributes;
    const uint16_t wMaxPacketSize;
    const uint8_t  bInterval;
} GCC_ATTRIBUTE_PACKED USB_Std_Endpoint_Descriptor_t;



/**
 * Non-standard Descriptors to offer flexibility. Allows user to assign
 * any Descriptor Configuration to their Device.
 */

/**
 * @brief Allows user to explicitly assign various Endpoints to each Interface
 * Descriptor. This configuration will be defined at compile-time and cannot
 * change at run-time. Meant for use in USB_Std_Descriptors_Collection
 * structure.
 * 
 */
typedef struct
{
    const uint8_t bLength;
    const uint8_t bDescriptorType;
    const uint8_t bInterfaceNumber;
    const uint8_t bAlternateSetting;
    const uint8_t bNumEndpoints;
    const uint8_t bInterfaceClass;
    const uint8_t bInterfaceSubClass;
    const uint8_t bInterfaceProtocol;
    const uint8_t iInterface;
    const USB_Std_Endpoint_Descriptor_t * (* const Endpoint_Descriptors)[];
} GCC_ATTRIBUTE_PACKED USB_Dynamic_Interface_Descriptor_t;


/**
 * @brief Allows user to explicitly assign various Interfaces to each
 * Configuration Descriptor. This configuration will be defined at compile-time 
 * and cannot change at run-time. Meant for use in USB_Std_Descriptors_Collection
 * structure.
 * 
 */
typedef struct
{
    const uint8_t  bLength;
    const uint8_t  bDescriptionType;
    const uint16_t wTotalLength;
    const uint8_t  bNumInterfaces;
    const uint8_t  bConfigurationValue;
    const uint8_t  iConfiguration;
    const uint8_t  bmAttributes;
    const uint8_t  bMaxPower;
    const USB_Dynamic_Interface_Descriptor_t * (* const Interface_Descriptors)[];
} GCC_ATTRIBUTE_PACKED USB_Dynamic_Configuration_Descriptor_t;


/**
 * @brief Use for maximum flexibility. Allows a device to be configured with any 
 * number of Configuration, Interface, and Endpoint Descriptor combinations. Only
 * one Device Descriptor is defined for each Device. Each Configuration Descriptor
 * stores an array of Interface Descriptors assigned to each Configuration.
 * Each Interface Descriptor stores an array of Endpoint Descriptors assigned to
 * each Interface.
 * 
 * @note This configuration has to be defined at compile-time and is not able to change
 * during run-time.
 * 
 */
typedef struct
{
    const USB_Std_Device_Descriptor_t * const Device_Descriptor;
    const USB_Dynamic_Configuration_Descriptor_t * (* const Configuration_Descriptors)[];
} USB_Std_Descriptors_Collection;


// typedef struct
// {
//     uint8_t  bLength;
//     uint8_t  bDescriptorType;
//     uint16_t wLANGID;
// } GCC_ATTRIBUTE_PACKED USB_Std_String_Descriptor_Zero_t;


// typedef struct
// {
//     uint8_t  bLength;
//     uint8_t  bDescriptorType;
//     uint16_t bString[];
// } GCC_ATTRIBUTE_PACKED USB_Std_String_Descriptor_t;

#endif
