/** @file gpio.h
*
* @brief Basic GPIO driver for ATmega32U4. Author: Ian Ress
*
*/ 

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef struct {
	volatile uint8_t * const pinx;
	volatile uint8_t * const ddrx;
	volatile uint8_t * const portx;
} gpio_reg_t;

void gpio_set_input(uint8_t index, uint8_t pin);
void gpio_set_output(uint8_t index, uint8_t pin);
void gpio_set_inputpullup(uint8_t index, uint8_t pin);
void gpio_output_low(uint8_t index, uint8_t pin);
void gpio_output_high(uint8_t index, uint8_t pin);
uint8_t gpio_read(uint8_t index, uint8_t pin);

#endif /*GPIO_H*/
