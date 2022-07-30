/** @file systick.c
*
* @brief System timer configured to tick every 1ms. Author: Ian Ress
*
*/

#include <avr/interrupt.h>

#include "systick.h"
#include "timer.h"

static timer_t * const systick = &SYSTICK_TIMER_SELECT;

static void systick_isr(void);

/**
 * @brief ISR that executes each timer tick.
 * 
 */
static void systick_isr(void) {
    cli();
    g_ms++;
    sei();
}

/**
 * @brief Initializes the systick to count every 1ms without starting.
 * 
 */
void systick_init(void) {
    systick->init(1); // timerx_init(1). See timer.c
}

/**
 * @brief Starts the systick.
 * 
 */
void systick_start(void) {
    systick->start(systick_isr); // timerx_start(systick_isr). See timer.c
}
