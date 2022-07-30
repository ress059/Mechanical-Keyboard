/** @file pin_map.h
*
* @brief Maps pins to ATmega32U4 register address and pin number. Author: Ian Ress
*
*/

#ifndef PIN_MAP_H
#define PIN_MAP_H

#include <stdint.h>

#define PIN_PB0                         {0,0}                       
#define PIN_PB1     					{0,1}
#define PIN_PB2     					{0,2}
#define PIN_PB3     					{0,3}
#define PIN_PB4     					{0,4}
#define PIN_PB5     					{0,5}
#define PIN_PB6     					{0,6}
#define PIN_PB7     					{0,7}
#define PIN_PC6     					{1,6}
#define PIN_PC7     					{1,7}
#define PIN_PD0     					{2,0}
#define PIN_PD1     					{2,1}
#define PIN_PD2     					{2,2}
#define PIN_PD3     					{2,3}
#define PIN_PD4     					{2,4}
#define PIN_PD5     					{2,5}
#define PIN_PD6     					{2,6}
#define PIN_PD7     					{2,7}
#define PIN_PE2     					{3,2}
#define PIN_PE6     					{3,6}
#define PIN_PF0     					{4,0}
#define PIN_PF1     					{4,1}
#define PIN_PF4     					{4,4}
#define PIN_PF5     					{4,5}
#define PIN_PF6     					{4,6}
#define PIN_PF7     					{4,7}

#include "user_config.h"

typedef struct {
	uint8_t port_index;
    uint8_t pin_number;
} pin_map_t;

extern const pin_map_t g_keyboard_rowpins[NUM_ROWS];
extern const pin_map_t g_keyboard_colpins[NUM_COLUMNS];

#endif /* PIN_MAP_H */
