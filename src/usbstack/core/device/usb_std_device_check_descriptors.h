/**
 * @file usb_std_device_check_descriptors.h
 * @author Ian Ress
 * @brief Functions to check if descriptors created for a standard USB Device are valid.
 * Currently follows USB v2.0
 * @date 2023-04-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef USBSTDDEVICEDESCRIPTORCHECKS_H
#define USBSTDDEVICEDESCRIPTORCHECKS_H

#include <stdbool.h>
#include "usb_std_descriptors.h"

bool USB_Std_Device_Descriptor_Check(const USB_Std_Device_Descriptor_t * const Device_Descriptor);
bool USB_Std_Configuration_Descriptor_Check(const USB_Std_Configuration_Descriptor_t * const Configuration_Descriptor);
bool USB_Std_Interface_Descriptor_Check(const USB_Std_Interface_Descriptor_t * const Interface_Descriptor);
bool USB_Std_Endpoint_Descriptor_Check(const USB_Std_Endpoint_Descriptor_t * const Endpoint_Descriptor);

#endif /* USBSTDDEVICEDESCRIPTORCHECKS_H */
