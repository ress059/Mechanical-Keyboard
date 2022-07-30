/** @file main.c
*
* @brief Runs the keyboard. Author: Ian Ress
*
*/ 

#include "timer.h"
#include "debug.h"

#include <util/delay.h>

int main(void) {
	test_matrix();
    while(1) {
		// blink();
		// _delay_ms(5000);
    }
}
