/** @file avr_arch.h
*
* @brief AVR microcontrollers are either 8-bit, 16-bit, or 32-bit machines. Therefore the size of the return 
* type when reading registers will be different based on the microcontroller target. When 
* registers must be accessed in the application code, the data type definitions in this file should 
* be used instead of the ones defined in <stdint.h>. This file will determine at compile time whether
* a uint8_t, uint16_t, or uint32_t datatype should be used based on preprocessor defines handled by AVR GCC.
* Therefore if the build target changes at any point, the data types used when accessing registers
* will automatically be adjusted with no changes in the application code required. The microcontroller
* is defined with the -mmcu= compiler flag. When a microcontroller target is selected and compiled in
* Atmel Studio, this is automatically inputted. 
*
* If a new microcontroller is ever used it must be added into a define correlating to its word size.
*
* Author: Ian Ress
*
*/

#ifndef AVR_ARCH_H
#define AVR_ARCH_H

#include <stdint.h>


/* 8-bit machines */
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATxmega64B3__) /* ADD 8-BIT MACHINES HERE */
    typedef AVR_reg_t uint8_t;

/* 16-bit machines */
// #elif defined() /* ADD 16-BIT MACHINES HERE */
    // typedef AVR_reg_t uint16_t;

/* 32-bit machines */
// #elif defined() /* ADD 32-BIT MACHINES HERE */
    // typedef AVR_reg_t uint32_t;

/* Supported target not selected or -mmcu flag not given to compiler. */
#else
    #error "Target microcontroller unsupported at this time."
#endif

#endif /* AVR_ARCH_H */