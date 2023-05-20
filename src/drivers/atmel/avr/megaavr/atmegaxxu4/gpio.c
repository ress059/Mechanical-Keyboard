/**
 * @file gpio.c
 * @author Ian Ress
 * @brief Basic GPIO driver for ATMega32U4. See gpio.h for full description.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <avr/io.h> /* GPIO Register Memory Map */
#include "gpio.h"

/* ATMega32U4 gpio registers. See ATMega32U4 datasheet chapter 31. */
typedef struct
{
	volatile uint8_t * const PINx;
	volatile uint8_t * const DDRx;
	volatile uint8_t * const PORTx;
} GPIOReg_t;

static const GPIOReg_t GPIO[] = 
{
    {&PINB, &DDRB, &PORTB},
    {&PINC, &DDRC, &PORTC},
    {&PIND, &DDRD, &PORTD},
    {&PINE, &DDRE, &PORTE},
    {&PINF, &DDRF, &PORTF}
};

/**
 * @brief Sets GPIO pin as an input pullup. Example call: GPIO_Set_Input(PIN_PD2);
 * 
 * @param pin Pinmap_t struct containing the pin's index in GPIO array 
 * and it's pin mask.
 * 
 */
void GPIO_Set_Input(const Pinmap_t pin) 
{
    *(GPIO[pin.PortIndex].DDRx) &= ~pin.Mask;
    *(GPIO[pin.PortIndex].PORTx) |= pin.Mask;
}

/**
 * @brief Sets GPIO pin as an output. Example call: GPIO_Set_Output(PIN_PD2);
 * 
 * @param pin Pinmap_t struct containing the pin's index in GPIO array 
 * and it's pin mask.
 * 
 */
void GPIO_Set_Output(Pinmap_t pin) 
{
    *(GPIO[pin.PortIndex].DDRx) |= pin.Mask;
}

/**
 * @brief Outputs a LOW signal on the GPIO pin. GPIO_Set_Output() must be called once beforehand.
 * Example call: GPIO_Output_Low(PIN_PD2);
 * 
 * @param pin Pinmap_t struct containing the pin's index in GPIO array 
 * and it's pin mask.
 * 
 */
void GPIO_Output_Low(Pinmap_t pin) 
{
    *(GPIO[pin.PortIndex].PORTx) &= ~pin.Mask;
}

/**
 * @brief Outputs a HIGH signal on the GPIO pin. GPIO_Set_Output() must be called once beforehand.
 * Example call: GPIO_Output_High(PIN_PD2);
 * 
 * @param pin Pinmap_t struct containing the pin's index in GPIO array 
 * and it's pin mask.
 * 
 */
void GPIO_Output_High(Pinmap_t pin) 
{
    *(GPIO[pin.PortIndex].PORTx) |= pin.Mask;
}

/**
 * @brief Outputs LOW signal if the GPIO is previously outputting HIGH and vise versa.
 * GPIO_Set_Output() must be called once beforehand. Example call: GPIO_Toggle(PIN_PD2);
 * 
 * @param pin Pinmap_t struct containing the pin's index in GPIO array 
 * and it's pin mask.
 * 
 */
void GPIO_Toggle(Pinmap_t pin) 
{
    GPIO[pin.index]->PORTx ^= pin.mask;
}

/**
 * @brief Reads the status of the GPIO pin. Example call: bool val = GPIO_Read(PIN_PD2);
 * 
 * @param pin Pinmap_t struct containing the pin's index in GPIO array 
 * and it's pin mask.
 * 
 * @return true if LOW (pressed), false if HIGH.
 * 
 */
bool GPIO_Read(Pinmap_t pin) 
{
    return (!(GPIO[pin.index]->PINx & pin.mask));
}
