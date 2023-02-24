/**
 * @file SysTick.c
 * @author Ian Ress
 * \brief System timer configured to tick every 1ms. In order to make the systick hardware
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
#include "SysTick.h"
#include "Timer.h"

/* Assigning the systick to TIM1. See microcontroller's timer.c for full function definitions. */
static const timer1_t* const systick = &TIM1; 

volatile systick_wordsize_t g_ms = 0;

/**
 * \brief ISR that executes each timer tick.
 * 
 */
static void systick_isr(void);
static void systick_isr(void) 
{
    g_ms++;
    // if (g_ms == 0) 
    // {
    //     g_ms = 1;
    // }
}


/**
 * \brief Initializes the systick to count every 1ms without starting. To change the tick frequency
 * update the SYSTICK_PERIOD_MS definition in systick.h
 * 
 */
void systick_init(void) 
{
    systick->init(SYSTICK_PERIOD_MS);
}


/**
 * \brief Starts the systick.
 * 
 */
void systick_start(void) 
{
    systick->start(systick_isr);
}


/**
 * \brief Stops the systick.
 * 
 */
void systick_stop(void)
{
    systick->stop();
}


// /**
//  * \brief Can be called within application to set the systick counter in 
//  * a thread-safe manner. Disabling interrupts prevents a possible race condition
//  * when g_ms is incremented in the systick ISR. Unable to be inlined because I would
//  * like g_ms to have internal linkage and only have it be able to be changed 
//  * through this function call.
//  * 
//  * \param val Value to set systick counter to.
//  */
// void ATOMIC_SET_SYSTICK(uint16_t)
// {
//     cli();
//     g_ms = val;
//     sei();
// }


// /**
//  * \brief Can be called within application to get the systick counter value in 
//  * a thread-safe manner. Disabling interrupts prevents a possible race condition
//  * when g_ms is incremented in the systick ISR. Unable to be inlined because I would
//  * like g_ms to have internal linkage and only have it be able to be accessed 
//  * through this function call.
//  * 
//  * \return The current systick timer counter.
//  */
// uint16_t ATOMIC_GET_SYSTICK(void)
// {
//     uint16_t val;
//     cli();
//     val = g_ms;
//     sei();
//     return val;
// }
