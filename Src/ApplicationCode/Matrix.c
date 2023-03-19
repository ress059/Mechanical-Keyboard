/**
 * @file Matrix.c
 * @author Ian Ress
 * @brief Keyboard scanning logic to detect keypresses. 
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/atomic.h>
#include "Debug.h"
#include "Gpio.h"
#include "Matrix.h"
#include "SysTick.h"
#include "UserConfig.h"

static uint16_t matrix_state[NUM_ROWS][NUM_COLUMNS] = {{0}};

static bool debounce_logic(uint8_t row, uint8_t col);

static systick_wordsize_t g_ms_copy = 0;
uint8_t keypress = 0;
uint8_t debugpress = 0;

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
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		g_ms_copy = g_ms;
	}
	
	/* Handle lower-bound overflow cases. E.g. (systick_wordsize_t)(5-65535) = 5 which is desired since
	g_ms wraps around to 0 on overflow, so this still gives us the amount of time passed. This example
	is if systick_wordsize_t definition is set to uint16_t. */
	if ((systick_wordsize_t)(g_ms_copy - matrix_state[row][col]) >= (systick_wordsize_t)DEBOUNCE_TIME) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

/**
 * @brief Initializes the key matrix. 
 * 
 */
void Matrix_Init(void) 
{
	/* Disable JTAG or else PF4, PF5, PF6, and PF7 will be pulled up HIGH permanently */
	/* TODO: Make portable across all targets */
	#if defined(__AVR_ATmega32U4__)
		MCUCR |= (1U << 7);
		MCUCR |= (1U << 7);
	#endif

	for (int r = 0; r < NUM_ROWS; r++) {
		gpio_set_input(g_keyboard_rowpins[r]); /* Input pullup */
	}

	for (int c = 0; c < NUM_COLUMNS; c++) {
		gpio_set_output(g_keyboard_colpins[c]);
		gpio_output_high(g_keyboard_colpins[c]);
	}
}

/**
 * @brief Scans the entire key matrix to detect debounced key presses.
 * 
 */
void Matrix_Scan(void) 
{
	uint8_t keypress = 0;

	for (int c = 0; c < NUM_COLUMNS; c++) {
		gpio_output_low(g_keyboard_colpins[c]);

		for (int r = 0; r < NUM_ROWS; r++) {

			//if (matrix_state[r][c]) { /* Has debounce timer already started for this key? */

				//if (debounce_logic(r,c)) { /* Has the key been fully debounced? */
					keypress = gpio_read(g_keyboard_rowpins[r]);
					
					if (keypress) {
						//TODO: Store press loc, translate to keycode, store keymap in USB buffer

						gpio_toggle(led); /* DEBUG */
						debugpress = 1; /* DEBUG */
					}
					//matrix_state[r][c] = 0;
				}
				gpio_output_high(g_keyboard_colpins[c]);
			}

			// else { /* Otherwise start debounce timer if initial keypress detected */
			// 	keypress = gpio_read(g_keyboard_rowpins[r]);	
			// 	if (keypress) 
			// 	{
			// 		matrix_state[r][c] = g_ms; /* TODO: Handle unlucky case where g_ms = 0 */
			// 	}
			// }
		// }
		
	}
// }
