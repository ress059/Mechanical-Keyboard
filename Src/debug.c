/** @file debug.c
*
* @brief For internal debugging. Author: Ian Ress
*
*/ 

#include "debug.h"
#include "matrix.h"
#include "USBhandler.h" 

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


void test_keyboard(void) {
    matrix_init();
    SetupHardware();
	GlobalInterruptEnable();

    while (1) {
        matrix_scan();
        HID_Device_USBTask(&Keyboard_HID_Interface);
		USB_USBTask();
    }
}
