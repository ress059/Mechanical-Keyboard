/**
 * @file Gpio.c
 * @author Ian Ress
 * @brief Basic GPIO driver for ATxMega64B3. See Gpio.h for full description.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Gpio.h"

static gpioreg_t * const gpio[5] = 
{
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOG,
    GPIOM
};

/**
 * @brief Sets gpio pin as an input. External pullups are used for ATXMEGA64B3 PCB.
 * 
 * @param pin pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 */
void gpio_set_input(pinmap_t pin) 
{
    gpio[pin.index]->DIR &= ~pin.mask;
}

/**
 * @brief Sets gpio pin as an output.
 * 
 * @param pin pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 */
void gpio_set_output(pinmap_t pin) 
{
    gpio[pin.index]->DIR |= pin.mask;
}

/**
 * @brief Outputs a LOW signal on the gpio pin. gpio_set_output() must be called once beforehand.
 * 
 * @param pin pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 */
void gpio_output_low(pinmap_t pin) 
{
    gpio[pin.index]->OUT &= ~pin.mask;
}

/**
 * @brief Outputs a HIGH signal on the gpio pin. gpio_set_output() must be called once beforehand.
 * 
 * @param pin pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 */
void gpio_output_high(pinmap_t pin) 
{
    gpio[pin.index]->OUT |= pin.mask;
}

/**
 * @brief Outputs LOW signal if the gpio is previously outputting HIGH and vise versa.
 * gpio_set_output() must be called once beforehand.
 * 
 * @param pin pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 */
void gpio_toggle(pinmap_t pin) 
{
    gpio[pin.index]->OUT ^= pin.mask;
}

/**
 * @brief Reads the status of the gpio pin.
 * 
 * @param pin pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 * @return 1 if LOW (pressed), 0 if HIGH.
 * 
 */
uint8_t gpio_read(pinmap_t pin) 
{
    return (!(gpio[pin.index]->IN & pin.mask));
}
