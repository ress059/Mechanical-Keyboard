/** @file pin_map.c
*
* @brief Maps pins to ATmega32U4 register address and pin number. Author: Ian Ress
*
*/

#include "pin_map.h"

const pin_map_t g_keyboard_rowpins[NUM_ROWS] = ROW_PINS;
const pin_map_t g_keyboard_colpins[NUM_COLUMNS] = COLUMN_PINS;
