/** @file gpio_atmega32u4.c
*
* @brief Basic GPIO driver for AVR. Author: Ian Ress
*
*/

#include "gpio_atmega32u4.h"

#include <avr/io.h>

static const gpio_reg_t gpio_reg[5] = 
{
    {&DDRB, &PORTB, &PINB},
    {&DDRC, &PORTC, &PINC},
    {&DDRD, &PORTD, &PIND},
    {&DDRE, &PORTE, &PINE},
    {&DDRF, &PORTF, &PINF}
};

/**
 * @brief Sets gpio pin as an input pullup.
 * 
 * @param[in] index index in gpio_reg containing memory mapped I/O address.
 * @param[in] mask  pin mask.
 * 
 */
void gpio_set_input(uint8_t index, uint8_t mask) 
{
    *(gpio_reg[index].ddrx) &= ~mask;
    *(gpio_reg[index].portx) |= mask;
}

/**
 * @brief Sets gpio pin as an output.
 * 
 * @param[in] index index in gpio_reg containing memory mapped I/O address.
 * @param[in] mask  pin mask.
 * 
 */
void gpio_set_output(uint8_t index, uint8_t mask) 
{
    *(gpio_reg[index].ddrx) |= mask;
}

/**
 * @brief Outputs a LOW signal on the gpio pin. gpio_set_output() must be called once beforehand.
 * 
 * @param[in] index index in gpio_reg containing memory mapped I/O address.
 * @param[in] mask  pin mask.
 * 
 */
void gpio_output_low(uint8_t index, uint8_t mask) 
{
    *(gpio_reg[index].portx) &= ~mask;
}

/**
 * @brief Outputs a HIGH signal on the gpio pin. gpio_set_output() must be called once beforehand.
 * 
 * @param[in] index index in gpio_reg containing memory mapped I/O address.
 * @param[in] mask  pin mask.
 * 
 */
void gpio_output_high(uint8_t index, uint8_t mask) 
{
    *(gpio_reg[index].portx) |= mask;
}

/**
 * @brief Outputs LOW signal if the gpio is previously outputting HIGH and vise versa.
 * gpio_set_output() must be called once beforehand.
 * 
 * @param[in] index index in gpio_reg containing memory mapped I/O address.
 * @param[in] mask  pin mask.
 * 
 */
void gpio_toggle(uint8_t index, uint8_t mask) 
{
    *(gpio_reg[index].portx) ^= mask;
}

/**
 * @brief Reads the status of the gpio pin.
 * 
 * @param[in] index index in gpio_reg containing memory mapped I/O address.
 * @param[in] mask  pin mask.
 * 
 * @return 1 if LOW (pressed), 0 if HIGH.
 */
uint8_t gpio_read(uint8_t index, uint8_t mask) 
{
    return (!(*(gpio_reg[index].pinx) & mask));
}
