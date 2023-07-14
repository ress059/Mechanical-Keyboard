/**
 * @file kb_config.c
 * @author Ian Ress
 * @brief Defines the keyboard layout. User should not edit this file. Instead, the 
 * user configures all the keyboard settings within kb_config.h. 
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "kb_config.h"

const Pinmap_t g_keyboard_rowpins[KB_NUMBER_OF_ROWS] = ROW_PINS;
const Pinmap_t g_keyboard_colpins[KB_NUMBER_OF_COLUMNS] = COLUMN_PINS;
