/** @file gpio_atmega32u4.h
*
* @brief Basic GPIO driver for AVR. Author: Ian Ress
*
*/ 

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/* ATXMEGA64B3 has SET and CLR registers (e.g. OUTSET, OUTCLR). These perform register
writes via hardware with a single atomic instruction instead of a read-modify-write. The original
plan was to use this (and make the code more bloated) for context switching safety. However
this is now not necessary since AVR-GCC compiler automatically saves the MCU context before 
being pre-empted. */
typedef struct {
	volatile uint8_t * const dirx;
	volatile uint8_t * const outx;
	volatile uint8_t * const inx;
} gpio_reg_t;

void gpio_set_input(uint8_t index, uint8_t mask);
void gpio_set_output(uint8_t index, uint8_t mask);
void gpio_output_low(uint8_t index, uint8_t mask);
void gpio_output_high(uint8_t index, uint8_t mask);
void gpio_toggle(uint8_t index, uint8_t mask);
uint8_t gpio_read(uint8_t index, uint8_t mask);

#endif /*GPIO_H*/
