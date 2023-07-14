/**
 * @file kb_config.h
 * @author Ian Ress
 * @brief User configures keyboard settings here.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef KEYBOARDCONFIG_H
#define KEYBOARDCONFIG_H


#include <bsp_gpio.h>
#include <keycodes.h>

#define KB_HELPER_DEFINITIONS_


/*----------------------------------------------------------------------------------------------------------------*/
/*------ Helper Definitions. Do NOT edit or use in Application Code. Solely for making things easier to read. ----*/
/*----------------------------------------------------------------------------------------------------------------*/

/**
 * @brief HIGH Voltage Reading. 
 * 
 * @attention Do not use in Application Code. Meant for use only within kb_config.h
 * 
 */
#define KB_PIN_HIGH										1


/**
 * @brief LOW Voltage Reading. 
 * 
 * @attention Do not use in Application Code. Meant for use only within kb_config.h
 * 
 */
#define KB_PIN_LOW										0


/**
 * @brief Set the rows or columns as inputs. 
 * 
 * @attention Do not use in Application Code. Meant for use only within kb_config.h
 * 
 */
#define KB_SET_INPUT									0


/**
 * @brief Sets the rows or columns as outputs.
 * 
 * @attention Do not use in Application Code. Meant for use only within kb_config.h
 * 
 */
#define KB_SET_OUTPUT									1



/*----------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------ USER CONFIGURES KEYBOARD HERE ---------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/

/**
 * @brief The keyswitch debounce time in milliseconds. For example setting this value to 5 correlates to a 
 * debounce time of 5 milliseconds. Setting this value to 0 or a negative number means that no debouncing 
 * will occur.
 * 
 */
#define KB_DEBOUNCE_TIME_MS								5000


/**
 * @brief Controls the Matrix Scanning Algorithm. Setting this to 1 will set the Columns as OUTPUTS. Setting
 * this to 0 will set the Columns as INPUTS. On most Keyboards, the default behavior is to set the Columns as 
 * outputs and the Rows as inputs. Thus KB_SET_COLUMNS_AS_OUTPUTS would be 1 and KB_SET_ROWS_AS_OUTPUTS would be 0.
 * 
 * @warning This can only be set to either 0 or 1. If this is set to 0 then KB_SET_ROWS_AS_OUTPUTS must be set to 1, 
 * and if this is set to 1 then KB_SET_ROWS_AS_OUTPUTS must be set to 0. A compilation error will occur if this is
 * not followed.
 * 
 */
#define KB_SET_COLUMNS_AS_INPUTS_OR_OUTPUTS				1


/**
 * @brief Controls the Matrix Scanning Algorithm. Setting this to 1 will set the Rows as Outputs. Setting
 * this to 0 will set the Rows as Inputs. On most Keyboards, the default behavior is to set the Columns as 
 * outputs and the Rows as inputs. Thus KB_SET_COLUMNS_AS_OUTPUTS would be 1 and KB_SET_ROWS_AS_OUTPUTS would be 0.
 * 
 * @warning This can only be set to either 0 or 1. If this is set to 0 then KB_SET_COLUMNS_AS_OUTPUTS must be set to 1, 
 * and if this is set to 1 then KB_SET_COLUMNS_AS_OUTPUTS must be set to 0. A compilation error will occur if this is
 * not followed.
 * 
 * @attention BE AWARE OF DIODE DIRECTION. 
 * 
 */
#define KB_SET_ROWS_AS_OUTPUTS							0


