/**
 * @file usb_hid_descriptors.h
 * @author Ian Ress
 * @brief Descriptor headers defined by the USB HID spec. Currently follows HID Spec v1.11.
 * This is separated out from the standard descriptors for cleaner organization.
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef USBHIDDESCRIPTORS_H
#define USBHIDDESCRIPTORS_H

#include <stdbool.h>
#include <stdint.h>
#include "attributes.h"
#include "usb_std_descriptors.h"

enum
{
    HID_CLASS_VERSION = 0x111               /* Version 1.11. If HID Class Specification is ever updated, this should be changed. */
};

enum
{
    HID_CLASS_CODE = 0x03                   /* bInterfaceClass in Interface Descriptor */
};

enum
{
    HID_DESCRIPTOR_TYPE = 0x21,             /* bDescriptorType in HID Descriptor */
    HID_REPORT_DESCRIPTOR_TYPE = 0x22,      /* Additional bDescriptorType in HID Descriptor */
    HID_PHYSICAL_DESCRIPTOR_TYPE = 0x23     /* Additional bDescriptorType in HID Descriptor */
};

enum
{
    HID_NO_SUBCLASS = 0x00,                 /* bInterfaceProtocol in Interface Descriptor. */
    HID_BOOT_INTERFACE_SUBCLASS = 0x01      /* bInterfaceProtocol in Interface Descriptor. Means device requires Boot support. */
};

enum
{
    HID_NO_PROTOCOL_CODE = 0x00,            /* bInterfaceProtocol in Interface Descriptor must be set to this if bInterfaceSubClass is 0 */
    HID_KEYBOARD_INTERFACE_CODE = 0x01,     /* bInterfaceProtocol in Interface Descriptor. Only set when you need when UEFI/BIOS support */
    HID_MOUSE_INTERFACE_CODE = 0x02         /* bInterfaceProtocol in Interface Descriptor. Only set when you need when UEFI/BIOS support */
};



/**
 * Standard HID Descriptors defined by USB HID spec.
 */

/**
 * @brief All HID Descriptors must include at least one Report Descriptor.
 * This structure is the base-level descriptor required by all HID Devices.
 * Use @p USB_HID_Dynamic_HID_Descriptor_t if your Device uses additional
 * Report/Physical Descriptors.
 * 
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
    const uint16_t bcdHID;
    const uint8_t  bCountryCode;
    const uint8_t  bNumDescriptors;     /* Should be 1 since only using 1 Report Descriptor */
    const uint8_t  bDescriptorType2;    /* Report Descriptor */
    const uint16_t wDescriptorLength;   /* Size of Report Descriptor in bytes */
} GCC_ATTRIBUTE_PACKED USB_HID_Std_HID_Descriptor_t;


// /* TODO: Trying to architect way to configure any possible Descriptor Configuration
// at compile-time */

// /**
//  * Non-standard Descriptors to offer flexibility. Allows user to assign
//  * any Descriptor Configuration to their HID Device.
//  */

// /**
//  * @brief The HID Descriptor Header. Not meant to be used within the
//  * application as this does not include the info for the Report/Physical
//  * Descriptors attached to this HID Descriptor. Meant for use in 
//  * @p USB_HID_Dynamic_HID_Descriptor_t
//  * 
//  * @warning Meant for GCC. Do NOT declare/use multi-byte pointers to 
//  * any members of this struct to prevent unaligned memory access. Only 
//  * access multi-byte members directly as GCC guarantees that misalignment
//  * via direct member access will automatically be handled by the compiler.
//  * 
//  */
// typedef struct
// {
//     const uint8_t  bLength;
//     const uint8_t  bDescriptorType;
//     const uint16_t bcdHID;
//     const uint8_t  bCountryCode;
//     const uint8_t  bNumDescriptors;
// } GCC_ATTRIBUTE_PACKED USB_HID_Descriptor_Header;


// /**
//  * @brief Headers for any Report and Physical Descriptors the user adds
//  * to their HID Descriptor. Not meant to be used within the application. 
//  * Meant for use in @p USB_HID_Dynamic_HID_Descriptor_t
//  * 
//  * @warning Meant for GCC. Do NOT declare/use multi-byte pointers to 
//  * any members of this struct to prevent unaligned memory access. Only 
//  * access multi-byte members directly as GCC guarantees that misalignment
//  * via direct member access will automatically be handled by the compiler.
//  * 
//  */
// typedef struct
// {
//     const uint8_t  bDescriptorType;
//     const uint16_t wDescriptorLength;
// } GCC_ATTRIBUTE_PACKED USB_HID_Report_And_Physical_Descriptor_Header;


// /**
//  * @brief Allows the user to assign any number of Report and Physical
//  * Descriptors Headers to an HID Descriptor. Not meant to be used 
//  * within the application. Meant for use in @p USB_HID_Dynamic_HID_Descriptor_t
//  * 
//  * @warning Meant for GCC. @p USB_HID_Descriptor_Header 
//  * and @p USB_HID_Report_And_Physical_Descriptor_Header are packed. 
//  * Do NOT declare/use multi-byte pointers to any members of these packed 
//  * structs to prevent unaligned memory access. Only access multi-byte members 
//  * directly as GCC guarantees that misalignment via direct member access 
//  * will automatically be handled by the compiler.
//  * 
//  */
// typedef struct
// {
//     const USB_HID_Descriptor_Header HID_Header;                                                     /* USB_HID_Descriptor_Header is Packed */
//     const USB_HID_Report_And_Physical_Descriptor_Header Report_And_Physical_Descriptor_Headers[];   /* USB_HID_Report_And_Physical_Descriptor_Header is Packed */
// } GCC_ATTRIBUTE_PACKED USB_HID_Dynamic_HID_Descriptor_Headers_t;


