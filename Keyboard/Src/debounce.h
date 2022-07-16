/** @file debounce.h
*
* @brief Debounces the keyswitches. Author: Ian Ress
*
*/

#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <stdint.h>

typedef enum {
    LOW = 0,
    HIGH = 1
} state_t;

void debounce(uint8_t ms);

#endif /* DEBOUNCE_H */