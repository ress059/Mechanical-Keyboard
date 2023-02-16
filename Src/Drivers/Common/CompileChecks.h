/**
 * @file CompileChecks.h
 * @author Ian Ress
 * @brief Solely used for compile-time checks. CompilerChecks.h/.c is meant to be compiled in 
 * its own translation unit, never being included in any other source/header file.
 * @date 2023-02-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef COMPILECHECKS_H
#define COMPILECHECKS_H

#include "DeviceSpecific.h"
#include "USBConfig.h"
#include "KeyboardConfig.h"

/* Mandatory definitions in DeviceSpecific.h not included for the target MCU. */
#if (!(defined(AVR_BIG_ENDIAN) || defined(AVR_LITTLE_ENDIAN))) || \
        (!(defined(CAN_BE_USB_LOW_SPEED_DEVICE) || defined(CAN_BE_USB_FULL_SPEED_DEVICE))) || \
        (!defined(NUMBER_OF_IO_PINS)) || \
        (!defined(NUMBER_OF_USB_ENDPOINTS))
    #error "Target microcontroller does not have one of the above definitions."
#endif

/* USB Configuration checks. USBConfig.h definitions compared against target MCU in DeviceSpecific.h */
#if !defined(HAS_USB_INTERNAL_REGULATOR) && defined(USB_USE_INTERNAL_REGULATOR) || \
    (defined(USB_FULLSPEED_DEVICE) && defined(USB_LOWSPEED_DEVICE)) || \
    !(defined(USB_FULLSPEED_DEVICE) && defined(USB_LOWSPEED_DEVICE))
    #error "USB configuration created in USBConfig.h is not possible with target MCU."
#endif


/* Keyboard Configuration checks. */
#if ((NUM_COLUMNS + NUM_ROWS) > NUMBER_OF_IO_PINS) /* TODO: Try to add check for only valid GPIO pins are used. */
    #error "Target MCU does not have enough I/O pins to support keyboard configuration in KeyboardConfig.h"
#endif

#endif /* COMPILECHECKS_H */