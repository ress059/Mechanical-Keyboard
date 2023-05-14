/**
 * @file USBVersion.h
 * @author Ian Ress
 * @brief USB Version that the codebase currently supports. Kept separate for cleaner organization
 * and repurposing (i.e. another codebase that uses only USB).
 * @date 2023-04-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef USBVERSION_H
#define USBVERSION_H


/**
 * @brief The USB Version currently supported by this codebase in BCD format
 * 0xMMnn where MM is the major version and nn is the minor version. For example,
 * 0x0200 corresponds to v2.0.
 * 
 * @note This value and relevant USB code must be changed if devices in this 
 * codebase are required to conform to specs greater than v2.0.
 * 
 */
#define SOFTWARE_SUPPORTED_USB_VERSION               0x0200


#endif /* USBVERSION_H */
