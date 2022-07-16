/** @file user_config.h
*
* @brief User configures keyboard settings here. Author: Ian Ress
*
*/ 

#ifndef USER_CONFIG_H
#define USER_CONFIG_H

#include "pin_map.h"

/**
 * @brief Keyboard configuration. User changes settings here.
 * 
 * @param DEBOUNCE_TIME Keyswitch debounce time in ms.
 * @param NUM_ROWS The number of rows on the keyboard.
 * @param NUM_COLUMNS The number of columns on the keyboard.
 * 
 */
#define DEBOUNCE_TIME				5 //ms
#define NUM_ROWS					4
#define NUM_COLUMNS					14
#define KEY_LAYOUT					{{KEY_ESC,			KEY_Q,		KEY_W,		KEY_E,		KEY_R,		KEY_T,		KEY_Y,		KEY_U,		KEY_I,		KEY_O,		KEY_P,			KEY_RIGHT_BRACE,	KEY_BACKSPACE,	KEY_PRINTSCREEN},	\
									 {KEY_TAB,			KEY_A,		KEY_S,		KEY_D,		KEY_F,		KEY_G,		KEY_H,		KEY_J,		KEY_K,		KEY_L,		KEY_SEMICOLON,	KEY_ENTER,			KEY_NONE,		KEY_CAPS_LOCK},		\
									 {KEY_LEFT_SHIFT,	KEY_Z,		KEY_X,		KEY_C,		KEY_V,		KEY_B,		KEY_N,		KEY_M,		KEY_COMMA,	KEY_PERIOD,	KEY_SLASH,		KEY_UP,				KEY_NONE,		KEY_EQUAL},			\
									 {KEY_CTRL,			KEY_GUI,	KEY_ALT,	KEY_NONE,	KEY_NONE,	KEY_NONE,	KEY_SPACE,	KEY_NONE,	KEY_NONE,	KEY_TILDE,	KEY_NONE,		KEY_DOWN,			KEY_NONE,		KEY_RIGHT}} //TODO - add back column 12 after done with debugging LED

/**
 * @brief Programmer declarations. Do not edit.
 * 
 */
extern const pin_map_t g_keyboard_rowpins[NUM_ROWS];
extern const pin_map_t g_keyboard_colpins[NUM_COLUMNS];

#endif /* USER_CONFIG_H */
