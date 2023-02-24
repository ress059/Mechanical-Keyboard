/**
 * @file Timer.h
 * @author Ian Ress
 * \brief Basic timer driver for ATmega32U4. Currently only supports Timers 1 and 3 in
 * output compare modes.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

typedef struct
{ 
    void (*init)(uint16_t);
    void (*start)(void (*isr)(void));
    void (*stop)(void);
} timer1_t;

typedef struct
{
    void (*init)(uint16_t);
    void (*start)(void (*isr)(void));
    void (*stop)(void);
} timer3_t;

extern const timer1_t TIM1;
extern const timer3_t TIM3;

#endif /* TIMER_H */
