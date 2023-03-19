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
 * @note USB_LOW_SPEED_DEVICE or USB_FULL_SPEED_DEVICE must be defined. A compile-time
 * error will occur if both are defined or if none are defined.
 * 
 */
// #define USB_LOW_SPEED_DEVICE

/**
 * @brief Use this when you want to have the keyboard be a full speed USB device.
 * 
 * @note USB_LOW_SPEED_DEVICE or USB_FULL_SPEED_DEVICE must be defined. A compile-time
 * error will occur if both are defined or if none are defined.
 * 
 */
#define USB_FULL_SPEED_DEVICE

/**
 * @brief When this is defined, the internal RC oscillator will be used to clock
 * the USB controller.
 * 
 * @warning This will also set the CPU to use the Internal Oscillator.
 * 
 * @note A compile-time error will occur if this is defined while using a target
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
 * @warning This will also set the CPU to use the External Oscillator.
 * 
 * @note USB_USE_INTERNAL_OSCILLATOR or USB_USE_EXTERNAL_OSCILLATOR must be defined. 
 * A compile-time error will occur if both are defined or if none are defined.
 * 
 */
#define USB_USE_EXTERNAL_OSCILLATOR





/*---------------------------------- DO NOT COMMENT ANY OF THESE DEFINITIONS OUT. ------------------------------------*/
/**
 * @brief Frequency, in Hz, of the input clock source going into the PLL prescalar. This is
 * used to determine the prescalar value if the external clock is used.
 * 
 * @note This is the frequency of the external clock, not the internal clock. If the target
 * MCU has an internal clock and it is used, it will always be set to the frequency 
 * needed by the target MCU's PLL.
 * 
 */
#define USB_EXTERNAL_CLOCK_FREQUENCY        16000000

/**
 * @brief The maximum amount of data, in bytes, that the Endpoint 0 bank 
 * can receive/send for Control Transfers. This is the bMaxPacketSize0 
 * entry in the Device Descriptor.
 * 
 * @note This value must be less than @p ENDPOINT0_MAX_FIFO_SIZE which is a
 * property of the target MCU. This must be 8 bytes for Low-Speed Devices.
 * Can be 8, 16, 32, or 64 bytes for Full-Speed Devices. These conditions
 * are automatically checked at compile-time.
 * 
 */
#define CONTROL_ENDPOINT_SIZE               8

/**
 * @brief The maximum amount of data, in bytes, that the Endpoint 1 bank 
 * can receive/send. This is for the HID Report sent to the host. This is
 * wMaxPacketSize of the Endpoint 1 Descriptor.
 * 
 * @warning This must be 8 bytes or less for Low-Speed Devices. This must 
 * be 64 bytes or less for Full-Speed Devices. These conditions are 
 * automatically checked at compile-time.
 * 
 * @warning This must also be less than the selected endpoint's max FIFO
 * size. This check is only done (at run-time) for targets that check 
 * this via hardware. E.g. For @p AVR_DEVICE_FAMILY1 devices, the CFGOK 
 * bit is set by hardware if the configured endpoint's size is less 
 * than the max FIFO size. Therefore this check is done at run-time when 
 * @p USBReg_Is_Endpoint_Configured() executes for these devices. Otherwise
 * this check is not done and it is up to the user to ensure the sizes
 * are set up correctly.
 * 
 */
#define HID_ENDPOINT_SIZE                   64

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


/* TODO: */
#define USB_VERSION                         0x0200          /*  USB Version 2.0 */

#define NUMBER_OF_CONFIGURATIONS            1

#define NUMBER_OF_INTERFACES                1

#define USB_DEVICE_MAX_CURRENT              100             /* mA */

#define ENDPOINT_INTERRUPT_INTERVAL         5               /* ms */

#endif /* USBCONFIG_H */