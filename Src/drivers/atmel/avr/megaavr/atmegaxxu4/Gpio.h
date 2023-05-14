/**
 * @file Gpio.h
 * @author Ian Ress
 * @brief Basic GPIO driver for ATMega32U4. Pins specific to the microcontroller are declared here
 * as a Pinmap_t type. The Pinmap_t struct contains two members:
 * 
 * 1) index = index in the gpio array defined in Gpio.c. This array contains the base address
 * of each GPIO port. So this maps each pin to the correct memory mapped I/O port address 
 * (port B, port C, etc.)
 * 
 * 2) mask. AVR does not have a barrel shifter so storing each pin's pin mask at compile time
 * saves clock cycles whenever the gpio driver is used.
 * 
 * Declaring the pins this way makes it easy for the end user to define the column/row pins of
 * their keyboard in KeyboardConfig.h, while abstracting away the lower-level info needed for the gpio
 * driver. E.g. 
 * #define ROW_PINS 			{PIN_PD0, PIN_PD1, PIN_PD2, PIN_PD3}.
 * 
 * The application code can then use these keyboard pins whenever the gpio driver is called. 
 * Therefore the keyboard settings in KeyboardConfig.h and the application code are 
 * microcontroller-agnostic. Only the gpio driver needs to be changed for each AVR microcontroller. 
 * It should also be noted that the user will get a compiler error if an invalid pin is used 
 * (pin that doesn't exist/can't be used for their microcontroller won't be declared in Gpio.h).
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	uint8_t PortIndex;
	uint8_t Mask;
} Pinmap_t;

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


void GPIO_Set_Input(const Pinmap_t pin);
void GPIO_Set_Output(const Pinmap_t pin);
void GPIO_Output_Low(const Pinmap_t pin);
void GPIO_Output_High(const Pinmap_t pin);
void GPIO_Toggle(const Pinmap_t pin);
bool GPIO_Read(const Pinmap_t pin); 	/* 	Only reads if individual pin is HIGH or LOW. Not returning bitmap of
											the entire port since separate MCUs will have different register sizes. 
											This will be called in the application so it needs to be microcontroller
											agnostic. We cannot have the return type of GPIO_Read() functions 
											return different sizes. E.g. Can't have GPIO_Read() of ATMega32U4 return
											uint8_t and GPIO_Read() for ATxMegaB return uint16_t */

#endif /* GPIO_H */
