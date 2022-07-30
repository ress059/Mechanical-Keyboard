/** @file systick.h
*
* @brief System timer configured to tick every 1ms. Author: Ian Ress
*
*/

#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include <stdbool.h>

#define SYSTICK_TIMER_SELECT       TIM1 

extern volatile uint16_t g_ms;

void systick_init(void);
void systick_start(void);

#endif /* SYSTICK_H */