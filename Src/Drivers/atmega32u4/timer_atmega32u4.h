/** @file timer_atmega32u4.h
*
* @brief Basic timer driver for ATmega32U4. Currently only supports Timers 1 and 3 in
* output compare modes. Author: Ian Ress
*
*/ 

#ifndef TIMER_ATMEGA32U4_H
#define TIMER_ATMEGA32U4_H

#include <stdint.h>

typedef struct { /* Collection of timer methods to more easily assign timers to different tasks. */
    void (*init)(uint16_t);
    void (*start)(void (*isr)(void));
    void (*stop)(void);
} timer_t;

extern timer_t TIM1;
extern timer_t TIM3;

void timer1_init(uint16_t period_ms);
void timer1_start(void (*isr)(void));
void timer1_stop(void);
void timer3_init(uint16_t period_ms);
void timer3_start(void (*isr)(void));
void timer3_stop(void); 

#endif /* TIMER_ATMEGA32U4_H */