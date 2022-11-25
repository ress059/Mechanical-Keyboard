/** @file user_config.c
*
* @brief Defines the keyboard. User should not edit this file. Instead, the user configures 
* all the keyboard settings within user_config.h. 
*
* Author: Ian Ress
*
*/ 

#include "user_config.h"

const pinmap_t g_keyboard_rowpins[NUM_ROWS] = ROW_PINS;
const pinmap_t g_keyboard_colpins[NUM_COLUMNS] = COLUMN_PINS;
