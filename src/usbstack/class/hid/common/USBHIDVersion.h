/**
 * @file USBHIDVersion.h
 * @author Ian Ress
 * @brief HID Version that the codebase currently supports. Kept separate for cleaner organization
 * and repurposing (i.e. another codebase that uses only USB).
 * @date 2023-04-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef USBHIDVERSION_H
#define USBHIDVERSION_H


/**
 * @brief The HID Version currently supported by this codebase in BCD format
 * 0xMMnn where MM is the major version and nn is the minor version. For example,
 * 0x0111 corresponds to v1.1.
 * 
 * @note This value and relevant HID code must be changed if devices in this 
 * codebase are required to conform to future specs greater than v1.11.
 * 
 */
#define SOFTWARE_SUPPORTED_HID_VERSION               0x0111


#endif /* USBHIDVERSION_H */
