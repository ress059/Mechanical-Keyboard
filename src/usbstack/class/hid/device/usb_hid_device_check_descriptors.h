/**
 * @file usb_hid_device_check_descriptors.h
 * @author Ian Ress
 * @brief Functions to check if descriptors created for an HID Device are valid.
 * Currently follows HID v1.11
 * @date 2023-04-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef USBHIDDEVICEDESCRIPTORCHECKS_H
#define USBHIDDEVICEDESCRIPTORCHECKS_H

#include "usb_hid_descriptors.h"

/* TODO: */
bool USB_HID_Device_Descriptor_Check(const USB_Std_Device_Descriptor_t * const Device_Descriptor, 
                                 const uint8_t bNumConfigurations);

bool USB_HID_Configuration_Descriptor_Check(const USB_Std_Configuration_Descriptor_t * const Configuration_Descriptor, 
                                        const uint16_t wTotalLength);

/* bInterfaceClass must equal HID_CLASS_CODE */
bool USB_HID_Interface_Descriptor_Check(const USB_Std_Interface_Descriptor_t * const Interface_Descriptor);
bool USB_HID_Std_HID_Descriptor_Check(const USB_HID_Std_HID_Descriptor_t * HID_Descriptor);
bool USB_HID_Dynamic_HID_Descriptor_Check(); /* Any number of Report and Physical Descriptor Headers */

bool USB_HID_Endpoint_Descriptor_Check(const USB_Std_Endpoint_Descriptor_t * const Endpoint_Descriptor);

#endif /* USBHIDDEVICEDESCRIPTORCHECKS_H */
