/**
 * @file KeyboardConfig.c
 * @author Ian Ress
 * @brief Defines the keyboard layout. User should not edit this file. Instead, the 
 * user configures all the keyboard settings within KeyboardConfig.h. 
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "KeyboardConfig.h"

const Pinmap_t g_keyboard_rowpins[NUM_ROWS] = ROW_PINS;
const Pinmap_t g_keyboard_colpins[NUM_COLUMNS] = COLUMN_PINS;
