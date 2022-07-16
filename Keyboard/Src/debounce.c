/** @file debounce.c
*
* @brief Debounces the keyswitches. Author: Ian Ress
*
*/

#include "debounce.h"

/**
 * @brief Debounces a keypress.
 * 
 * @param[in] msec debounce time.
 * 
 */
void debounce (uint8_t ms) {
    static state_t switchstate = LOW;
    //if button pressed
    //poll again in msec time
    //if still pressed register a press
}