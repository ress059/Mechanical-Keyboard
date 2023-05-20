/**
 * @file usb_std_descriptors.h
 * @author Ian Ress
 * @brief Standard descriptor headers defined by the USB spec. Currently follows USB Spec v2.0
 * @date 2023-02-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef USBSTDDESCRIPTORS_H
#define USBSTDDESCRIPTORS_H

#include <stdbool.h>
#include <stdint.h>
#include "attributes.h"

/**
 * @brief Use to set bMaxPower of the Configuration Descriptor.
 * 
 * @param mA Maximum current draw of the USB Device in mA.
 * 
 */
#define SET_MAX_CURRENT(mA)                     ((mA) >> 1)


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

/**
 * @warning Meant for GCC. Do NOT declare/use multi-byte pointers to 
 * any members of this struct to prevent unaligned memory access. Only 
 * access multi-byte members directly as GCC guarantees that misalignment
 * via direct member access will automatically be handled by the compiler.
 * 
 */
typedef struct
{
    const uint8_t  bLength;
    const uint8_t  bDescriptorType;
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


/**
 * @warning Meant for GCC. Do NOT declare/use multi-byte pointers to 
 * any members of this struct to prevent unaligned memory access. Only 
 * access multi-byte members directly as GCC guarantees that misalignment
 * via direct member access will automatically be handled by the compiler.
 * 
 */
typedef struct
{
    const uint8_t  bLength;
    const uint8_t  bDescriptorType;
    const uint16_t wTotalLength;
    const uint8_t  bNumInterfaces;
    const uint8_t  bConfigurationValue;
    const uint8_t  iConfiguration;
    const uint8_t  bmAttributes;
    const uint8_t  bMaxPower;
} GCC_ATTRIBUTE_PACKED USB_Std_Configuration_Descriptor_t;


/**
 * @warning Meant for GCC. Do NOT declare/use multi-byte pointers to 
 * any members of this struct to prevent unaligned memory access. Only 
 * access multi-byte members directly as GCC guarantees that misalignment
 * via direct member access will automatically be handled by the compiler.
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
} GCC_ATTRIBUTE_PACKED USB_Std_Interface_Descriptor_t;


/**
 * @warning Meant for GCC. Do NOT declare/use multi-byte pointers to 
 * any members of this struct to prevent unaligned memory access. Only 
 * access multi-byte members directly as GCC guarantees that misalignment
 * via direct member access will automatically be handled by the compiler.
 * 
 */
typedef struct
{
    const uint8_t  bLength;
    const uint8_t  bDescriptorType;
    const uint8_t  bEndpointAddress;
    const uint8_t  bmAttributes;
    const uint16_t wMaxPacketSize;
    const uint8_t  bInterval;
} GCC_ATTRIBUTE_PACKED USB_Std_Endpoint_Descriptor_t;




// /* TODO: Trying to architect way to configure any possible Descriptor Configuration
// at compile-time */

// /**
//  * Non-standard Descriptors to offer flexibility. Allows user to assign
//  * any Descriptor Configuration to their Device.
//  */

// /**
//  * @brief Allows user to explicitly assign various Endpoints to each Interface
//  * Descriptor. Meant for use within @p USB_Std_Descriptors_Collection structure.
//  * 
//  * @warning Meant for GCC. @p USB_Std_Interface_Descriptor_t and 
//  * @p USB_Std_Endpoint_Descriptor_t are packed. Do NOT declare/use multi-byte 
//  * pointers to any members of these packed structs to prevent unaligned memory 
//  * access. Only access multi-byte members directly as GCC guarantees that misalignment
//  * via direct member access will automatically be handled by the compiler.
//  * 
//  */
// typedef struct
// {
//     const USB_Std_Interface_Descriptor_t Interface_Header;                      /* USB_Std_Interface_Descriptor_t is Packed */
//     const USB_Std_Endpoint_Descriptor_t ** const Endpoint_Descriptors;          /* USB_Std_Endpoint_Descriptor_t is Packed */
// } USB_Dynamic_Interface_Descriptor_t;


// /**
//  * @brief Allows user to explicitly assign various Interface Descriptors 
//  * to each Configuration Descriptor. Meant for use within 
//  * @p USB_Std_Descriptors_Collection structure.
//  * 
//  * @warning Meant for GCC. @p USB_Std_Configuration_Descriptor_t is packed.
//  * Individual members of @p USB_Dynamic_Interface_Descriptor_t are packed.
//  * Do NOT declare/use multi-byte pointers to any members of these packed structs 
//  * to prevent unaligned memory access. Only access multi-byte members 
//  * directly as GCC guarantees that misalignment via direct member access 
//  * will automatically be handled by the compiler.
//  * 
//  */
// typedef struct
// {
//     const USB_Std_Configuration_Descriptor_t Configuration_Header;                  /* USB_Std_Configuration_Descriptor_t is Packed */
//     const USB_Dynamic_Interface_Descriptor_t ** const Interface_Descriptors;        /* Members of USB_Dynamic_Interface_Descriptor_t are Packed but the struct itself is not Packed */
// } USB_Dynamic_Configuration_Descriptor_t;


// /**
//  * @brief Use for maximum flexibility. Allows a Device to be configured with any 
//  * number of Configuration, Interface, and Endpoint Descriptor combinations. Each
//  * Device can only have one Device Descriptor. But it can have multiple Configuration
//  * Descriptors. Each Configuration Descriptor can have its own set of Interface 
//  * Descriptors. Each Interface Descriptor can have its own set of Endpoint Descriptors.
//  * 
//  * @warning Meant for GCC. @p USB_Std_Device_Descriptor_t is packed. 
//  * See @p USB_Dynamic_Configuration_Descriptor_t to see which members of this
//  * struct are packed. Do NOT declare/use multi-byte pointers to any members 
//  * of these packed structs to prevent unaligned memory access. Only access multi-byte 
//  * members directly as GCC guarantees that misalignment via direct member access 
//  * will automatically be handled by the compiler.
//  * 
//  * @note This configuration has to be defined at compile-time and is not able to be
//  * changed during run-time.
//  * 
//  */
// typedef struct
// {
//     const USB_Std_Device_Descriptor_t * const Device_Descriptor;                            /* USB_Std_Device_Descriptor_t is Packed */
//     const USB_Dynamic_Configuration_Descriptor_t * (* const Configuration_Descriptors)[];   /* See USB_Dynamic_Configuration_Descriptor_t to see which members are Packed */
// } USB_Std_Descriptors_Collection;


// // typedef struct
// // {
// //     uint8_t  bLength;
// //     uint8_t  bDescriptorType;
// //     uint16_t wLANGID;
// // } GCC_ATTRIBUTE_PACKED USB_Std_String_Descriptor_Zero_t;


// // typedef struct
// // {
// //     uint8_t  bLength;
// //     uint8_t  bDescriptorType;
// //     uint16_t bString[];
// // } GCC_ATTRIBUTE_PACKED USB_Std_String_Descriptor_t;

#endif
