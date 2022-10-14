/** @file debug.h
*
* @brief For internal debugging. Author: Ian Ress
*
*/ 

#ifndef DEBUG_H
#define DEBUG_H

#include "mcu_drivers.h"
#include <stdint.h>

extern pin_map_t led;

void blink(void);
void test_matrixinit(void);
void test_matrixscan(void);
void test_keyboard(void);


#endif /* DEBUG_H */