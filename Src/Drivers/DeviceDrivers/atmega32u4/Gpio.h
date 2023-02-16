/**
 * @file Gpio.h
 * @author Ian Ress
 * @brief Basic GPIO driver for ATMega32U4. Pins specific to the microcontroller are declared here
 * as a pinmap_t type. The pinmap_t struct contains two members:
 * 
 * 1) index = index in the gpio array defined in gpio.c. This array contains the base address
 * of each GPIO port. So this maps each pin to the correct memory mapped I/O port address 
 * (port B, port C, etc.)
 * 
 * 2) mask. AVR does not have a barrel shifter so storing each pin's pin mask at compile time
 * saves clock cycles whenever the gpio driver is used.
 * 
 * Declaring the pins this way makes it easy for the end user to define the column/row pins of
 * their keyboard in userconfig.h, while abstracting away the lower-level info needed for the gpio
 * driver. E.g. 
 * #define ROW_PINS 			{PIN_PD0, PIN_PD1, PIN_PD2, PIN_PD3}.
 * 
 * The application code can then use these keyboard pins whenever the gpio driver is called. 
 * Therefore the keyboard settings in userconfig.h and application code are microcontroller-agnostic. 
 * Only the gpio driver needs to be changed for each AVR microcontroller. It should also be noted that 
 * the user will get a compiler error if an invalid pin is used (pin that doesn't exist/can't be used 
 * for their microcontroller won't be declared in gpio.h).
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef struct {
	uint8_t index;
	uint8_t mask;
} pinmap_t;

typedef struct {
	volatile uint8_t PINx;
	volatile uint8_t DDRx;
	volatile uint8_t PORTx;
} gpioreg_t;

/* ATMega32U4 gpio registers. See ATMega32U4 datasheet chapter 31. */
#define GPIOB							((gpioreg_t *) ((uint8_t)0x23))
#define GPIOC							((gpioreg_t *) ((uint8_t)0x26))
#define GPIOD							((gpioreg_t *) ((uint8_t)0x29))
#define GPIOE							((gpioreg_t *) ((uint8_t)0x2C))
#define GPIOF							((gpioreg_t *) ((uint8_t)0x2F))

/* MCU specific pinouts */
#define PORTB_INDEX                     0
#define PORTC_INDEX                     1
#define PORTD_INDEX                     2
#define PORTE_INDEX                     3
#define PORTF_INDEX                     4

#define PIN0_MASK					    (1U << 0)
#define PIN1_MASK					    (1U << 1)
#define PIN2_MASK					    (1U << 2)
#define PIN3_MASK					    (1U << 3)
#define PIN4_MASK					    (1U << 4)
#define PIN5_MASK					    (1U << 5)
#define PIN6_MASK					    (1U << 6)
#define PIN7_MASK					    (1U << 7)

/* #define Pin                          {Index in gpio array (see gpio.c), Pin mask} */ 
#define PIN_PB0                         {PORTB_INDEX, (PIN0_MASK)}                       
#define PIN_PB1     					{PORTB_INDEX, (PIN1_MASK)}
#define PIN_PB2     					{PORTB_INDEX, (PIN2_MASK)}
#define PIN_PB3     					{PORTB_INDEX, (PIN3_MASK)}
#define PIN_PB4     					{PORTB_INDEX, (PIN4_MASK)}
#define PIN_PB5     					{PORTB_INDEX, (PIN5_MASK)}
#define PIN_PB6     					{PORTB_INDEX, (PIN6_MASK)}
#define PIN_PB7     					{PORTB_INDEX, (PIN7_MASK)}

#define PIN_PC6     					{PORTC_INDEX, (PIN6_MASK)}
#define PIN_PC7     					{PORTC_INDEX, (PIN7_MASK)}

#define PIN_PD0     					{PORTD_INDEX, (PIN0_MASK)}
#define PIN_PD1     					{PORTD_INDEX, (PIN1_MASK)}
#define PIN_PD2     					{PORTD_INDEX, (PIN2_MASK)}
#define PIN_PD3     					{PORTD_INDEX, (PIN3_MASK)}
#define PIN_PD4     					{PORTD_INDEX, (PIN4_MASK)}
#define PIN_PD5     					{PORTD_INDEX, (PIN5_MASK)}
#define PIN_PD6     					{PORTD_INDEX, (PIN6_MASK)}
#define PIN_PD7     					{PORTD_INDEX, (PIN7_MASK)}

#define PIN_PE2     					{PORTE_INDEX, (PIN2_MASK)}
#define PIN_PE6     					{PORTE_INDEX, (PIN6_MASK)}

#define PIN_PF0     					{PORTF_INDEX, (PIN0_MASK)}
#define PIN_PF1     					{PORTF_INDEX, (PIN1_MASK)}
#define PIN_PF4     					{PORTF_INDEX, (PIN4_MASK)}
#define PIN_PF5     					{PORTF_INDEX, (PIN5_MASK)}
#define PIN_PF6     					{PORTF_INDEX, (PIN6_MASK)}
#define PIN_PF7     					{PORTF_INDEX, (PIN7_MASK)}

void gpio_set_input(pinmap_t pin);
void gpio_set_output(pinmap_t pin);
void gpio_output_low(pinmap_t pin);
void gpio_output_high(pinmap_t pin);
void gpio_toggle(pinmap_t pin);
uint8_t gpio_read(pinmap_t pin);

#endif /* GPIO_H */