/**
 * @brief Set to either KB_PIN_HIGH or KB_PIN_LOW. The Keyboard will register a keypress when the input pins 
 * detect this voltage state. If this is KB_PIN_HIGH, the input pins MUST use internal or external PULLDOWN 
 * resistors. If this is KB_PIN_LOW, the input pins MUST use internal or external PULLUP resistors. On most 
 * Keyboards, the inputs use PULLDOWN resistors and a KB_PIN_HIGH reading would register a keypress.
 * 
 * @warning This must either be set to KP_PIN_HIGH or KB_PIN_LOW otherwise a compilation error will occur.
 * 
 * @note This definition is included to mainly 
 * 
 * If the EXTERNAL definitions are used, a physical resistor would have to be on the Keyboard PCB.
 * 
 * 
 * This definition allows the user to have either pullup or pulldown resistors
 * connected to the inputs
 * 
 * 
 * 
 * 
 * The user
 * can assign BSP_PIN_Pxyyy_INPUT_INTERNAL_PULLUP, BSP_PIN_Pxyyy_INPUT_EXTERNAL_PULLUP
 * 
 * This is normally
 * defined by the hardware however this gives the user the option to change
 * 
 * if this is HIGH the inputs MUST either use internal or external pulldowns. If this is LOW the inputs MUST either use internal or external pullups
 * 
 */
#define KB_KEYPRESS_DETECTION_LEVEL						KB_PIN_HIGH //HIGH reading means keypress. Sets all column outputs to LOW and rows to inputs with pulldowns.



/**
 * @brief COL2ROW or ROW2COL - how your matrix is configured. COL2ROW means the Cathode (gray marking line) on your diode is facing 
 * to the rows, and between the switch and the rows.
 * 
 */
#define KB_DIODE_DIRECTION 								COL2ROW





#define ROW_PINS					{BSP_PIN_PD0_INPUT_INTERNAL_PULLUP, BSP_PIN_PD1_INPUT_INTERNAL_PULLUP, BSP_PIN_PD2_INPUT_INTERNAL_PULLUP, BSP_PIN_PD3_INPUT_INTERNAL_PULLUP} // TODO: must all be set to one voltage state. i.e. all pulldown or all pullup. how can I do a compile check?
#define COLUMN_PINS					{PIN_PF0, PIN_PF1, PIN_PF4, PIN_PF5, PIN_PF6, PIN_PF7, PIN_PC7, PIN_PC6, PIN_PB6, PIN_PB5, PIN_PB4, PIN_PD6, PIN_PD4, PIN_PD5} //TODO - add PD7 (LED) after testing

/* 
	---------------------------------------------------------------------
	| 							LAYER N							    	|
	---------------------------------------------------------------------
	| 							LAYER 2							    	|
	---------------------------------------------------------------------
	| 						LAYER 1 (main layer)						|
	---------------------------------------------------------------------
*/
#define KEY_LAYOUT					{{KEY_ESC,			KEY_Q,		KEY_W,		KEY_E,		KEY_R,		KEY_T,		KEY_Y,		KEY_U,		KEY_I,		KEY_O,		KEY_P,			KEY_RIGHT_BRACE,	KEY_BACKSPACE,	KEY_PRINTSCREEN},	\
									 {KEY_TAB,			KEY_A,		KEY_S,		KEY_D,		KEY_F,		KEY_G,		KEY_H,		KEY_J,		KEY_K,		KEY_L,		KEY_SEMICOLON,	KEY_ENTER,			KEY_NONE,		KEY_CAPS_LOCK},		\
									 {KEY_LEFT_SHIFT,	KEY_Z,		KEY_X,		KEY_C,		KEY_V,		KEY_B,		KEY_N,		KEY_M,		KEY_COMMA,	KEY_PERIOD,	KEY_SLASH,		KEY_UP,				KEY_NONE,		KEY_EQUAL},			\
									 {KEY_CTRL,			KEY_GUI,	KEY_ALT,	KEY_NONE,	KEY_NONE,	KEY_NONE,	KEY_SPACE,	KEY_NONE,	KEY_NONE,	KEY_TILDE,	KEY_NONE,		KEY_DOWN,			KEY_NONE,		KEY_RIGHT}} //TODO - add back column 12 after done with debugging LED. Add layer 2

/* Programmer declarations. Do not edit. */
extern const Pinmap_t g_keyboard_rowpins[KB_NUMBER_OF_ROWS];
extern const Pinmap_t g_keyboard_colpins[KB_NUMBER_OF_COLUMNS];

#endif /* KEYBOARDCONFIG_H */
