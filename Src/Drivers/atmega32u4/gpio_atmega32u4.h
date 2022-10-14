/** @file gpio_atmega32u4.h
*
* @brief Basic GPIO driver for AVR. Author: Ian Ress
*
*/ 

#ifndef GPIO_ATMEGA32U4_H
#define GPIO_ATMEGA32U4_H

// #if !defined(__MCU_DRIVERS_INCLUDED)
// 	#error "Do not include this file directly. Include mcu_drivers.h instead."
// #endif

#include <stdint.h>

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

/* #define Pin                          {Index in port address table (see gpio.c), Pin mask} */ 
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

typedef struct {
	uint8_t port_index;
    uint8_t pin_mask;
} pin_map_t;

typedef struct {
	volatile uint8_t * const ddrx;
	volatile uint8_t * const portx;
	volatile uint8_t * const pinx;
} gpio_reg_t;

void gpio_set_input(uint8_t index, uint8_t mask);
void gpio_set_output(uint8_t index, uint8_t mask);
void gpio_output_low(uint8_t index, uint8_t mask);
void gpio_output_high(uint8_t index, uint8_t mask);
void gpio_toggle(uint8_t index, uint8_t mask);
uint8_t gpio_read(uint8_t index, uint8_t mask);

#endif /* GPIO_ATMEGA32U4_H */
