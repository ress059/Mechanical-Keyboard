/**
 * @file main.c
 * @author Ian Ress
 * @brief Runs the keyboard.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "debug.h"
#include "matrix.h"
#include "scheduler.h"
#include "systick.h"

int main(void) 
{
	// blink();
	// timer_blink(1000); /* 1 second */
	// systick_blink(5000); /* 5 seconds */
	test_matrixinit(); /* All rows and columns should be HIGH */
	// test_matrixscan();
	// test_keyboard();


	// cli();
	// /* TODO: Watchdog Disable */
	// Systick_Init();
	// Matrix_Init();
	// /* Other initializations */
	// USB_Init();
	// /* Wait for enumeration phase to complete */

	// (void)Create_Task(Matrix_Scan, 20);
	// (void)Create_Task(USB_HIDTask, 5);

	// Systick_Start();
	// sei();
	
	// while(1)
	// {
	// 	Begin_Scheduler();
	// }
}
