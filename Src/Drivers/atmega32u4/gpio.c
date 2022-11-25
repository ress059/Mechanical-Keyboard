/** @file gpio.c
*
* @brief Basic GPIO driver for ATMega32U4. See gpio.h for full description.
*
* Author: Ian Ress
*
*/

#include "gpio.h"

static gpioreg_t * const gpio[5] = 
{
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOF
};

/**
 * @brief Sets gpio pin as an input pullup. Example call: gpio_set_input(PIN_PD2);
 * 
 * @param[in] pin pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 */
void gpio_set_input(pinmap_t pin) 
{
    gpio[pin.index]->DDRx &= ~pin.mask;
    gpio[pin.index]->PORTx |= pin.mask;
}

/**
 * @brief Sets gpio pin as an output. Example call: gpio_set_output(PIN_PD2);
 * 
 * @param[in] pin pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 */
void gpio_set_output(pinmap_t pin) 
{
    gpio[pin.index]->DDRx |= pin.mask;
}

/**
 * @brief Outputs a LOW signal on the gpio pin. gpio_set_output() must be called once beforehand.
 * Example call: gpio_output_low(PIN_PD2);
 * 
 * @param[in] pin pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 */
void gpio_output_low(pinmap_t pin) 
{
    gpio[pin.index]->PORTx &= ~pin.mask;
}

/**
 * @brief Outputs a HIGH signal on the gpio pin. gpio_set_output() must be called once beforehand.
 * Example call: gpio_output_high(PIN_PD2);
 * 
 * @param[in] pin pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 */
void gpio_output_high(pinmap_t pin) 
{
    gpio[pin.index]->PORTx |= pin.mask;
}

/**
 * @brief Outputs LOW signal if the gpio is previously outputting HIGH and vise versa.
 * gpio_set_output() must be called once beforehand. Example call: gpio_toggle(PIN_PD2);
 * 
 * @param[in] pin pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 */
void gpio_toggle(pinmap_t pin) 
{
    gpio[pin.index]->PORTx ^= pin.mask;
}

/**
 * @brief Reads the status of the gpio pin. Example call: uint8_t val = gpio_read(PIN_PD2);
 * 
 * @param[in] pin pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 * @return 1 if LOW (pressed), 0 if HIGH.
 * 
 */
uint8_t gpio_read(pinmap_t pin) 
{
    return (!(gpio[pin.index]->PINx & pin.mask));
}
