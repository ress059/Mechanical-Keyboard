/** @file assert.c
*
* @brief Used to throw compile and real-time errors. This is implemented via the naked attribute
* because we do not want to waste time saving program context. If this function triggers, a significant
* error has occured so we want to disable all interrupts and have program execution stop as soon
* as possible. Author: Ian Ress
*
*/

#include <avr/interrupt.h>

void HARD_FAULT(void) {
    cli();
    while(1) { /* TODO: make sure this doesn't get optimized out. */

    }
}

