/** @file pin_map.h
*
* @brief Maps pins to ATmega32U4 register address and pin number. Author: Ian Ress
*
*/

#ifndef PIN_MAP_H
#define PIN_MAP_H

#include <stdint.h>

#define PB0                         {0,0}                       
#define PB1     					{0,1}
#define PB2     					{0,2}
#define PB3     					{0,3}
#define PB4     					{0,4}
#define PB5     					{0,5}
#define PB6     					{0,6}
#define PB7     					{0,7}
#define PC6     					{1,6}
#define PC7     					{1,7}
#define PD0     					{2,0}
#define PD1     					{2,1}
#define PD2     					{2,2}
#define PD3     					{2,3}
#define PD4     					{2,4}
#define PD5     					{2,5}
#define PD6     					{2,6}
#define PD7     					{2,7}
#define PE2     					{3,2}
#define PE6     					{3,6}
#define PF0     					{4,0}
#define PF1     					{4,1}
#define PF4     					{4,4}
#define PF5     					{4,5}
#define PF6     					{4,6}
#define PF7     					{4,7}

typedef struct {
	uint8_t port_index;
    uint8_t pin_number;
} pin_map_t;

#endif /* PIN_MAP_H */
