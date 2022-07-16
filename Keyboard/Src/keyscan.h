/** @file keyscan.h
*
* @brief Keyboard scanning logic to detect keypresses. Author: Ian Ress
*
*/

#ifndef KEYSCAN_H
#define KEYSCAN_H

#include <stdint.h>

#define KEYSCAN_BUF_SIZE 15

extern uint8_t keyscan_buf[KEYSCAN_BUF_SIZE];

void keyscan(void);

#endif /* KEYSCAN_H */