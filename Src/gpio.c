/** @file gpio.c
*
* @brief Basic GPIO driver for AVR. Author: Ian Ress
*
*/

#include "gpio.h"

#include <avr/io.h>

#if defined (__AVR_ATMEGA32U4__)
static const gpio_reg_t gpio_reg[5] = 
{
    {&DDRB, &PORTB, &PINB},
    {&DDRC, &PORTC, &PINC},
    {&DDRD, &PORTD, &PIND},
    {&DDRE, &PORTE, &PINE},
    {&DDRF, &PORTF, &PINF}
};

#elif defined (__AVR_ATXMEGA64B3__)
static const gpio_reg_t gpio_reg[7] =
{
    {&PORTB_DIR, &PORTB_OUT, &PORTB_IN},
    {&PORTC_DIR, &PORTC_OUT, &PORTC_IN},
    {&PORTD_DIR, &PORTD_OUT, &PORTD_IN},
    {0, 0, 0}, //no PORTE on ATXMEGA64B3
    {0, 0, 0}, //no PORTF on ATXMEGA64B3
    {&PORTG_DIR, &PORTG_OUT, &PORTG_IN},
    {&PORTM_DIR, &PORTM_OUT, &PORTM_IN}
};

#else
    #error "Unsupported MCU."
#endif

/**
 * @brief Sets gpio pin as an input pullup. External pullups are used for ATXMEGA64B3 PCB.
 * 
 * @param[in] index index in gpio_reg containing memory mapped I/O address.
 * @param[in] mask  pin mask.
 * 
 */
void gpio_set_input(uint8_t index, uint8_t mask) 
{
    *(gpio_reg[index].dirx) &= ~mask;
#if defined (__AVR_ATMEGA32U4__)
    *(gpio_reg[index].outx) |= mask;
#endif
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
    *(gpio_reg[index].dirx) |= mask;
}

/**
 * @brief Outputs a LOW signal on the gpio pin.
 * 
 * @param[in] index index in gpio_reg containing memory mapped I/O address.
 * @param[in] mask  pin mask.
 * 
 */
void gpio_output_low(uint8_t index, uint8_t mask) 
{
    *(gpio_reg[index].outx) &= ~mask;
}

/**
 * @brief Outputs a HIGH signal on the gpio pin.
 * 
 * @param[in] index index in gpio_reg containing memory mapped I/O address.
 * @param[in] mask  pin mask.
 * 
 */
void gpio_output_high(uint8_t index, uint8_t mask) 
{
    *(gpio_reg[index].outx) |= mask;
}

/**
 * @brief Outputs LOW signal if the gpio is previously outputting HIGH and vise versa.
 * 
 * @param[in] index index in gpio_reg containing memory mapped I/O address.
 * @param[in] mask  pin mask.
 * 
 */
void gpio_toggle(uint8_t index, uint8_t mask) 
{
    *(gpio_reg[index].outx) ^= mask;
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
    return (!(*(gpio_reg[index].inx) & mask));
}
