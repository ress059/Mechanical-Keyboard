/** @file debug.h
*
* @brief For internal debugging. Author: Ian Ress
*
*/ 

#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>

#include "pin_map.h" 

pin_map_t led;
void blink(void);
void test_matrix(void);


#endif /* DEBUG_H */