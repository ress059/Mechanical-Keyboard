/**
 * @file Main.c
 * @author Ian Ress
 * \brief Runs the keyboard.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Debug.h"

int main(void) 
{
	// blink();
	// timer_blink(1000); /* 1 second */
	// systick_blink(5000); /* 5 seconds */
	test_matrixinit(); /* All rows and columns should be HIGH */
	// test_matrixscan();
	// test_keyboard();
}
