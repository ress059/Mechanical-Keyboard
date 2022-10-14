/** @file gpio_atxmega64b3.h
*
* @brief Basic GPIO driver for AVR. Author: Ian Ress
*
*/ 

#ifndef GPIO_ATXMEGA64B3_H
#define GPIO_ATXMEGA64B3_H

#if !defined(MCU_DRIVERS_INCLUDED)
	#error "Do not include this file directly. Include mcu_drivers.h instead."
#endif

#include <stdint.h>

#define PORTB_INDEX                     0
#define PORTC_INDEX                     1
#define PORTD_INDEX                     2
#define PORTG_INDEX                     3
#define PORTM_INDEX                     4

#define PIN0_MASK					    (1U << 0)
#define PIN1_MASK					    (1U << 1)
#define PIN2_MASK					    (1U << 2)
#define PIN3_MASK					    (1U << 3)
#define PIN4_MASK					    (1U << 4)
#define PIN5_MASK					    (1U << 5)
#define PIN6_MASK					    (1U << 6)
#define PIN7_MASK					    (1U << 7)

/* #define Pin                          {Index in port address table (see gpio.h), Pin mask} */ 
#define PIN_PB0                         {PORTB_INDEX, (PIN0_MASK)}                       
#define PIN_PB1     					{PORTB_INDEX, (PIN1_MASK)}
#define PIN_PB2     					{PORTB_INDEX, (PIN2_MASK)}
#define PIN_PB3     					{PORTB_INDEX, (PIN3_MASK)}
#define PIN_PB4     					{PORTB_INDEX, (PIN4_MASK)}
#define PIN_PB5     					{PORTB_INDEX, (PIN5_MASK)}
#define PIN_PB6     					{PORTB_INDEX, (PIN6_MASK)}
#define PIN_PB7     					{PORTB_INDEX, (PIN7_MASK)}

#define PIN_PC0     					{PORTC_INDEX, (PIN0_MASK)}
#define PIN_PC1     					{PORTC_INDEX, (PIN1_MASK)}
#define PIN_PC2     					{PORTC_INDEX, (PIN2_MASK)}
#define PIN_PC3     					{PORTC_INDEX, (PIN3_MASK)}
#define PIN_PC4     					{PORTC_INDEX, (PIN4_MASK)}
#define PIN_PC5     					{PORTC_INDEX, (PIN5_MASK)}
#define PIN_PC6     					{PORTC_INDEX, (PIN6_MASK)}
#define PIN_PC7     					{PORTC_INDEX, (PIN7_MASK)}

#define PIN_PD0     					{PORTD_INDEX, (PIN0_MASK)}
#define PIN_PD1     					{PORTD_INDEX, (PIN1_MASK)}

#define PIN_PG0                         {PORTG_INDEX, (PIN0_MASK)}                       
#define PIN_PG1     					{PORTG_INDEX, (PIN1_MASK)}
#define PIN_PG2     					{PORTG_INDEX, (PIN2_MASK)}
#define PIN_PG3     					{PORTG_INDEX, (PIN3_MASK)}
#define PIN_PG4     					{PORTG_INDEX, (PIN4_MASK)}
#define PIN_PG5     					{PORTG_INDEX, (PIN5_MASK)}
#define PIN_PG6     					{PORTG_INDEX, (PIN6_MASK)}
#define PIN_PG7     					{PORTG_INDEX, (PIN7_MASK)}

#define PIN_PM0                         {PORTM_INDEX, (PIN0_MASK)}                       
#define PIN_PM1     					{PORTM_INDEX, (PIN1_MASK)}
#define PIN_PM2     					{PORTM_INDEX, (PIN2_MASK)}
#define PIN_PM3     					{PORTM_INDEX, (PIN3_MASK)}
#define PIN_PM4     					{PORTM_INDEX, (PIN4_MASK)}
#define PIN_PM5     					{PORTM_INDEX, (PIN5_MASK)}
#define PIN_PM6     					{PORTM_INDEX, (PIN6_MASK)}
#define PIN_PM7     					{PORTM_INDEX, (PIN7_MASK)}

typedef struct {
	uint8_t port_index;
    uint8_t pin_mask;
} pin_map_t;

/* ATXMEGA64B3 has SET and CLR registers (e.g. OUTSET, OUTCLR). These perform register
writes via hardware with a single atomic instruction instead of a read-modify-write. The original
plan was to use this (and make the code more bloated) for context switching safety. However
this is now not necessary since AVR-GCC compiler automatically saves the MCU context before 
being pre-empted. */
typedef struct {
	volatile uint8_t * const dirx;
	volatile uint8_t * const outx;
	volatile uint8_t * const inx;
} gpio_reg_t;

void gpio_set_input(uint8_t index, uint8_t mask);
void gpio_set_output(uint8_t index, uint8_t mask);
void gpio_output_low(uint8_t index, uint8_t mask);
void gpio_output_high(uint8_t index, uint8_t mask);
void gpio_toggle(uint8_t index, uint8_t mask);
uint8_t gpio_read(uint8_t index, uint8_t mask);

#endif /* GPIO_ATXMEGA64B3_H */
