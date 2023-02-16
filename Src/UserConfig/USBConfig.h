/**
 * @file USBConfig.h
 * @author Ian Ress
 * @brief Configure USB device settings here. All settings are contained in this single header file
 * so it can be included in the rest of the USB stack. This provides a portable way to create 
 * Descriptors and setup the USB device if the settings ever change.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* TODO: Major cleanup and work */
#ifndef USBCONFIG_H
#define USBCONFIG_H


/**********************  COMMENT OUT WHICHEVER FEATURE YOU WOULD NOT LIKE TO USE ********************************/
/**
 * @brief Use this when you want to use the USB Controllers' internal voltage regulator.
 * 
 */
#define USB_USE_INTERNAL_REGULATOR

/**
 * @brief Use this when you want to enables the VBUS pad connected to the USB controller. This is not
 * used to power up the device. It is mostly used to detect when the device is plugged in.
 * 
 */
// #define USB_USE_VBUS_WAKEUP


/**
 * @brief Use this when you want to have the keyboard be a low speed USB device.
 * 
 * \note USB_LOWSPEED_DEVICE or USB_FULLSPEED_DEVICE must be defined. A compile-time
 * error will occur if both are defined or if none are defined.
 * 
 */
// #define USB_LOWSPEED_DEVICE


/**
 * @brief Use this when you want to have the keyboard be a full speed USB device.
 * 
 * \note USB_LOWSPEED_DEVICE or USB_FULLSPEED_DEVICE must be defined. A compile-time
 * error will occur if both are defined or if none are defined.
 * 
 */
#define USB_FULLSPEED_DEVICE




#define USB_VERSION                         0x0200          /*  USB Version 2.0 */

#define NUMBER_OF_CONFIGURATIONS            1

#define NUMBER_OF_INTERFACES                1

#define NUMBER_OF_ENDPOINTS                 0               /*  TODO: There may be different number of endpoints for each interface (if there's more than one interface)
                                                                This does not include Endpoint 0. */
#define ENDPOINT0_MAX_BUFFER_SIZE           8               /* 8 Bytes. Can only be more than 8 bytes if using a Full Speed or High Speed USB Device. */

#define USB_DEVICE_MAX_CURRENT              100             /* mA */

#define ENDPOINT_INTERRUPT_INTERVAL         5               /* ms */

#endif /* USBCONFIG_H */