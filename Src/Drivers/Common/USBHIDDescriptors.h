/**
 * @file USBHIDDescriptors.h
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

#include <stdint.h>
#include "Attributes.h"
#include "USBStdDescriptors.h"

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
    HID_KEYBOARD_INTERFACE_CODE = 0x01,     /* bInterfaceProtocol in Interface Descriptor. Only set when you need when UEFI/BIOS support */
    HID_MOUSE_INTERFACE_CODE = 0x02         /* bInterfaceProtocol in Interface Descriptor. Only set when you need when UEFI/BIOS support */
};


/**
 * Standard Descriptors defined by the USB HID Spec. 
 */

/**
 * @brief Standard USB HID Descriptor Header.
 * 
 * @warning This definition does NOT include bDescriptorType and wDescriptorLength
 * which are needed for each Report and Physical Descriptor assigned to this HID 
 * Descriptor. A minimum of one Report Descriptor is required for every HID Device.
 * Therefore this definition on it's own will not work. Meant for use
 * within @p USB_Dynamic_HID_Descriptor_t.
 * 
 */
struct GCC_ATTRIBUTE_PACKED USB_HID_Std_HID_Descriptor_Header
{
    const uint8_t  bLength;
    const uint8_t  bDescriptorType;
    const uint16_t bcdHID;
    const uint8_t  bCountryCode;
    const uint8_t  bNumDescriptors;
};


/**
 * @brief 
 * 
 */
typedef struct
{
    #error "TODO:"
} GCC_ATTRIBUTE_PACKED USB_HID_Std_Physical_Descriptor_t;




/**
 * Non-standard Descriptors to offer flexibility. Allows user to assign
 * any Descriptor Configuration to their HID Device.
 */


/**
 * @brief Allows user to define any number of Report and Physical Descriptors
 * within an HID Descriptor. Meant for use within @p USB_HID_Dynamic_HID_Descriptor_t.
 * 
 */
typedef struct
{
    const uint8_t  bDescriptorType;
    const uint16_t wDescriptorLength;
    const uint8_t * Report_Descriptor;
    // TODO: Add support for Physical Descriptor
    // void * Report_Or_Physical_Descriptor;  /* Pointer to Report or Physical Descriptor assigned to this header. Typecast to (uint8_t *) or (USB_Std_Physical_Descriptor_t *) depending on which descriptor is used*/
} GCC_ATTRIBUTE_PACKED USB_HID_Report_And_Physical_Descriptors;


/**
 * @brief Non-standard USB HID Descriptor definition. This definition
 * allows the user to assign any number of Report and Physical Descriptors to
 * the HID Descriptor.
 * 
 */
typedef struct
{
    const struct USB_HID_Std_HID_Descriptor_Header HID_Descriptor_Header;
    const USB_HID_Report_And_Physical_Descriptors * (* const Report_And_Physical_Descriptors)[];
} GCC_ATTRIBUTE_PACKED USB_HID_Dynamic_HID_Descriptor_t;


/**
 * @brief Allows the user to explicitly assign both Endpoint and HID Descriptors
 * to each Interface Descriptor. Meant for use in @p USB_HID_Descriptors_Collection
 * structure.
 * 
 */
typedef struct
{
    const uint8_t bLength;              /* Size of the Standard Interface Descriptor. E.g. sizeof(USB_Std_Interface_Descriptor_t). NOT the size of this descriptor. */
    const uint8_t bDescriptorType;
    const uint8_t bInterfaceNumber;
    const uint8_t bAlternateSetting;
    const uint8_t bNumEndpoints;
    const uint8_t bInterfaceClass;
    const uint8_t bInterfaceSubClass;
    const uint8_t bInterfaceProtocol;
    const uint8_t iInterface;
    const USB_Std_Endpoint_Descriptor_t * (* const Endpoint_Descriptors)[];
    const USB_HID_Dynamic_HID_Descriptor_t * (* const HID_Descriptors)[];
} USB_HID_Dynamic_Interface_Descriptor_t;


/**
 * @brief Allows user to explicitly assign various Interfaces to each
 * Configuration Descriptor. Meant for use in @p USB_HID_Descriptors_Collection
 * structure.
 * 
 */
typedef struct
{
    const uint8_t  bLength;             /* Size of the Standard Configuration Descriptor. E.g. sizeof(USB_Std_Configuration_Descriptor_t). NOT the size of this descriptor. */
    const uint8_t  bDescriptionType;
    const uint16_t wTotalLength;        /* Calculated using lengths of Standard Descriptors. */
    const uint8_t  bNumInterfaces;
    const uint8_t  bConfigurationValue;
    const uint8_t  iConfiguration;
    const uint8_t  bmAttributes;
    const uint8_t  bMaxPower;
    const USB_HID_Dynamic_Interface_Descriptor_t * (* const Interface_Descriptors)[];
} GCC_ATTRIBUTE_PACKED USB_HID_Dynamic_Configuration_Descriptor_t;


/**
 * @brief Use for maximum flexibility. Allows a device to be configured with any 
 * number of Configuration, Interface, Endpoint, HID, Report, and Physical Descriptor 
 * combinations. Only one Device Descriptor is defined for each Device. Each Configuration Descriptor
 * stores an array of Interface Descriptors assigned to each Configuration.
 * Each Interface Descriptor stores an array of Endpoint and HID Descriptors assigned to
 * each Interface.
 * 
 * @note This configuration has to be defined at compile-time and is not able to change
 * during run-time.
 * 
 */
typedef struct
{
    const USB_Std_Device_Descriptor_t * const Device_Descriptor;
    const USB_HID_Dynamic_Configuration_Descriptor_t * (* const Configuration_Descriptors)[];
} USB_HID_Descriptors_Collection;


#endif /* USBHIDDESCRIPTORS_H */