// /**
//  * @brief Meant to be used within the application. Allows the user 
//  * to assign any number of Report and Physical Descriptors to an 
//  * HID Descriptor. Also includes the Report and Physical Descriptors 
//  * meant to be assigned to this HID Descriptor.
//  * 
//  * @warning Meant for GCC. @p USB_HID_Dynamic_HID_Descriptor_Headers_t 
//  * is packed. Do NOT declare/use multi-byte pointers to any members of this 
//  * packed struct to prevent unaligned memory access. Only access multi-byte 
//  * members directly as GCC guarantees that misalignment via direct member 
//  * access will automatically be handled by the compiler.
//  * 
//  */
// typedef struct
// {
//     const USB_HID_Dynamic_HID_Descriptor_Headers_t HID_Descriptor;  /* USB_HID_Dynamic_HID_Descriptor_Headers_t is Packed */
//     const uint8_t * const Report_Descriptors[];
//     /* TODO: Physical Descriptors */
// } USB_HID_Dynamic_HID_Descriptor_t;


// /**
//  * @brief Meant to be used within the application. Allows the user to 
//  * explicitly assign both Endpoint and HID Descriptors to each Interface
//  * Descriptor. Meant for use in @p USB_HID_Descriptors_Collection 
//  * 
//  * @warning Meant for GCC. @p USB_Std_Interface_Descriptor_t 
//  * @p USB_Std_Endpoint_Descriptor_t and @p USB_HID_Dynamic_HID_Descriptor_Headers_t 
//  * in @p USB_HID_Dynamic_HID_Descriptor_t are packed. Do NOT declare/use multi-byte 
//  * pointers to any members of these packed structs to prevent unaligned memory access. 
//  * Only access multi-byte members directly as GCC guarantees that misalignment 
//  * via direct member access will automatically be handled by the compiler.
//  * 
//  */
// typedef struct
// {
//     const USB_Std_Interface_Descriptor_t Interface_Header;                      /* USB_Std_Interface_Descriptor_t is Packed */
//     const USB_Std_Endpoint_Descriptor_t * (* const Endpoint_Descriptors)[];     /* USB_Std_Endpoint_Descriptor_t is Packed */
//     const USB_HID_Dynamic_HID_Descriptor_t * (* const HID_Descriptors)[];       /* USB_HID_Dynamic_HID_Descriptor_Headers_t in USB_HID_Dynamic_HID_Descriptor_t is Packed */
// } USB_HID_Dynamic_Interface_Descriptor_t;


// /**
//  * @brief Meant to be used within the application. Allows the user to 
//  * explicitly assign various Interface Descriptors to each Configuration 
//  * Descriptor. Meant for use within @p USB_HID_Descriptors_Collection
//  * 
//  * @warning Meant for GCC. @p USB_Std_Configuration_Descriptor_t is packed.
//  * The struct members of @p USB_HID_Dynamic_Interface_Descriptor_t are packed
//  * but the @p USB_HID_Dynamic_Interface_Descriptor_t struct itself is not packed.
//  * Do NOT declare/use multi-byte pointers to any members of these packed structs to 
//  * prevent unaligned memory access. Only access multi-byte members directly as 
//  * GCC guarantees that misalignment via direct member access will automatically 
//  * be handled by the compiler.
//  * 
//  */
// typedef struct
// {
//     const USB_Std_Configuration_Descriptor_t Configuration_Header;                      /* USB_Std_Configuration_Descriptor_t is Packed */
//     const USB_HID_Dynamic_Interface_Descriptor_t * (* const Interface_Descriptors)[];   /* Members of USB_HID_Dynamic_Interface_Descriptor_t are individually Packed but the struct itself is not */
// } USB_HID_Dynamic_Configuration_Descriptor_t;


// /**
//  * @brief Use for maximum flexibility. Allows a Device to be configured with any 
//  * number of Configuration, Interface, HID, and Endpoint Descriptor combinations. Each
//  * Device can only have one Device Descriptor. But it can have multiple Configuration
//  * Descriptors. Each Configuration Descriptor can have its own set of Interface 
//  * Descriptors. Each Interface Descriptor can have its own set of HID and 
//  * Endpoint Descriptors.
//  * 
//  * @warning Meant for GCC. @p USB_Std_Device_Descriptor_t is packed. See 
//  * @p USB_HID_Dynamic_Configuration_Descriptor_t to see which members
//  * of this struct are packed. Do NOT declare/use multi-byte pointers to any members 
//  * of these packed structs to prevent unaligned memory access. Only access multi-byte 
//  * members directly as GCC guarantees that misalignment via direct member access 
//  * will automatically be handled by the compiler.
//  * 
//  * @note This configuration has to be defined at compile-time and is not able to be
//  * changed during run-time. This includes the Report and Physical Descriptors also
//  * assigned to this Device.
//  * 
//  */
// typedef struct
// {
//     const USB_Std_Device_Descriptor_t * const Device_Descriptor;                                /* USB_Std_Device_Descriptor_t is Packed */
//     const USB_HID_Dynamic_Configuration_Descriptor_t * (* const Configuration_Descriptors)[];   /* See description to see which members are Packed */
// } USB_HID_Descriptors_Collection;


#endif /* USBHIDDESCRIPTORS_H */
