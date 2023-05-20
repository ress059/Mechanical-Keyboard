/**
 * @file gpio.c
 * @author Ian Ress
 * @brief Basic GPIO driver for ATxMega64B3. See gpio.h for full description.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "gpio.h"

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
 * @param pin Pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 */
void GPIO_Set_Input(Pinmap_t pin) 
{
    gpio[pin.index]->DIR &= ~pin.mask;
}

/**
 * @brief Sets gpio pin as an output.
 * 
 * @param pin Pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 */
void GPIO_Set_Output(Pinmap_t pin) 
{
    gpio[pin.index]->DIR |= pin.mask;
}

/**
 * @brief Outputs a LOW signal on the gpio pin. GPIO_Set_Output() must be called once beforehand.
 * 
 * @param pin Pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 */
void GPIO_Output_Low(Pinmap_t pin) 
{
    gpio[pin.index]->OUT &= ~pin.mask;
}

/**
 * @brief Outputs a HIGH signal on the gpio pin. GPIO_Set_Output() must be called once beforehand.
 * 
 * @param pin Pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 */
void GPIO_Output_High(Pinmap_t pin) 
{
    gpio[pin.index]->OUT |= pin.mask;
}

/**
 * @brief Outputs LOW signal if the gpio is previously outputting HIGH and vise versa.
 * GPIO_Set_Output() must be called once beforehand.
 * 
 * @param pin Pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 */
void GPIO_Toggle(Pinmap_t pin) 
{
    gpio[pin.index]->OUT ^= pin.mask;
}

/**
 * @brief Reads the status of the gpio pin.
 * 
 * @param pin Pinmap_t struct containing the pin's index in gpio array 
 * and it's pin mask.
 * 
 * @return 1 if LOW (pressed), 0 if HIGH.
 * 
 */
uint8_t GPIO_Read(Pinmap_t pin) 
{
    return (!(gpio[pin.index]->IN & pin.mask));
}
