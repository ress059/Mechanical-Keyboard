/** @file gpio.c
*
* @brief Basic GPIO driver for ATmega32U4. Author: Ian Ress
*
*/

#include <avr/io.h>

#include "gpio.h"

#ifdef __AVR_ATmega32U4__
static const gpio_reg_t gpio_reg[5] = 
{
    {&PINB, &DDRB, &PORTB},
    {&PINC, &DDRC, &PORTC},
    {&PIND, &DDRD, &PORTD},
    {&PINE, &DDRE, &PORTE},
    {&PINF, &DDRF, &PORTF}
};
#endif

/* TODO: verify that uint8_t var = (1U << pin) is OK */

/**
 * @brief Sets gpio pin as an input.
 * 
 * @param[in] index index in gpio_reg containing register address info.
 * @param[in] pin pin number.
 * 
 */
void gpio_set_input(uint8_t index, uint8_t pin) {
    *(gpio_reg[index].ddrx) &= (1U << pin);
}

/**
 * @brief Sets gpio pin as an output.
 * 
 * @param[in] index index in gpio_reg containing register address info.
 * @param[in] pin pin number.
 * 
 */
void gpio_set_output(uint8_t index, uint8_t pin) {
    *(gpio_reg[index].ddrx) |= (1U << pin);
}

/**
 * @brief Sets gpio pin as an input pullup.
 * 
 * @param[in] index index in gpio_reg containing register address info.
 * @param[in] pin pin number.
 * 
 */
void gpio_set_inputpullup(uint8_t index, uint8_t pin) {
    *(gpio_reg[index].ddrx) &= (1U << pin);
    *(gpio_reg[index].portx) |= (1U << pin);
}

/**
 * @brief Outputs a LOW signal on the gpio pin.
 * 
 * @param[in] index index in gpio_reg containing register address info.
 * @param[in] pin pin number.
 * 
 */
void gpio_output_low(uint8_t index, uint8_t pin) {
    *(gpio_reg[index].portx) &= (1U << pin);
}

/**
 * @brief Outputs a HIGH signal on the gpio pin.
 * 
 * @param[in] index index in GPIO_ATMEGA32U4_REG containing register address info.
 * @param[in] pin pin number.
 * 
 */
void gpio_output_high(uint8_t index, uint8_t pin) {
    *(gpio_reg[index].portx) |= (1U << pin);
}

/**
 * @brief Reads the status of the gpio pin.
 * 
 * @param[in] index index in gpio_reg containing register address info.
 * @param[in] pin pin number.
 * 
 * @return 1 if HIGH, 0 if LOW.
 */
uint8_t gpio_read(uint8_t index, uint8_t pin) {
    return (*(gpio_reg[index].pinx) & (1U << pin));
}
