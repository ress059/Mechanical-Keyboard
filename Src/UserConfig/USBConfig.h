/**
 * @file USBConfig.h
 * @author Ian Ress
 * @brief Configure USB device settings here. All settings are contained in this single header file
 * so it can be included in the rest of the USB stack. For defines that do not have an explicit value, the
 * user should comment out any of these definitions that are not used on their keyboard.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* TODO: Major cleanup and work */
#ifndef USBCONFIG_H
#define USBCONFIG_H

/*---------------------------------- COMMENT OUT ANY FUNCTIONALITY NOT DESIRED IN THESE SET OF DEFINES. ------------------------------------*/
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
 * \note USB_LOW_SPEED_DEVICE or USB_FULL_SPEED_DEVICE must be defined. A compile-time
 * error will occur if both are defined or if none are defined.
 * 
 */
// #define USB_LOW_SPEED_DEVICE

/**
 * @brief Use this when you want to have the keyboard be a full speed USB device.
 * 
 * \note USB_LOW_SPEED_DEVICE or USB_FULL_SPEED_DEVICE must be defined. A compile-time
 * error will occur if both are defined or if none are defined.
 * 
 */
#define USB_FULL_SPEED_DEVICE

/**
 * @brief When this is defined, the internal RC oscillator will be used to clock
 * the USB controller.
 * 
 * \warning This will also set the CPU to use the Internal Oscillator.
 * 
 * \note A compile-time error will occur if this is defined while using a target
 * MCU that does not have an internal oscillator. USB_USE_INTERNAL_OSCILLATOR or 
 * USB_USE_EXTERNAL_OSCILLATOR must be defined. A compile-time error will occur 
 * if both are defined or if none are defined.
 * 
 */
// #define USB_USE_INTERNAL_OSCILLATOR

/**
 * @brief When this is defined, an external oscillator will be used to clock
 * the USB controller.
 * 
 * \warning This will also set the CPU to use the External Oscillator.
 * 
 * \note USB_USE_INTERNAL_OSCILLATOR or USB_USE_EXTERNAL_OSCILLATOR must be defined. 
 * A compile-time error will occur if both are defined or if none are defined.
 * 
 */
#define USB_USE_EXTERNAL_OSCILLATOR





/*---------------------------------- DO NOT COMMENT ANY OF THESE DEFINITIONS OUT. ------------------------------------*/
/**
 * @brief Frequency, in Hz, of the input clock source going into the PLL prescalar. This is
 * used to determine the prescalar value if the external clock is used.
 * 
 * \note This is the frequency of the external clock, not the internal clock. If the target
 * MCU has an internal clock and it is used, it will always be set to the frequency 
 * needed by the target MCU's PLL.
 * 
 */
#define USB_EXTERNAL_CLOCK_FREQUENCY        16000000


/* TODO: */
#define USB_VERSION                         0x0200          /*  USB Version 2.0 */

#define NUMBER_OF_CONFIGURATIONS            1

#define NUMBER_OF_INTERFACES                1

#define NUMBER_OF_ENDPOINTS                 0               /*  TODO: There may be different number of endpoints for each interface (if there's more than one interface)
                                                                This does not include Endpoint 0. */
#define ENDPOINT0_MAX_BUFFER_SIZE           8               /* 8 Bytes. Can only be more than 8 bytes if using a Full Speed or High Speed USB Device. */

#define USB_DEVICE_MAX_CURRENT              100             /* mA */

#define ENDPOINT_INTERRUPT_INTERVAL         5               /* ms */

#endif /* USBCONFIG_H */