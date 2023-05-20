/**
 * @file usb_config.h
 * @author Ian Ress
 * @brief Configure USB device settings here. Kept separate for cleaner organization
 * and repurposing (i.e. another codebase that uses only USB).
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef USBCONFIG_H
#define USBCONFIG_H


/**
 * @brief The USB version to compile for in BCD format 0xMMnn where MM is the major 
 * version and nn is the minor version. For example, 0x0200 corresponds to v2.0
 * 
 * @warning A compilation error will occur if this value is greater than 
 * SOFTWARE_SUPPORTED_USB_VERSION in usb_version.h. This means the USB version
 * set here is not supported by the current codebase.
 * 
 * @warning A compilation error will occur if this value is greater than 
 * CPU_SUPPORTED_USB_VERSION in target_specific.h. This means the USB Version
 * set here is not supported by the target CPU.
 * 
 * @attention This value is checked at run-time when USB Device Constructors 
 * are called. The relevant Constructor will return false if bcdUSB in the Device 
 * Descriptor is greater than this value. Please note that bcdUSB is only one of 
 * the many checks done. The Constructors check all descriptors and will also 
 * return false if any of those checks also do not pass. It is up to the user on 
 * how to handle this error.
 * 
 * @note This define can also be used to organize any code differentiation between 
 * USB versions. For example:
 * 
 * #if (USB_VERSION_ == 0x0300)
 *      // Code specific to USB v3.0
 * #elif (USB_VERSION_ == 0x0200)
 *      // Code specific to USB v2.0
 * #endif
 * 
 */
#define USB_VERSION_                         0x0200


/**
 * @brief Set to 1 to make all USB devices running on the target MCU Low
 * Speed Devices. Otherwise set to 0.
 * 
 * @warning Either USB_LOW_SPEED_DEVICE, USB_FULL_SPEED_DEVICE, or 
 * USB_HI_SPEED_DEVICE must be set to 1. A compilation error will occur if 
 * all speeds are set to 0 or if multiple speeds are set to 1.
 * 
 * @attention This codebase is intended for hardware targets with one USB
 * Controller that runs at a single speed. If this was compiled on a target
 * that can support multiple devices running at different speeds, all of 
 * the devices would still have to be set to Low Speed. compile_checks.h 
 * and USB hardware code would have to be edited in order to change this 
 * behavior.
 * 
 * @attention This is a property of the target MCU being compiled on. As a result,
 * only use this definition in hardware-specific code. Do NOT use this in the 
 * general application in order to make most of the code portable across different 
 * architectures.
 * 
 */
#define USB_LOW_SPEED_DEVICE                0


/**
 * @brief Set to 1 to make all USB devices running on the target MCU Full
 * Speed Devices. Otherwise set to 0.
 * 
 * @warning Either USB_LOW_SPEED_DEVICE, USB_FULL_SPEED_DEVICE, or 
 * USB_HI_SPEED_DEVICE must be set to 1. A compilation error will occur if 
 * all speeds are set to 0 or if multiple speeds are set to 1.
 * 
 * @attention This codebase is intended for hardware target's with one USB
 * Controller that runs at a single speed. If this was compiled on a target
 * that can support multiple devices running at different speeds, all of 
 * the devices would still have to be set to Full Speed. compile_checks.h 
 * and USB hardware code would have to be edited in order to change this 
 * behavior.
 * 
 * @attention This is a property of the target MCU being compiled on. As a result,
 * only use this definition in hardware-specific code. Do NOT use this in the 
 * general application in order to make most of the code portable across different 
 * architectures.
 * 
 */
#define USB_FULL_SPEED_DEVICE               1


/**
 * @brief Set to 1 to make all USB devices running on the target MCU Hi
 * Speed Devices. Otherwise set to 0.
 * 
 * @warning Either USB_LOW_SPEED_DEVICE, USB_FULL_SPEED_DEVICE, or 
 * USB_HI_SPEED_DEVICE must be set to 1. A compilation error will occur if 
 * all speeds are set to 0 or if multiple speeds are set to 1.
 * 
 * @attention This codebase is intended for hardware target's with one USB
 * Controller that runs at a single speed. If this was compiled on a target
 * that can support multiple devices running at different speeds, all of 
 * the devices would still have to be set to Hi-Speed. compile_checks.h 
 * and USB hardware code would have to be edited in order to change this 
 * behavior.
 * 
 * @attention This is a property of the target MCU being compiled on. As a result,
 * only use this definition in hardware-specific code. Do NOT use this in the 
 * general application in order to make most of the code portable across different 
 * architectures.
 * 
 */
#define USB_HI_SPEED_DEVICE                 0


