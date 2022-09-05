/** @file matrix.c
*
* @brief Keyboard scanning logic to detect keypresses. Author: Ian Ress
*
*/

#include <stdio.h>
#include <stdbool.h>

#include "matrix.h"
#include "gpio.h"
#include "user_config.h"
#include "systick.h"
#include "pin_map.h"

#include "debug.h"

static uint16_t matrix_state[NUM_ROWS][NUM_COLUMNS] = {{0}};

static bool debounce_logic(uint8_t row, uint8_t col);

/**
 * @brief Reads the pressed key when it is debounced. If it is pressed, the relevant key is
 * stored in a USB transmit buffer.
 * 
 * @param[in] row Matrix row index of the key.
 * @param[in] col Matrix column index of the key. 
 * 
 */
static bool debounce_logic(uint8_t row, uint8_t col)
{
	/* Handle lower-bound overflow cases. E.g. (uint16_t)(5-65535) = 5 which is desired since
	g_ms wraps around to 0 on overflow, so this still gives us the amount of time passed */
	if ((uint16_t)(g_ms - matrix_state[row][col]) >= (uint16_t)DEBOUNCE_TIME) {
		return true;
	}
	else {
		return false;
	}
}

/**
 * @brief Initializes the key matrix. 
 * 
 */
void matrix_init(void) 
{
	/* Disable JTAG or else PF4, PF5, PF6, and PF7 will be pulled up HIGH permanently */
	#ifdef __AVR_ATMEGA32U4__
		MCUCR |= (1U << 7);
		MCUCR |= (1U << 7);
	#endif

	for (int r = 0; r < NUM_ROWS; r++) {
		gpio_set_input(g_keyboard_rowpins[r].port_index, g_keyboard_rowpins[r].pin_mask);
	}

	for (int c = 0; c < NUM_COLUMNS; c++) {
		gpio_set_output(g_keyboard_colpins[c].port_index, g_keyboard_colpins[c].pin_mask);
		gpio_output_high(g_keyboard_colpins[c].port_index, g_keyboard_colpins[c].pin_mask);
	}
}

/**
 * @brief Scans the entire key matrix to detect debounced key presses.
 * TODO TODO TODO: DEBOUNCE ALGORITHM DOES NOT WORK IF KEY IS PRESSED OVER AND OVER AGAIN.
 */
void matrix_scan(void) 
{
	uint8_t keypress = 0;

	for (int c = 0; c < NUM_COLUMNS; c++) {
		gpio_output_low(g_keyboard_colpins[c].port_index, g_keyboard_colpins[c].pin_mask);

		for (int r = 0; r < NUM_ROWS; r++) {

			//if (matrix_state[r][c]) { /* Has debounce timer already started for this key? */

				//if (debounce_logic(r,c)) { /* Has the key been fully debounced? */
					keypress = gpio_read(g_keyboard_rowpins[r].port_index, g_keyboard_rowpins[r].pin_mask);
					
					if (keypress) {
						//TODO: Store press loc, translate to keycode, store keymap in USB buffer

						gpio_toggle(led.port_index, led.pin_mask); /* DEBUG */
					}
					//matrix_state[r][c] = 0;
				}
				gpio_output_high(g_keyboard_colpins[c].port_index, g_keyboard_colpins[c].pin_mask);
			}

			// else { /* Otherwise start debounce timer if initial keypress detected */
			// 	keypress = gpio_read(g_keyboard_rowpins[r].port_index, g_keyboard_rowpins[r].pin_mask);	
			// 	if (keypress) 
			// 	{
			// 		matrix_state[r][c] = g_ms; /* TODO: Handle unlucky case where g_ms = 0 */
			// 	}
			// }
		// }
		
	}
// }
