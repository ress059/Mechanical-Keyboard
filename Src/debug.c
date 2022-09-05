/** @file debug.c
*
* @brief For internal debugging. Author: Ian Ress
*
*/ 

#include "debug.h"
#include "gpio.h"
#include "matrix.h"
#include "systick.h"

#include <util/delay.h>

pin_map_t led = PIN_PD7;

void blink(void) 
{
    gpio_toggle(led.port_index, led.pin_mask);
    // _delay_ms(2000);
}

void test_matrixinit(void) {
    matrix_init();
}

void test_matrixscan(void) 
{
    matrix_init();

    while(1) {
        matrix_scan();
    }
}