/**
 * @brief Set to 1 if this is a self-powered device. Otherwise set to 0.
 * 
 */
#define USB_SELF_POWERED_DEVICE             0


/**
 * @brief Set to 1 if this is a self-powered device with VBUS detection enabled. 
 * Otherwise set to 0. This is not used to power the device. This is used to detect 
 * when the device is plugged into the bus. As a result this only makes sense to 
 * use for self-powered devices. TODO: Have user-definable handler execute when VBUS
 * signal goes from low to high.
 * 
 * @warning A compilation error will occur if USB_USE_VBUS_DETECTION is set to 1 
 * but USB_SELF_POWERED_DEVICE is set to 0.
 * 
 * @attention This is a property of the target MCU being compiled on. As a result,
 * only use this definition in hardware-specific code. Do NOT use this in the 
 * general application in order to make most of the code portable across different 
 * architectures.
 * 
 * @note Some target's have a dedicated VBUS detection peripheral embedded in
 * its USB Controller. Other devices will require the VBUS signal to be wired 
 * to a GPIO. In the second case the user must supply the GPIO this will be 
 * assigned to.
 * 
 */
#define USB_USE_VBUS_DETECTION              0


/**
 * @brief The GPIO pin used to detect a VBUS signal if USB_USE_VBUS_DETECTION
 * is set to 1.
 * 
 * @warning A compilation error will only occur if this definition does not 
 * exist. The pin assignment is NOT checked at compile-time. It is up to the 
 * user to ensure the pin assignment is correct for their target.
 * 
 * @note Some target's have a dedicated VBUS detection peripheral embedded in
 * its USB Controller so a GPIO VBUS detection pin is not needed. In this
 * scenario, the value of USB_VBUS_DETECT_GPIO is ignored.
 * 
 */
#define USB_VBUS_DETECT_GPIO                {PIN_PB2}


/**
 * @brief Set to 1 to have the target's USB Controller use the Internal
 * Oscillator.
 * 
 * @warning A compile-time error will occur if this value is set to 1 and
 * CAN_USE_USB_INTERNAL_OSCILLATOR is set to 0. This means we are trying to use
 * the Internal Oscillator to clock the USB Controller when the hardware
 * target being compiled on does not support this feature. 
 * 
 * @warning Either USB_USE_INTERNAL_OSCILLATOR or USB_USE_EXTERNAL_OSCILLATOR
 * must be set to 1. A compile-time error will occur if both are set to 0 or 
 * both are set to 1.
 * 
 * @attention On some AVR Architecetures, this will also set the CPU to use the 
 * Internal Oscillator!!
 * 
 * @attention This is a property of the target MCU being compiled on. As a result,
 * only use this definition in hardware-specific code. Do NOT use this in the 
 * general application in order to make most of the code portable across different 
 * architectures.
 * 
 */
#define USB_USE_INTERNAL_OSCILLATOR         0


/**
 * @brief Set to 1 to have the target's USB Controller use an External
 * Oscillator.
 * 
 * @warning A compile-time error will occur if this value is set to 1 and
 * USB_EXTERNAL_CLOCK_FREQUENCY is set to a value that the target does
 * not support. For example for ATMega32U4, the external clock must be
 * 8MHz or 16MHz to use the USB Controller.
 * 
 * @warning Either USB_USE_INTERNAL_OSCILLATOR or USB_USE_EXTERNAL_OSCILLATOR
 * must be set to 1. A compile-time error will occur if both are set to 0 or 
 * both are set to 1.
 * 
 * @attention On AVR Architecetures, this will also set the CPU to use the 
 * External Oscillator!!
 * 
 * @attention This is a property of the target MCU being compiled on. As a result,
 * only use this definition in hardware-specific code. Do NOT use this in the 
 * general application in order to make most of the code portable across different 
 * architectures.
 * 
 */
#define USB_USE_EXTERNAL_OSCILLATOR         1


/**
 * @brief Frequency, in Hz, of the External Oscillator being used. This is used
 * to set up the USB Controller and necessary prescalars if USB_USE_EXTERNAL_OSCILLATOR 
 * is set to 1.
 * 
 * @warning A compile-time error will occur if USB_USE_EXTERNAL_OSCILLATOR is
 * set to 1 and USB_EXTERNAL_CLOCK_FREQUENCY is set to a value that the target does
 * not support. For example for ATMega32U4, the external clock must be 8MHz or 16MHz 
 * to use the USB Controller.
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
 * This value can be 8, 16, 32, or 64 bytes for Full-Speed Devices. These 
 * conditions are automatically checked at compile-time.
 * 
 */
#define USB_CONTROL_ENDPOINT_SIZE           8


#endif /* USBCONFIG_H */
