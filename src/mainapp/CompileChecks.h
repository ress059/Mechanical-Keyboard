/**
 * @file CompileChecks.h
 * @author Ian Ress
 * @brief Solely used for compile-time checks. CompileChecks.h/.c is meant to be compiled in 
 * its own translation unit, never being included in any other source/header file.
 * 
 * @date 2023-02-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#if !defined(ONLY_INCLUDE_COMPILECHECKS_H_IN_COMPILECHECKS_C_)
    #error "Only include this file in CompileChecks.c"
#else
    #ifndef COMPILECHECKS_H
    #define COMPILECHECKS_H

        #include "Attributes.h"
        #include "TargetSpecific.h"
        #include "KeyboardConfig.h"
        #include "USBConfig.h"
        #include "USBHIDConfig.h"
        #include "USBHIDVersion.h"
        #include "USBVersion.h"


        /**
         * @brief Only used to check if the CPU wordsize in TargetSpecific.h 
         * is configured with a valid value. Never used.
         * 
         */
        static inline void CPU_Wordsize_Check(void) GCC_ATTRIBUTE_UNUSED;
        static inline void CPU_Wordsize_Check(void)
        {
            (void)sizeof(char[1 - 2*!(sizeof(CPU_RegSize_t))]);
        }



        /**
         * Mandatory definition in TargetSpecific.h not included.
         */
        #if ((!defined(CPU_BIG_ENDIAN) && !defined(CPU_LITTLE_ENDIAN)))
            #error "CPU_BIG_ENDIAN or CPU_LITTLE_ENDIAN must be defined for target. Fix in TargetSpecific.h"
        #endif
        #if (!defined(NUMBER_OF_IO_PINS))
            #error "NUMBER_OF_IO_PINS must be defined and set for target. Fix in TargetSpecific.h"
        #endif
        #if (!defined(CPU_SUPPORTED_USB_VERSION))
            #error "CPU_SUPPORTED_USB_VERSION must be defined and set for target. Fix in TargetSpecific.h"
        #endif
        #if (!defined(NUMBER_OF_USB_ENDPOINTS))
            #error "NUMBER_OF_USB_ENDPOINTS must be defined and set for target. Fix in TargetSpecific.h"
        #endif
        #if (!defined(ENDPOINT0_MAX_FIFO_SIZE))
            #error "ENDPOINT0_MAX_FIFO_SIZE must be defined and set for target. Fix in TargetSpecific.h"
        #endif
        #if (!defined(HAS_VBUS_PERIPHERAL))
            #error "HAS_VBUS_PERIPHERAL must be defined and set to 0 or 1 for target. Fix in TargetSpecific.h"
        #endif
        #if (!defined(CAN_BE_USB_LOW_SPEED_DEVICE))
            #error "CAN_BE_USB_LOW_SPEED_DEVICE must be defined and set to 0 or 1 for target. Fix in TargetSpecific.h"
        #endif
        #if (!defined(CAN_BE_USB_FULL_SPEED_DEVICE))
            #error "CAN_BE_USB_FULL_SPEED_DEVICE must be defined and set to 0 or 1 for target. Fix in TargetSpecific.h"
        #endif
        #if (!defined(CAN_BE_USB_HI_SPEED_DEVICE))
            #error "CAN_BE_USB_HI_SPEED_DEVICE must be defined and set to 0 or 1 for target. Fix in TargetSpecific.h"
        #endif
        #if (!defined(CAN_USE_USB_INTERNAL_OSCILLATOR))
            #error "CAN_USE_USB_INTERNAL_OSCILLATOR must be defined and set to 0 or 1 for target. Fix in TargetSpecific.h"
        #endif



        /**
         * Invalid definition in TargetSpecific.h
         */
        #if (defined(CPU_BIG_ENDIAN) && defined(CPU_LITTLE_ENDIAN))
            #error "Target MCU is defined as both Little Endian and Big Endian since CPU_BIG_ENDIAN and CPU_LITTLE_ENDIAN are defined. Must only define one. Fix in TargetSpecific.h"
        #endif
        #if ( (NUMBER_OF_IO_PINS) <= 0 )
            #error "NUMBER_OF_IO_PINS must be greater than 0. Fix in TargetSpecific.h"
        #endif
        #if ( (CPU_SUPPORTED_USB_VERSION) < 0x0100 )
            #error "CPU_SUPPORTED_USB_VERSION must be at least v1.0. Fix in TargetSpecific.h"
        #endif
        #if ( (NUMBER_OF_USB_ENDPOINTS) < 2 )
            #error "NUMBER_OF_USB_ENDPOINTS must be at least 2. Fix in TargetSpecific.h"
        #endif
        #if ( (ENDPOINT0_MAX_FIFO_SIZE) < 8 )
            #error "ENDPOINT0_MAX_FIFO_SIZE must be at least 8. Fix in TargetSpecific.h"
        #endif
        #if ( ((HAS_VBUS_PERIPHERAL) != 0) && ((HAS_VBUS_PERIPHERAL) != 1) )
            #error "HAS_VBUS_PERIPHERAL must be set to either 0 or 1. Fix in TargetSpecific.h"
        #endif
        #if ( ((CAN_BE_USB_LOW_SPEED_DEVICE) != 0) && ((CAN_BE_USB_LOW_SPEED_DEVICE) != 1) )
            #error "CAN_BE_USB_LOW_SPEED_DEVICE must be set to either 0 or 1. Fix in TargetSpecific.h"
        #endif
        #if ( ((CAN_BE_USB_FULL_SPEED_DEVICE) != 0) && ((CAN_BE_USB_FULL_SPEED_DEVICE) != 1) )
            #error "CAN_BE_USB_FULL_SPEED_DEVICE must be set to either 0 or 1. Fix in TargetSpecific.h"
        #endif
        #if ( ((CAN_USE_USB_INTERNAL_OSCILLATOR) != 0) && ((CAN_USE_USB_INTERNAL_OSCILLATOR) != 1) )
            #error "CAN_USE_USB_INTERNAL_OSCILLATOR must be set to either 0 or 1. Fix in TargetSpecific.h"
        #endif
        #if ( ((CAN_BE_USB_LOW_SPEED_DEVICE) == 0) && ((CAN_BE_USB_FULL_SPEED_DEVICE) == 0) )
            #error "No speed capabilities of the target MCU is defined since CAN_BE_USB_LOW_SPEED_DEVICE and CAN_BE_USB_FULL_SPEED_DEVICE are set to 0. Fix in TargetSpecific.h"
        #endif



        /**
         * Mandatory definition in USBConfig.h not included.
         */
        #if (!defined(USB_VERSION_))
            #error "USB_VERSION_ must be defined and set. Fix in USBConfig.h"
        #endif
        #if (!defined(USB_LOW_SPEED_DEVICE))
            #error "USB_LOW_SPEED_DEVICE must be defined and set to 0 or 1. Fix in USBConfig.h"
        #endif
        #if (!defined(USB_FULL_SPEED_DEVICE))
            #error "USB_FULL_SPEED_DEVICE must be defined and set to 0 or 1. Fix in USBConfig.h"
        #endif
        #if (!defined(USB_HI_SPEED_DEVICE))
            #error "USB_HI_SPEED_DEVICE must be defined and set to 0 or 1. Fix in USBConfig.h"
        #endif
        #if (!defined(USB_SELF_POWERED_DEVICE))
            #error "USB_SELF_POWERED_DEVICE must be defined and set to 0 or 1. Fix in USBConfig.h"
        #endif
        #if (!defined(USB_USE_VBUS_DETECTION))
            #error "USB_USE_VBUS_DETECTION must be defined and set to 0 or 1. Fix in USBConfig.h"
        #endif
        #if (!defined(USB_VBUS_DETECT_GPIO))
            #error "USB_VBUS_DETECT_GPIO must be defined and set. Fix in USBConfig.h"
        #endif
        #if (!defined(USB_USE_INTERNAL_OSCILLATOR))
            #error "USB_USE_INTERNAL_OSCILLATOR must be defined and set to 0 or 1. Fix in USBConfig.h"
        #endif
        #if (!defined(USB_USE_EXTERNAL_OSCILLATOR))
            #error "USB_USE_EXTERNAL_OSCILLATOR must be defined and set to 0 or 1. Fix in USBConfig.h"
        #endif
        #if (!defined(USB_EXTERNAL_CLOCK_FREQUENCY))
            #error "USB_EXTERNAL_CLOCK_FREQUENCY must be defined and set. Fix in USBConfig.h"
        #endif
        #if (!defined(USB_CONTROL_ENDPOINT_SIZE))
            #error "USB_CONTROL_ENDPOINT_SIZE must be defined and set. Fix in USBConfig.h"
        #endif



        /**
         * Invalid definition in USBConfig.h
         */
        #if ( (USB_VERSION_) < 0x0100 )
            #error "USB_VERSION_ must be set to at least v1.0. Fix in USBConfig.h"
        #endif
        #if ( ((USB_LOW_SPEED_DEVICE) != 0) && ((USB_LOW_SPEED_DEVICE) != 1) )
            #error "USB_LOW_SPEED_DEVICE must be set to either 0 or 1. Fix in USBConfig.h"
        #endif
        #if ( ((USB_FULL_SPEED_DEVICE) != 0) && ((USB_FULL_SPEED_DEVICE) != 1) )
            #error "USB_FULL_SPEED_DEVICE must be set to either 0 or 1. Fix in USBConfig.h"
        #endif
        #if ( ((USB_HI_SPEED_DEVICE) != 0) && ((USB_HI_SPEED_DEVICE) != 1) )
            #error "USB_HI_SPEED_DEVICE must be set to either 0 or 1. Fix in USBConfig.h"
        #endif
        #if ( ((USB_SELF_POWERED_DEVICE) != 0) && ((USB_SELF_POWERED_DEVICE) != 1) )
            #error "USB_SELF_POWERED_DEVICE must be set to either 0 or 1. Fix in USBConfig.h"
        #endif
        #if ( ((USB_USE_VBUS_DETECTION) != 0) && ((USB_USE_VBUS_DETECTION) != 1) )
            #error "USB_USE_VBUS_DETECTION must be set to either 0 or 1. Fix in USBConfig.h"
        #endif
        /* INSERT PIN CHECK FOR USB_VBUS_DETECT_GPIO HERE IF NEEDED */
        #if ( ((USB_USE_INTERNAL_OSCILLATOR) != 0) && ((USB_USE_INTERNAL_OSCILLATOR) != 1) )
            #error "USB_USE_INTERNAL_OSCILLATOR must be set to either 0 or 1. Fix in USBConfig.h"
        #endif
        #if ( ((USB_USE_EXTERNAL_OSCILLATOR) != 0) && ((USB_USE_EXTERNAL_OSCILLATOR) != 1) )
            #error "USB_USE_EXTERNAL_OSCILLATOR must be set to either 0 or 1. Fix in USBConfig.h"
        #endif
        #if ( ((USB_USE_EXTERNAL_OSCILLATOR) == 1) && ((USB_EXTERNAL_CLOCK_FREQUENCY) <= 0) )
            #error "USB_EXTERNAL_CLOCK_FREQUENCY must be greater than 0. Fix in USBConfig.h"
        #endif
        #if ( ((USB_CONTROL_ENDPOINT_SIZE) != 8) && ((USB_CONTROL_ENDPOINT_SIZE) != 16) && \
            ((USB_CONTROL_ENDPOINT_SIZE) != 32) && ((USB_CONTROL_ENDPOINT_SIZE) != 64) )
            #error "USB_CONTROL_ENDPOINT_SIZE must be 8, 16, 32, or 64. Fix in USBConfig.h"
        #endif



        /**
         * Mandatory definition in USBHIDConfig.h not included.
         */
        #if (!defined(HID_VERSION_))
            #error "HID_VERSION_ must be defined and set. Fix in USBHIDConfig.h"
        #endif
        #if (!defined(HID_ENDPOINT_NUMBER))
            #error "HID_ENDPOINT_NUMBER must be defined and set. Fix in USBHIDConfig.h"
        #endif
        #if (!defined(HID_ENDPOINT_SIZE))
            #error "HID_ENDPOINT_SIZE must be defined and set. Fix in USBHIDConfig.h"
        #endif



        /**
         * Invalid definition in USBHIDConfig.h
         */
        #if ( (HID_VERSION_) < 0x0100 )
            #error "HID_VERSION_ must be at least v1.0. Fix in USBHIDConfig.h"
        #endif
        #if ( (HID_ENDPOINT_NUMBER) <= 0 )
            #error "HID_ENDPOINT_NUMBER must be assigned to an Endpoint greater than 0. Fix in USBHIDConfig.h"
        #endif
        #if ( (HID_ENDPOINT_SIZE) <= 0 )
            #error "HID_ENDPOINT_SIZE must be greater than 0. Fix in USBHIDConfig.h"
        #endif



        /**
         * Target hardware and/or current codebase cannot support desired USB version in USBConfig.h 
         */
        #if ( (USB_VERSION_) > (CPU_SUPPORTED_USB_VERSION) )
            #error "USB_VERSION_ is greater than what the target CPU supports (CPU_SUPPORTED_USB_VERSION). Fix in USBConfig.h"
        #endif
        #if ( (USB_VERSION_) > (SOFTWARE_SUPPORTED_USB_VERSION) )
            #error "USB_VERSION_ is greater than what this codebase currently supports (SOFTWARE_SUPPORTED_USB_VERSION). Fix in USBConfig.h"
        #endif
        #if ( (HID_VERSION_) > (SOFTWARE_SUPPORTED_HID_VERSION) )
            #error "HID_VERSION_ is greater than what this codebase currently supports (SOFTWARE_SUPPORTED_HID_VERSION). Fix in USBHIDConfig.h"
        #endif



        /**
         * Check if target hardware can support current USB Configuration. USBConfig.h definitions 
         * compared against each other and against target in TargetSpecific.h.
         */
        #if ( (USB_CONTROL_ENDPOINT_SIZE) > (ENDPOINT0_MAX_FIFO_SIZE) )
            #error "USB_CONTROL_ENDPOINT_SIZE is greater than what the target can support (ENDPOINT0_MAX_FIFO_SIZE). Fix in USBConfig.h"
        #endif
        #if ( ((USB_LOW_SPEED_DEVICE) == 0) && ((USB_FULL_SPEED_DEVICE) == 0) && ((USB_HI_SPEED_DEVICE) == 0) )
            #error "USB_LOW_SPEED_DEVICE, USB_FULL_SPEED_DEVICE, or USB_HI_SPEED_DEVICE must be set to 1. Currently no speed setting is assigned. Fix in USBConfig.h"
        #endif
        #if ( ((USB_LOW_SPEED_DEVICE) == 1) && ((USB_FULL_SPEED_DEVICE) == 1) )
            #error "Only a single speed setting can be set to 1. Fix in USBConfig.h"
        #endif
        #if ( ((USB_LOW_SPEED_DEVICE) == 1) && ((USB_HI_SPEED_DEVICE) == 1) )
            #error "Only a single speed setting can be set to 1. Fix in USBConfig.h"
        #endif
        #if ( ((USB_FULL_SPEED_DEVICE) == 1) && ((USB_HI_SPEED_DEVICE) == 1) )
            #error "Only a single speed setting can be set to 1. Fix in USBConfig.h"
        #endif
        #if ( ((CAN_BE_USB_LOW_SPEED_DEVICE) == 0) && ((USB_LOW_SPEED_DEVICE) == 1) )
            #error "USB_LOW_SPEED_DEVICE set to 1 but target does not support this speed. Fix in USBConfig.h"
        #endif
        #if ( ((CAN_BE_USB_FULL_SPEED_DEVICE) == 0) && ((USB_FULL_SPEED_DEVICE) == 1) )
            #error "USB_FULL_SPEED_DEVICE set to 1 but target does not support this speed. Fix in USBConfig.h"
        #endif
        #if ( ((CAN_BE_USB_HI_SPEED_DEVICE) == 0) && ((USB_HI_SPEED_DEVICE) == 1) )
            #error "USB_HI_SPEED_DEVICE set to 1 but target does not support this speed. Fix in USBConfig.h"
        #endif
        #if ( ((USB_FULL_SPEED_DEVICE) == 1) && ((USB_VERSION_) < 0x0110) )
            #error "USB_FULL_SPEED_DEVICE set to 1 but USB_VERSION_ set to less than v1.1. Fix in USBConfig.h"
        #endif
        #if ( ((USB_HI_SPEED_DEVICE) == 1) && ((USB_VERSION_) < 0x0200) )
            #error "USB_HI_SPEED_DEVICE set to 1 but USB_VERSION_ set to less than v2.0. Fix in USBConfig.h"
        #endif
        #if ( ((USB_USE_INTERNAL_OSCILLATOR) == 1) && ((USB_USE_EXTERNAL_OSCILLATOR) == 1) )
            #error "USB_USE_INTERNAL_OSCILLATOR and USB_USE_EXTERNAL_OSCILLATOR are both set to 1. Must only use one. Fix in USBConfig.h"
        #endif
        #if ( ((USB_USE_INTERNAL_OSCILLATOR) == 0) && ((USB_USE_EXTERNAL_OSCILLATOR) == 0) )
            #error "USB_USE_INTERNAL_OSCILLATOR and USB_USE_EXTERNAL_OSCILLATOR are both set to 0. Must define a USB clock source. Fix in USBConfig.h"
        #endif
        #if ( ((USB_USE_INTERNAL_OSCILLATOR) == 1) && ((CAN_USE_USB_INTERNAL_OSCILLATOR) == 0) )
            #error "USB_USE_INTERNAL_OSCILLATOR set to 1 but target does not support this feature. Fix in USBConfig.h"
        #endif
        #if ( ((USB_USE_INTERNAL_OSCILLATOR) == 1) && ((USB_FULL_SPEED_DEVICE) == 1) )
            #error "Cannot use internal oscillator for USB Full Speed. Must use an external oscillator. Fix in USBConfig.h"
        #endif
        #if ( ((USB_USE_INTERNAL_OSCILLATOR) == 1) && ((USB_HI_SPEED_DEVICE) == 1) )
            #error "Cannot use internal oscillator for USB Hi-Speed. Must use an external oscillator. Fix in USBConfig.h"
        #endif
        #if ( ((USB_LOW_SPEED_DEVICE) == 1) && ((USB_CONTROL_ENDPOINT_SIZE) != 8) )
            #error "USB_CONTROL_ENDPOINT_SIZE must be 8 bytes for a Low Speed Device. Fix in USBConfig.h"
        #endif
        #if ( ((USB_FULL_SPEED_DEVICE) == 1) && ((USB_CONTROL_ENDPOINT_SIZE) != 8) && ((USB_CONTROL_ENDPOINT_SIZE) != 16) && \
            ((USB_CONTROL_ENDPOINT_SIZE) != 32) && ((USB_CONTROL_ENDPOINT_SIZE) != 64) )
            #error "USB_CONTROL_ENDPOINT_SIZE must be 8, 16, 32, or 64 bytes for Full Speed Device. Fix in USBConfig.h"
        #endif



        /**
         * USBHIDConfig.h definitions compared against USBConfig.h and TargetSpecific.h
         */
        #if ( ((USB_LOW_SPEED_DEVICE) == 1) && ((HID_ENDPOINT_SIZE) > 8) )
            #error "HID_ENDPOINT_SIZE must be 8 bytes or less for a Low Speed Device. Fix in USBHIDConfig.h"
        #endif
        #if ( ((USB_FULL_SPEED_DEVICE) == 1) && ((HID_ENDPOINT_SIZE) > 64) )
            #error "HID_ENDPOINT_SIZE must be 64 bytes or less for a Full Speed Device. Fix in USBHIDConfig.h"
        #endif
        #if (HID_ENDPOINT_NUMBER >= NUMBER_OF_USB_ENDPOINTS)
            #error "HID_ENDPOINT_NUMBER is greater than the number of endpoints supported by the target. Fix in USBHIDConfig.h"
        #endif



        /**
         * USB Configuration checks that are target-family specific.
         */
        #if (defined(ATMEGAXXU4_SERIES))
            #if ( ((USB_USE_EXTERNAL_OSCILLATOR) == 1) && ((USB_EXTERNAL_CLOCK_FREQUENCY) != 16000000) && ((USB_EXTERNAL_CLOCK_FREQUENCY) != 8000000) )
                #error "USB_EXTERNAL_CLOCK_FREQUENCY must be 8MHz or 16MHz for the current target to use an external oscillator. Fix in USBConfig.h"
            #endif
        #endif



        /**
         * Keyboard Configuration checks.
         */
        #if ((NUM_COLUMNS + NUM_ROWS) > NUMBER_OF_IO_PINS)
            #error "Target does not have enough I/O pins to support keyboard configuration in KeyboardConfig.h"
        #endif
        /* TODO: Try to add check for only valid GPIO pins are used. */

    #endif /* COMPILECHECKS_H */
#endif /* ONLY_INCLUDE_COMPILECHECKS_H_IN_COMPILECHECKS_C_ */
