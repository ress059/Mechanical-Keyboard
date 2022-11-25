/** @file main.c
*
* @brief Runs the keyboard. 
*
* Author: Ian Ress
*
*/ 

#include "debug.h"

int main(void) 
{
	// blink();
	// timer_blink(1000); /* 1 second */
	// systick_blink(5000); /* 5 seconds */
	test_matrixinit(); /* All rows and columns should be HIGH */
	// test_matrixscan();
	// test_keyboard();
}
