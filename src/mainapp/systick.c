/**
 * @file systick.c
 * @author Ian Ress
 * @brief System timer configured to tick every 1ms. In order to make the systick hardware
 * agnostic, this driver uses a general purpose timer as the systick, regardless if the 
 * microcontroller has a designated systick. It is essentially a collection of wrapper functions
 * that call timer functions specific to the target hardware.  All the user must do is
 * assign the systick to a specific timer in the microcontroller. A compilation error will occur
 * if the timer selected is invalid.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <avr/interrupt.h>
#include "systick.h"
#include "timer.h"

/* Assigning the systick to TIM1. See microcontroller's timer.c for full function definitions. */
static const timer1_t* const systick = &TIM1; 

volatile systick_wordsize_t g_ms = 0;

/**
 * @brief ISR that executes each timer tick.
 * 
 */
static void Systick_ISR(void);
static void Systick_ISR(void) 
{
    g_ms++;
    // if (g_ms == 0) 
    // {
    //     g_ms = 1;
    // }
}


/**
 * @brief Initializes the systick to count every @p SYSTICK_PERIOD_MS 
 * milliseconds without starting. To change the tick frequency
 * update the @p SYSTICK_PERIOD_MS definition in systick.h
 * 
 */
void Systick_Init(void) 
{
    systick->init(SYSTICK_PERIOD_MS);
}


/**
 * @brief Starts the systick.
 * 
 */
void Systick_Start(void) 
{
    systick->start(systick_isr);
}


/**
 * @brief Stops the systick.
 * 
 */
void Systick_Stop(void)
{
    systick->stop();
}
