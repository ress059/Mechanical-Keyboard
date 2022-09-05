/** @file pin_map.h
*
* @brief Maps pins to register address and pin mask. Author: Ian Ress
*
*/

#ifndef PIN_MAP_H
#define PIN_MAP_H

#include <stdint.h>

#define PORTB_INDEX                     0
#define PORTC_INDEX                     1
#define PORTD_INDEX                     2
#define PORTE_INDEX                     3
#define PORTF_INDEX                     4
#define PORTG_INDEX                     5
#define PORTM_INDEX                     6

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

#ifdef __AVR_ATXMEGA64B3__
#define PIN_PC0     					{PORTC_INDEX, (PIN0_MASK)}
#define PIN_PC1     					{PORTC_INDEX, (PIN1_MASK)}
#define PIN_PC2     					{PORTC_INDEX, (PIN2_MASK)}
#define PIN_PC3     					{PORTC_INDEX, (PIN3_MASK)}
#define PIN_PC4     					{PORTC_INDEX, (PIN4_MASK)}
#define PIN_PC5     					{PORTC_INDEX, (PIN5_MASK)}
#endif

#define PIN_PC6     					{PORTC_INDEX, (PIN6_MASK)}
#define PIN_PC7     					{PORTC_INDEX, (PIN7_MASK)}
#define PIN_PD0     					{PORTD_INDEX, (PIN0_MASK)}
#define PIN_PD1     					{PORTD_INDEX, (PIN1_MASK)}

#ifdef __AVR_ATMEGA32U4__
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
#endif

#ifdef __AVR_ATXMEGA64B3__
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
#endif

typedef struct {
	uint8_t port_index;
    uint8_t pin_mask;
} pin_map_t;

#endif /* PIN_MAP_H */
