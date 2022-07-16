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

void (*tim1_isr)(void); 
void (*tim3_isr)(void);

/**
 * @brief ISR that executes when Timer1 reaches the value stored in OCR1A register.
 * 
 */
ISR(TIMER1_COMPA_vect) {
    if (tim1_isr) {
        tim1_isr();
    }
}

/**
 * @brief ISR that executes when Timer3 reaches the value stored in OCR3A register.
 * 
 */
ISR(TIMER3_COMPA_vect) {
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
void timer1_init(uint8_t period_ms) {
    uint8_t sreg;
    uint16_t top;
    uint32_t top32; /* Account for 16-bit overflow during timer top and prescalar calculation. */

    for (int i = 0; i < PRESCALAR_OPTIONS; i++) {
        top32 = ((period_ms * SYS_CLOCK_FREQ)/(prescalar_vals[i] * 1000)) - 1;

        if (top32 > 1 && top32 <= 65535) {
            top = (uint16_t)top32;
            
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
            #error "No valid top and prescalar value combination exists for provided input."
        }
    }

    /* TODO: add support for control registers B and C. */
    TCCR1A = 0;
    sreg = SREG;
    cli();
    OCR1A = top; /* 16-bit register write on 8-bit machine. ATMega32U4, pgs. 113-116 */
    SREG = sreg;
    sei();
}

/**
 * @brief Starts Timer1 and enables its output compare interrupt. Call this function only
 * after calling timer1_init().
 * 
 * @param[in] isr callback that executes within the timer's ISR.
 * 
 */
void timer1_start(void (*isr)(void)) {
    tim1_isr = isr;
    TIMSK1 |= (1U << OCIE1A);
    PRR0 &= ~(1U << PRTIM1);
    
}

/**
 * @brief Stops Timer1 and disables its output compare interrupt. 
 * 
 */
void timer1_stop(timer16_t timer) {
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
void timer3_init(uint8_t period_ms) {
    uint8_t sreg;
    uint16_t top;
    uint32_t top32; /* Account for 16-bit overflow during timer top and prescalar calculation. */

    for (int i = 0; i < PRESCALAR_OPTIONS; i++) {
        top32 = ((period_ms * SYS_CLOCK_FREQ)/(prescalar_vals[i] * 1000)) - 1;

        if (top32 > 1 && top32 <= 65535) {
            top = (uint16_t)top32;
            
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
            #error "No valid top and prescalar value combination exists for provided input."
        }
    }

    /* TODO: add support for control registers B and C. */
    TCCR3A = 0;
    sreg = SREG;
    cli();
    OCR3A = top; /* 16-bit register write on 8-bit machine. ATMega32U4, pgs. 113-116 */
    SREG = sreg;
    sei();
}

/**
 * @brief Starts Timer3 and enables its output compare interrupt. Call this function only
 * after calling timer3_init().
 * 
 * @param[in] isr callback that executes within the timer's ISR.
 * 
 */
void timer3_start(void (*isr)(void)) {
    tim1_isr = isr;
    TIMSK3 |= (1U << OCIE3A);
    PRR1 &= ~(1U << PRTIM3);
}

/**
 * @brief Stops Timer3 and disables its output compare interrupt. 
 * 
 */
void timer3_stop(timer16_t timer) {
    TIMSK3 &= ~(1U << OCIE3A);
    PRR1 |= (1U << PRTIM3);
}
