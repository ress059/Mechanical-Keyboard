/** @file debug.c
*
* @brief For internal debugging. Author: Ian Ress
*
*/ 

#include "debug.h"
#include "gpio.h"
#include "matrix.h"
#include "systick.h"

pin_map_t led = PIN_PD7;

void blink(void) 
{
    gpio_toggle(led.port_index, led.pin_number);
}

void test_matrix(void) 
{
    matrix_init();
    systick_init();
    systick_start();

    while(1) {
        matrix_scan();
    }
}