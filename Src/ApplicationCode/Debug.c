/**
 * @file Debug.c
 * @author Ian Ress
 * @brief For internal debugging.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <util/delay.h>
#include <stddef.h>
#include "Debug.h"
#include "Matrix.h"
#include "Timer.h"
#include "USBHandler.h"

const pinmap_t led = PIN_PD7;
const timer1_t* const blinktimer = &TIM1;

static void timer_isr(void);
static void timer_isr(void)
{
    gpio_toggle(led);
}

/**
 * @brief Bare bones test of the GPIO driver. Blinks the onboard LED. Timing does not matter here,
 * all that is being tested is that the GPIO output functions work and toggled the LED.
 * 
 */
void blink(void) 
{
    gpio_set_output(led);
    while(1)
    {
        gpio_toggle(led);
        _delay_ms(2000);
    }
}

/**
 * @brief Tests the timer driver. Assign blinktimer object to any timer to test it. A GPIO output
 * pin is toggled within the timer ISR to verify timer frequency.
 * 
 * @param[in] freq The frequency to generate a compare match ISR.
 */
void timer_blink(uint16_t freq)
{
    gpio_set_output(led);
    gpio_output_high(led);
    blinktimer->init(freq);
    blinktimer->start(timer_isr);
    while(1){}
}

/**
 * @brief Tests the systick. The systick ISR is generated every 1ms and is tracked via
 * variable 'g_ms'.
 * 
 * @param[in] freq The frequency to toggle the GPIO output pin.
 */
void systick_blink(systick_wordsize_t freq)
{
    static systick_wordsize_t wait = 0;
    static systick_wordsize_t g_ms_copy = 0;

    gpio_set_output(led);
    Systick_Init();
    Systick_Start();

    while (1)
    {

        ATOMIC_BLOCK(ATOMIC_FORCEON)
        {
            g_ms_copy = g_ms;
        }

        if ( ((systick_wordsize_t)(g_ms_copy - wait)) >= freq )
        {
            gpio_toggle(led);
            wait = g_ms_copy;
        }
    }
}

/**
 * @brief Tests the remaining GPIO driver and user_config.h setup file. All rows
 * on the keyboard should be pulled HIGH (input pullup). All columns should also
 * be HIGH (output HIGH). 
 * 
 */
void test_matrixinit(void) 
{
    Matrix_Init();
}

/**
 * @brief Tests the matrix scanning function which scans through the entire keyboard
 * for keypresses.
 * 
 */
void test_matrixscan(void) 
{
    Matrix_Init();

    while(1) {
        Matrix_Scan();
    }
}


/**
 * @brief Tests the matrix scanning and USB functionality.
 * 
 */
void test_keyboard(void) 
{
    Matrix_Init();
    SetupHardware();
	GlobalInterruptEnable();

    while (1) {
        Matrix_Scan();
        HID_Device_USBTask(&Keyboard_HID_Interface);
		USB_USBTask();
    }
}
