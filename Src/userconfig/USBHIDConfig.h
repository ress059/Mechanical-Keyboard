/**
 * @file USBHIDConfig.h
 * @author Ian Ress
 * @brief Configure HID device settings here. Kept separate for cleaner organization
 * and repurposing (i.e. another codebase that uses only USB).
 * @date 2023-04-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef USBHIDCONFIG_H
#define USBHIDCONFIG_H


/**
 * @brief The HID version to compile for in BCD format 0xMMnn where MM is the major 
 * version and nn is the minor version. For example, 0x0111 corresponds to v1.11.
 * 
 * @warning A compilation error will occur if this value is greater than 
 * SOFTWARE_SUPPORTED_HID_VERSION in USBHIDVersion.h. This means the HID version
 * set here is not supported by the current codebase. This value is also checked
 * at run-time when USB HID Device Constructors are called. The relevant Constructor
 * will return false if bcdHID in the HID Descriptor is greater than this value.
 * Please note that bcdHID is only one of the many checks done. The Constructors 
 * check all descriptors and will also return false if any of those checks also do 
 * not pass. It is up to the user on how to handle this error.
 * 
 * @note This define can also be used to organize any code differentiation between 
 * HID versions. For example:
 * 
 * #if (HID_VERSION_ > 0x0111)
 *      // Code specific to HID v1.12 and greater
 * #else
 *      // Code specific to HID v1.11 and lower
 * #endif
 * 
 */
#define HID_VERSION_                         0x0111


/**
 * @brief The endpoint number to assign the HID endpoint to. Depending on
 * the target, there may be multiple endpoint numbers that have different
 * max FIFO sizes. Therefore it may be useful to assign the HID endpoint
 * number to one with the largest FIFO size.
 * 
 * @warning Do not assign this to Endpoint 0. Endpoint 0 is always
 * reserved for the Control Endpoint. This condition is checked
 * at compile-time.
 * 
 */
#define HID_ENDPOINT_NUMBER                 1


/**
 * @brief The maximum amount of data, in bytes, that the Endpoint 1 bank 
 * can receive/send. This is for the HID Report sent to the host. This is
 * wMaxPacketSize of the HID Endpoint Descriptor.
 * 
 * @warning This must be 8 bytes or less for Low-Speed Devices. This must 
 * be 64 bytes or less for Full-Speed Devices. These conditions are 
 * automatically checked at compile-time.
 * 
 * @warning This must also be less than the selected endpoint's max FIFO
 * size. This check is only done (at run-time) for targets that check 
 * this via hardware. E.g. For @p ATMEGAXXU4_SERIES devices, the CFGOK 
 * bit is set by hardware if the configured endpoint's size is less 
 * than the max FIFO size. Therefore this check is done at run-time when 
 * @p USBReg_Is_Endpoint_Configured() executes for these devices. Otherwise
 * this check is not done and it is up to the user to ensure the sizes
 * are set up correctly.
 * 
 */
#define HID_ENDPOINT_SIZE                   64


#endif /* USBHIDCONFIG_H */
