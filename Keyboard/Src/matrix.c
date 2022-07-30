/** @file matrix.c
*
* @brief Keyboard scanning logic to detect keypresses. Author: Ian Ress
*
*/

#include <avr/io.h>
#include <stdio.h>

#include "matrix.h"
#include "gpio.h"
#include "user_config.h"
#include "systick.h"
#include "pin_map.h"

static uint16_t matrix_state[NUM_ROWS][NUM_COLUMNS] = {{0}};

static void debounce_logic(uint8_t row, uint8_t col);
static uint8_t keyread(uint8_t row, uint8_t col);

/**
 * @brief Reads the pressed key when it is debounced. If it is pressed, the relevant key is
 * stored in a USB transmit buffer.
 * 
 * @param[in] row Matrix row index of the key.
 * @param[in] col Matrix column index of the key. 
 * 
 */
static void debounce_logic(uint8_t row, uint8_t col) {
	if ((g_ms - matrix_state[row][col]) > DEBOUNCE_TIME) { //TODO: handle overflow

		if(keyread(row, col)) { /* If key is pressed */
			//TODO: Store location in USB buffer. Translate into keycode.
		}
		matrix_state[row][col] = 0;
	}
}

/**
 * @brief Reads an individual key to see if it was pressed.
 * 
 * @param[in] row Matrix row index of the key.
 * @param[in] col Matrix column index of the key. 
 * 
 * @return 1 if pressed, 0 otherwise.
 */
static uint8_t keyread(uint8_t row, uint8_t col) {
	uint8_t keyread = 0;

	gpio_output_low(g_keyboard_colpins[col].port_index, g_keyboard_colpins[col].pin_number);
	keyread = gpio_read(g_keyboard_rowpins[row].port_index, g_keyboard_rowpins[row].pin_number);
	gpio_output_high(g_keyboard_colpins[col].port_index, g_keyboard_colpins[col].pin_number);
	return (keyread);
}

/**
 * @brief Initializes the key matrix. 
 * 
 */
void matrix_init(void) {
	/* Disable JTAG or else PF4, PF5, PF6, and PF7 will be pulled up HIGH permanently */
	#ifdef __AVR_ATmega32U4__
		MCUCR |= (1U << 7);
		MCUCR |= (1U << 7);
	#endif

	for (int r = 0; r < NUM_ROWS; r++) {
		gpio_set_inputpullup(g_keyboard_rowpins[r].port_index, g_keyboard_rowpins[r].pin_number);
	}

	for (int c = 0; c < NUM_COLUMNS; c++) {
		gpio_set_output(g_keyboard_colpins[c].port_index, g_keyboard_colpins[c].pin_number);
		gpio_output_high(g_keyboard_colpins[c].port_index, g_keyboard_colpins[c].pin_number);
	}
}

/**
 * @brief Scans the entire key matrix to detect key presses. 
 * 
 */
void matrix_scan(void) {
	uint8_t keypress = 0;

	for (int c = 0; c < NUM_COLUMNS; c++) {
		gpio_output_low(g_keyboard_colpins[c].port_index, g_keyboard_colpins[c].pin_number);

		for (int r = 0; r < NUM_ROWS; r++) {
			 keypress = gpio_read(g_keyboard_rowpins[r].port_index, g_keyboard_rowpins[r].pin_number);

			 if (keypress) { /* Only read the key when debounce time has been reached */
				if (matrix_state[r][c]) {
					debounce_logic(r,c);
				}
				else {
					matrix_state[r][c] = g_ms;
				}
			 }
		}
		gpio_output_high(g_keyboard_colpins[c].port_index, g_keyboard_colpins[c].pin_number);
	}
}
