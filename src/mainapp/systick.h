/**
 * @file systick.h
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

#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

#define SYSTICK_PERIOD_MS                       1

typedef uint16_t systick_wordsize_t;

extern volatile systick_wordsize_t g_ms;

void Systick_Init(void);
void Systick_Start(void);
void Systick_Stop(void);


#endif /* SYSTICK_H */
