/** @file user_config.h
* 
* @brief User configures keyboard settings here. Author: Ian Ress
*
*/

#include "user_config.h"

/**
 * @brief Keyboard configuration. User changes settings here.
 * 
 */
const pin_map_t g_keyboard_rowpins[NUM_ROWS] = {PD0, PD1, PD2, PD3};
const pin_map_t g_keyboard_colpins[NUM_COLUMNS] = {PF0, PF1, PF4, PF5, PF6, PF7, PC7, PC6, PB6, PB5, PB4, PD6, PD4, PD5} //TODO - add _PD7 after testing