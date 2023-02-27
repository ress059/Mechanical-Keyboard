/**
 * @file CompileChecks.h
 * @author Ian Ress
 * \brief Solely used for compile-time checks. CompileChecks.h/.c is meant to be compiled in 
 * its own translation unit, never being included in any other source/header file.
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
        #include "DeviceSpecific.h"
        #include "KeyboardConfig.h"
        #include "USBConfig.h"


        /**
         * \brief Only used to check if the CPU wordsize in DeviceSpecific.h is
         * configured with a valid value. Never used.
         * 
         */
        static inline void AVR_CPU_Wordsize_Check(void) GCCATTRIBUTE_UNUSED;
        static inline void AVR_CPU_Wordsize_Check(void)
        {
            (void)sizeof(char[(2*(sizeof(AVR_reg_t))) - 1]);
        }


        /**
         * Mandatory definitions in DeviceSpecific.h not included for the target MCU.
         * 
         */
        #if (!defined(AVR_BIG_ENDIAN)) && (!defined(AVR_LITTLE_ENDIAN))
            #error "Target MCU's endianness is not defined. Fix in DeviceSpecific.h"
        #endif
        #if (!defined(CAN_BE_USB_LOW_SPEED_DEVICE)) && (!defined(CAN_BE_USB_FULL_SPEED_DEVICE))
            #error "Target MCU's USB speed capabilities is not defined. Fix in DeviceSpecific.h"
        #endif
        #if (!defined(NUMBER_OF_IO_PINS))
            #error "Number of I/O pins on target MCU is not defined. Fix in DeviceSpecific.h"
        #endif
        #if (!defined(NUMBER_OF_USB_ENDPOINTS))
            #error "Number of USB Endpoints on target MCU is not defined. Fix in DeviceSpecific.h"
        #endif
        #if (!defined(ENDPOINT0_MAX_FIFO_SIZE))
            #error "Endpoint 0 max FIFO size is not defined. Fix in DeviceSpecific.h"
        #endif



        /**
         * USB Configuration checks. USBConfig.h definitions compared against target MCU in DeviceSpecific.h.
         * 
         */
        #if (!defined(HAS_USB_INTERNAL_REGULATOR)) && (defined(USB_USE_INTERNAL_REGULATOR))
            #error "Configured to use USB internal regulator when target MCU does not have one. Fix in USBConfig.h."
        #endif
        #if (defined(USB_FULL_SPEED_DEVICE)) && (defined(USB_LOW_SPEED_DEVICE))
            #error "Configured to both USB Low Speed and USB Full Speed. Must only set one. Fix in USBConfig.h"
        #endif
        #if (!defined(USB_FULL_SPEED_DEVICE)) && (!defined(USB_LOW_SPEED_DEVICE))
            #error "USB Speed is not configured. Fix in USBConfig.h"
        #endif
        #if (!defined(CAN_BE_USB_LOW_SPEED_DEVICE)) && (defined(USB_LOW_SPEED_DEVICE))
            #error "Configured to USB Low Speed when target MCU does not support this. Fix in USBConfig.h"
        #endif
        #if (!defined(CAN_BE_USB_FULL_SPEED_DEVICE)) && (defined(USB_FULL_SPEED_DEVICE))
            #error "Configured to USB Full Speed when target MCU does not support this. Fix in USBConfig.h"
        #endif
        #if (defined(USB_USE_INTERNAL_OSCILLATOR)) && (defined(USB_USE_EXTERNAL_OSCILLATOR))
            #error "Configured to use both internal and external oscillator for USB. Must only set to one. Fix in USBConfig.h"
        #endif
        #if (!defined(USB_USE_INTERNAL_OSCILLATOR)) && (!defined(USB_USE_EXTERNAL_OSCILLATOR))
            #error "Clock source for USB is not configured. Fix in USBConfig.h"
        #endif
        #if (!defined(CAN_USE_USB_INTERNAL_CLOCK)) && (defined(USB_USE_INTERNAL_OSCILLATOR))
            #error "Configured to use internal oscillator for USB when target MCU does not support this. Fix in USBConfig.h"
        #endif
        #if (defined(USB_USE_INTERNAL_OSCILLATOR)) && (defined(USB_FULL_SPEED_DEVICE))
            #error "Cannot use internal oscillator for USB Full Speed. Fix in USBConfig.h"
        #endif
        #if (CONTROL_ENDPOINT_SIZE > ENDPOINT0_MAX_FIFO_SIZE)
            #error "Control Endpoint size is greater than maximum Endpoint 0 size the target MCU can support. Fix in USBConfig.h"
        #endif
        #if (CONTROL_ENDPOINT_SIZE < 0)
            #error "Assigned a negative value for Control Endpoint size. Fix in USBConfig.h"
        #endif
        #if (defined(USB_LOW_SPEED_DEVICE)) && (CONTROL_ENDPOINT_SIZE != 8)
            #error "Control Endpoint size must be 8 bytes for a Low Speed Device. Fix in USBConfig.h"
        #endif
        #if (defined(USB_FULL_SPEED_DEVICE)) && (CONTROL_ENDPOINT_SIZE != 8) && (CONTROL_ENDPOINT_SIZE != 16) && \
            (CONTROL_ENDPOINT_SIZE != 32) && (CONTROL_ENDPOINT_SIZE != 64)
            #error "Control Endpoint size must be 8, 16, 32, or 64 bytes for Full Speed Device. Fix in USBConfig.h"
        #endif
        #if (defined(USB_LOW_SPEED_DEVICE)) && (HID_ENDPOINT_SIZE > 8)
            #error "HID Endpoint size must be 8 bytes or less for a Low Speed Device. Fix in USBConfig.h"
        #endif
        #if (defined(USB_FULL_SPEED_DEVICE)) && (HID_ENDPOINT_SIZE > 64)
            #error "HID Endpoint size must be 64 bytes or less for a Full Speed Device. Fix in USBConfig.h"
        #endif
        #if (HID_ENDPOINT_SIZE < 0)
            #error "Assigned a negative value for HID Endpoint size. Fix in USBConfig.h"
        #endif
        #if (HID_ENDPOINT_NUMBER == 0)
            #error "Assigned HID Endpoint number to Endpoint 0. This is always reserved for Control Endpoint. Fix in USBConfig.h"
        #endif
        #if (HID_ENDPOINT_NUMBER < 0)
            #error "Assigned a negative value for HID Endpoint number. Fix in USBConfig.h"
        #endif
        #if (HID_ENDPOINT_NUMBER >= NUMBER_OF_USB_ENDPOINTS)
            #error "Selected HID Endpoint number is greater than the number of endpoints on target MCU. Fix in USBConfig.h"
        #endif



        /**
         * USB Configuration checks that are MCU specific.
         * 
         */
        #if (defined(AVR_DEVICE_FAMILY1)) && (defined(USB_USE_EXTERNAL_OSCILLATOR)) && \
            (USB_EXTERNAL_CLOCK_FREQUENCY != 16000000) && (USB_EXTERNAL_CLOCK_FREQUENCY != 8000000)
            #error "Configured to use external clock for USB. It must be 8MHz or 16MHz for selected target MCU. Fix in USBConfig.h"
        #endif



        /**
         * Keyboard Configuration checks.
         * 
         */
        #if ((NUM_COLUMNS + NUM_ROWS) > NUMBER_OF_IO_PINS)
            #error "Target MCU does not have enough I/O pins to support keyboard configuration in KeyboardConfig.h"
        #endif
        /* TODO: Try to add check for only valid GPIO pins are used. */

    #endif /* COMPILECHECKS_H */
#endif /* ONLY_INCLUDE_COMPILECHECKS_H_IN_COMPILECHECKS_C_ */
