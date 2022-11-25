/** @file systick.c
*
* @brief System timer configured to tick every 1ms. In order to make the systick hardware
* agnostic, this driver uses a general purpose timer as the systick, regardless if the 
* microcontroller has a designated systick. It is essentially a collection of wrapper functions
* that call timer functions specific to the target hardware.  All the user must do is
* assign the systick to a specific timer in the microcontroller. A compilation error will occur
* if the timer selected is invalid. 
*
* Author: Ian Ress
*
*/

#include <avr/interrupt.h>

#include "systick.h"
#include "timer.h"

volatile uint16_t g_ms = 0;

/* Assigning the systick to TIM1. See microcontroller's timer.c for full function definitions. */
static const timer1_t* const systick = &TIM1; 

static void systick_isr(void);

/**
 * @brief ISR that executes each timer tick.
 * 
 */
static void systick_isr(void) 
{
    g_ms++;
    if (g_ms == 0) 
    {
        g_ms = 1;
    }
}

/**
 * @brief Initializes the systick to count every 1ms without starting. To change the tick frequency
 * update the SYSTICK_PERIOD_MS definition in systick.h
 * 
 */
void systick_init(void) 
{
    systick->init(SYSTICK_PERIOD_MS);
}

/**
 * @brief Starts the systick.
 * 
 * @param[in] isr ISR to execute when systick interrupt occurs
 * 
 */
void systick_start(void) 
{
    systick->start(systick_isr);
}

/**
 * @brief Stops the systick.
 * 
 */
void systick_stop(void)
{
    systick->stop();
}
