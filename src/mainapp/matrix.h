/**
 * @file matrix.h
 * @author Ian Ress
 * @brief Keyboard scanning logic to detect keypresses.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

extern uint8_t debugpress; /* TODO: DEBUGGING */

void Matrix_Init(void);
void Matrix_Scan(void);

#endif /* MATRIX_H */
