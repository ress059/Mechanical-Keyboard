/** @file timer.c
*
* @brief Basic timer driver for ATmega32U4. Currently only supports Timers 1 and 3 in
* output compare modes. Author: Ian Ress
*
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"

#ifdef __AVR_ATmega32U4__
#define PRESCALAR_OPTIONS                 5
#define SYS_CLOCK_FREQ                    2000000 /* Hz. 16MHz crystal divided by 8 for USB. */

/* TCCRnB register. CSn2:0 bits */
#define TIMER1_PRESCALAR_1                (1U << CS10)
#define TIMER1_PRESCALAR_8                (1U << CS11)
#define TIMER1_PRESCALAR_64               ((1U << CS11) | (1U << CS10))
#define TIMER1_PRESCALAR_256              (1U << CS12)
#define TIMER1_PRESCALAR_1024             ((1U << CS12) | (1U << CS10))
#define TIMER3_PRESCALAR_1                (1U << CS30)
#define TIMER3_PRESCALAR_8                (1U << CS31)
#define TIMER3_PRESCALAR_64               ((1U << CS31) | (1U << CS30))
#define TIMER3_PRESCALAR_256              (1U << CS32)
#define TIMER3_PRESCALAR_1024             ((1U << CS32) | (1U << CS30))
#define TIMER1_CTC_MODE                   (1U << WGM12)
#define TIMER3_CTC_MODE                   (1U << WGM32)

static const uint16_t prescalar_vals[PRESCALAR_OPTIONS] = {1, 8, 64, 256, 1024};
#endif

static void (*tim1_isr)(void); 
static void (*tim3_isr)(void);

timer_t TIM1 = {timer1_init, timer1_start, timer1_stop};
timer_t TIM3 = {timer3_init, timer3_start, timer3_stop};

/**
 * @brief ISR that executes when Timer1 reaches the value stored in OCR1A register.
 * 
 */
ISR(TIMER1_COMPA_vect) 
{
    if (tim1_isr) {
        tim1_isr();
    }
}

/**
 * @brief ISR that executes when Timer3 reaches the value stored in OCR3A register.
 * 
 */
ISR(TIMER3_COMPA_vect) 
{
    if (tim3_isr) {
        tim3_isr();
    }
}

/**
 * @brief Initializes Timer1 that generates an ISR every 'period_ms'.
 * 
 * @param[in] period_ms Amount of milliseconds timer increments before 
 * sending an interrupt request. 
 * 
 */
void timer1_init(uint16_t period_ms) 
{
    uint16_t top = 0;
    uint64_t top64 = 0; /* Account for 16-bit overflow during timer top and prescalar calculation. Ugly but will do for now. */

    for (int i = 0; i < PRESCALAR_OPTIONS; i++) {        
        top64 = ((uint64_t)period_ms * (SYS_CLOCK_FREQ/1000)) / prescalar_vals[i] - 1;

        if (top64 > 1 && top64 <= 65535) {
            top = (uint16_t)top64;
            
            if (prescalar_vals[i] == 1) {
                TCCR1B = (TIMER1_CTC_MODE | TIMER1_PRESCALAR_1);
            }
            else if (prescalar_vals[i] == 8) {
                TCCR1B = (TIMER1_CTC_MODE | TIMER1_PRESCALAR_8);
            }
            else if (prescalar_vals[i] == 64) {
                TCCR1B = (TIMER1_CTC_MODE | TIMER1_PRESCALAR_64);
            }
            else if (prescalar_vals[i] == 256) {
                TCCR1B = (TIMER1_CTC_MODE | TIMER1_PRESCALAR_256);
            }
            else if (prescalar_vals[i] == 1024) {
                TCCR1B = (TIMER1_CTC_MODE | TIMER1_PRESCALAR_1024);
            }
            break;
        }

        else if (i == (PRESCALAR_OPTIONS - 1)) {
            //TODO: throw real-time error
        }
    }

    /* TODO: add support for control registers B and C. */
    if (top) {
        TCCR1A = 0;
        OCR1A = top; /* 16-bit register write on 8-bit machine. ATMega32U4, pgs. 113-116 */
    }
}

/**
 * @brief Starts Timer1 and enables its output compare interrupt. Call this function only
 * after calling timer1_init().
 * 
 * @param[in] isr callback that executes within the timer's ISR.
 * 
 */
void timer1_start(void (*isr)(void)) 
{
    cli();
    tim1_isr = isr;
    TCNT1 = 0; /* 16-bit register write on 8-bit machine. ATMega32U4, pgs. 113-116 */
    TIMSK1 |= (1U << OCIE1A);
    sei();
    PRR0 &= ~(1U << PRTIM1);
}

/**
 * @brief Stops Timer1 and disables its output compare interrupt. 
 * 
 */
void timer1_stop(void) 
{
    TIMSK1 &= ~(1U << OCIE1A);
    PRR0 |= (1U << PRTIM1);
}

/**
 * @brief Initializes Timer3 that generates an ISR every 'period_ms'.
 * 
 * @param[in] period_ms Amount of milliseconds timer increments before 
 * sending an interrupt request. 
 * 
 */
void timer3_init(uint16_t period_ms) 
{
    uint16_t top = 0;
    uint64_t top64 = 0; /* Account for 16-bit overflow during timer top and prescalar calculation. Ugly but will do for now. */

    for (int i = 0; i < PRESCALAR_OPTIONS; i++) {
        top64 = ((uint64_t)period_ms * (SYS_CLOCK_FREQ/1000)) / prescalar_vals[i] - 1;

        if (top64 > 1 && top64 <= 65535) {
            top = (uint16_t)top64;
            
            if (prescalar_vals[i] == 1) {
                TCCR3B = (TIMER3_CTC_MODE | TIMER3_PRESCALAR_1);
            }
            else if (prescalar_vals[i] == 8) {
                TCCR3B = (TIMER3_CTC_MODE | TIMER3_PRESCALAR_8);
            }
            else if (prescalar_vals[i] == 64) {
                TCCR3B = (TIMER3_CTC_MODE | TIMER3_PRESCALAR_64);
            }
            else if (prescalar_vals[i] == 256) {
                TCCR3B = (TIMER3_CTC_MODE | TIMER3_PRESCALAR_256);
            }
            else if (prescalar_vals[i] == 1024) {
                TCCR3B = (TIMER3_CTC_MODE | TIMER3_PRESCALAR_1024);
            }
            break;
        }

        else if (i == (PRESCALAR_OPTIONS - 1)) {
            //TODO: throw real-time error
        }
    }

    /* TODO: add support for control registers B and C. */
    if (top) {
        TCCR3A = 0;
        OCR3A = top;
    }
}

/**
 * @brief Starts Timer3 and enables its output compare interrupt. Call this function only
 * after calling timer3_init().
 * 
 * @param[in] isr callback that executes within the timer's ISR.
 * 
 */
void timer3_start(void (*isr)(void)) 
{
    cli();
    tim3_isr = isr;
    TCNT3 = 0; /* 16-bit register write on 8-bit machine. ATMega32U4, pgs. 113-116 */
    TIMSK3 |= (1U << OCIE3A);
    sei();
    PRR1 &= ~(1U << PRTIM3);
}

/**
 * @brief Stops Timer3 and disables its output compare interrupt. 
 * 
 */
void timer3_stop(void) 
{
    TIMSK3 &= ~(1U << OCIE3A);
    PRR1 |= (1U << PRTIM3);
}
