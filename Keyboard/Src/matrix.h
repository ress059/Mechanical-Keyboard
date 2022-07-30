/** @file matrix.h
*
* @brief Keyboard scanning logic to detect keypresses. Author: Ian Ress
*
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

void matrix_init(void);
void matrix_scan(void);

#endif /* MATRIX_H */