/**
 * @file DeviceSpecific.h
 * 
 * \brief USB capabilities, instruction sets, registers, etc will depend on which MCU is used. 
 * This file is used to determine device-dependent parameters at compile-time. The goal is to
 * contain all device-specific code within this file and in the MCU specific drivers. So if 
 * a new device is ever added, only this file and the MCU's basic hardware peripheral drivers
 * need to be changed. The USB stack and application code should not have to be altered.
 * 
 * The user must pass the target device name into the -mmcu flag. For example for an ATMega32U4
 * -mmcu=atmega32u4.
 * 
 */

#ifndef DEVICESPECIFIC_H
#define DEVICESPECIFIC_H

#include <stdint.h>

#if defined(__DOXYGEN__)
    /* TODO: Add member group for all required defines */

    /* TODO: Add member group for all possible defines depending on MCU. */

/* TODO: Add JTAGEnable() and JTAGDisable() functions? */
#elif defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__)
    /**
     * \brief CPU wordsize.
     * 
     */
    typedef uint8_t AVR_reg_t;

    /**
     * \brief Target MCU is Little Endian
     * 
     */
    #define AVR_LITTLE_ENDIAN
    
    /**
     * \brief ATMega16U4 and ATMega32U4 microcontrollers. 
     * 
     */
    #define AVR_DEVICE_FAMILY1

    /**
     * \brief Number of General Purpose I/O pins.
     * 
     */
    #define NUMBER_OF_IO_PINS                           26

    /**
     * \brief Number of endpoint addresses including Endpoint 0. 
     * 
     * \note Each endpoint includes an IN and OUT endpoint. E.g. If NUMBER_OF_USB_ENDPOINTS 
     * is 2, there are 2 IN endpoint banks and 2 OUT endpoint banks.
     * 
     */
    #define NUMBER_OF_USB_ENDPOINTS                     7

    /**
     * \brief Maximum size, in bytes, that the Endpoint 0 bank can be programmed to.
     * 
     */
    #define ENDPOINT0_MAX_FIFO_SIZE                     64

    /**
     * \brief The MCU's USB controller has an internal regulator that can be enabled/disabled.
     * 
     */
    #define HAS_USB_INTERNAL_REGULATOR

    /**
     * \brief The MCU can be configured as a USB Low Speed Device.
     * 
     */
    #define CAN_BE_USB_LOW_SPEED_DEVICE

    /**
     * \brief The MCU can be configured as a USB High Speed Device.
     * 
     */
    #define CAN_BE_USB_FULL_SPEED_DEVICE

    /**
     * \brief The MCU's USB Controller can be driven using an internal clock. 
     * External crystal is not needed.
     * 
     */
    #define CAN_USE_USB_INTERNAL_CLOCK

#elif defined(__AVR_ATmega8U2__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega32U2__)
    /**
     * \brief CPU wordsize.
     * 
     */
    typedef uint8_t AVR_reg_t;
    
    /**
     * \brief Target MCU is Little Endian
     * 
     */
    #define AVR_LITTLE_ENDIAN

    /**
     * \brief ATMega8U2, ATMega16U2, and ATMega32U2 microcontrollers. 
     * 
     */
    #define AVR_DEVICE_FAMILY2

    /**
     * \brief Number of General Purpose I/O pins.
     * 
     */
    #define NUMBER_OF_IO_PINS                           22

    /**
     * \brief Number of endpoint addresses including Endpoint 0. 
     * 
     * \note Each endpoint includes an IN and OUT endpoint. E.g. If NUMBER_OF_USB_ENDPOINTS 
     * is 2, there are 2 IN endpoint banks and 2 OUT endpoint banks.
     * 
     */
    #define NUMBER_OF_USB_ENDPOINTS                     5

    /**
     * \brief The MCU can be configured as a USB High Speed Device.
     * 
     */
    #define CAN_BE_USB_FULL_SPEED_DEVICE

#elif defined(__AVR_ATxmega64B3__) || defined(__AVR_ATxmega128B3__)
    /**
     * \brief CPU wordsize. These microcontrollers use 8/16bit architecture (not sure why..) however wordsize
     * is set to 8-bits since all Memory Mapped I/O peripherals are 8-bit registers.
     * 
     */
    typedef uint8_t AVR_reg_t;

    /**
     * \brief Target MCU is Little Endian
     * 
     */
    #define AVR_LITTLE_ENDIAN

    /**
     * \brief ATxmega128B3 and ATxmega64B3 microcontrollers. 
     * 
     */
    #define AVR_DEVICE_FAMILY3

    /**
     * \brief Number of General Purpose I/O pins.
     * 
     */
    #define NUMBER_OF_IO_PINS                           36

    /**
     * \brief Number of endpoint addresses including Endpoint 0. 
     * 
     * \note Each endpoint includes an IN and OUT endpoint. E.g. If NUMBER_OF_USB_ENDPOINTS 
     * is 2, there are 2 IN endpoint banks and 2 OUT endpoint banks.
     * 
     */
    #define NUMBER_OF_USB_ENDPOINTS                     16

    /**
     * \brief The MCU can be configured as a USB Low Speed Device.
     * 
     */
    #define CAN_BE_USB_LOW_SPEED_DEVICE

    /**
     * \brief The MCU can be configured as a USB High Speed Device.
     * 
     */
    #define CAN_BE_USB_FULL_SPEED_DEVICE
    
#else
    #error "Selected MCU is currently unsupported or -mmcu flag was not set."
#endif


#endif /* DEVICESPECIFIC_H */