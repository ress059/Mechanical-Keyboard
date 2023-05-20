/**
 * @file debug.h
 * @author Ian Ress
 * @brief For internal debugging.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>
#include "gpio.h"
#include "systick.h"

extern const Pinmap_t led;

void blink(void);
void timer_blink(uint16_t freq);
void systick_blink(systick_wordsize_t freq);
void test_matrixinit(void);
void test_matrixscan(void);
void test_keyboard(void);

#endif /* DEBUG_H */
