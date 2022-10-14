/** @file mcu_drivers.h
*
* @brief Master include file for all MCU specific low-level drivers. This file should be included
* directly whenever MCU peripherals are needed. Include this file instead of directly including
* the MCU driver. E.g. #include "mcu_drivers.h" instead of #include "../Drivers/atmega32u4/gpio_atmega32u4.h"
* Author: Ian Ress
*
*/ 

#ifndef MCU_DRIVERS_H
#define MCU_DRIVERS_H

// #define MCU_DRIVERS_INCLUDED

#if defined (__AVR_ATmega32U4__)
    #include "Drivers/atmega32u4/gpio_atmega32u4.h"
    #include "Drivers/atmega32u4/timer_atmega32u4.h"

#elif defined (__AVR_ATxmega64B3__)
    #include "Drivers/atxmega64b3/gpio_atxmega64b3.h"

#else
    #error "Unsupported MCU."
#endif

#endif /* MCU_DRIVERS_H */