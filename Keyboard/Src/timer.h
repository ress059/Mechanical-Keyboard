/** @file timer.h
*
* @brief Basic timer driver for ATmega32U4. Currently only supports Timers 1 and 3 in
* output compare modes. Author: Ian Ress
*
*/ 

#ifndef TIMER16_H
#define TIMER16_H

#include <stdint.h>

void timer1_init(uint8_t period_ms);
void timer1_start(void (*isr)(void))
void timer1_stop(void);
void timer3_init(uint8_t period_ms);
void timer3_start(void (*isr)(void))
void timer3_stop(void);

#endif /* TIMER_H */
