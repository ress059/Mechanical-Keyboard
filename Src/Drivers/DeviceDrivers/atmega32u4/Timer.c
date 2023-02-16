/**
 * @file Timer.c
 * @author Ian Ress
 * @brief Basic timer driver for ATmega32U4. Currently only supports Timers 1 and 3 in
 * output compare modes.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"

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
static void (*tim1_isr)(void); 
static void (*tim3_isr)(void);

/* The actual timer functions are declared static to prevent them from being directly used in 
the application code. Instead a task should be assigned to a timer and referenced like in the
example below. This is to prevent having to change large amounts of application code if the task
requires a new timer due to a microcontroller change or general functionality change. */
static void timer1_init(uint16_t period_ms);
static void timer1_start(void (*isr)(void));
static void timer1_stop(void);
static void timer3_init(uint16_t period_ms);
static void timer3_start(void (*isr)(void));
static void timer3_stop(void);

/* Collection of timer methods to more easily assign timers to different tasks. Based on the timer,
the functions associated with it and corresponding arguments may be different. So each timer is
declared with a unique type. To assign a timer to a specific functionality (e.g. systick), a pointer to
the timer object can be created and referenced 

    For example:
    const timer1_t* const systick = &TIM1;
    systick->init(1);
    systick->stop();

If a desired timer function doesn't exist or a timer that isn't supported by a specific MCU is used, 
the user will get a compilation error. Only the initial definition of the pointer must be changed 
to an appropriate timer instead of having to go through and change all the application code. */
const timer1_t TIM1 = {timer1_init, timer1_start, timer1_stop};
const timer3_t TIM3 = {timer3_init, timer3_start, timer3_stop};


/**
 * @brief ISR that executes when Timer1 reaches the value stored in OCR1A register.
 * 
 */
ISR(TIMER1_COMPA_vect) 
{
    if (tim1_isr) 
    {
        tim1_isr();
    }
}

/**
 * @brief ISR that executes when Timer3 reaches the value stored in OCR3A register.
 * 
 */
ISR(TIMER3_COMPA_vect) 
{
    if (tim3_isr) 
    {
        tim3_isr();
    }
}

/**
 * @brief Initializes Timer1 that generates an ISR every 'period_ms'.
 * 
 * @param period_ms Amount of milliseconds timer increments before 
 * sending an interrupt request. 
 * 
 */
static void timer1_init(uint16_t period_ms) 
{
    uint16_t top = 0;
    uint64_t top64 = 0; /* Account for 16-bit overflow during timer top and prescalar calculation. Ugly but will do for now. */

    for (int i = 0; i < PRESCALAR_OPTIONS; i++) {        
        top64 = ((uint64_t)period_ms * (SYS_CLOCK_FREQ/1000)) / prescalar_vals[i] - 1;

        if (top64 > 1 && top64 <= 65535) { /* Did we find a valid prescalar value for our desired frequency? */
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
        cli();
        OCR1A = top; /* 16-bit register write on 8-bit machine. ATMega32U4, pgs. 113-116 */
        sei();
    }
}

/**
 * @brief Starts Timer1 and enables its output compare interrupt. Call this function only
 * after calling timer1_init().
 * 
 * @param[in] isr callback that executes within the timer's ISR. This makes it easier to
 * pass in custom ISRs.
 * 
 */
static void timer1_start(void (*isr)(void)) 
{
    tim1_isr = isr;
    cli();
    TCNT1 = 0; /* 16-bit register write on 8-bit machine. ATMega32U4, pgs. 113-116 */
    sei();
    TIMSK1 |= (1U << OCIE1A);
    PRR0 &= ~(1U << PRTIM1);
}

/**
 * @brief Stops Timer1 and disables its output compare interrupt. 
 * 
 */
static void timer1_stop(void) 
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
static void timer3_init(uint16_t period_ms) 
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
        cli();
        OCR3A = top; /* 16-bit register write on 8-bit machine. ATMega32U4, pgs. 113-116 */
        sei();
    }
}

/**
 * @brief Starts Timer3 and enables its output compare interrupt. Call this function only
 * after calling timer3_init().
 * 
 * @param[in] isr callback that executes within the timer's ISR. This makes it easier to
 * pass in custom ISRs.
 * 
 */
static void timer3_start(void (*isr)(void)) 
{
    tim3_isr = isr;
    cli();
    TCNT3 = 0; /* 16-bit register write on 8-bit machine. ATMega32U4, pgs. 113-116 */
    sei();
    TIMSK3 |= (1U << OCIE3A);
    PRR1 &= ~(1U << PRTIM3);
}

/**
 * @brief Stops Timer3 and disables its output compare interrupt. 
 * 
 */
static void timer3_stop(void) 
{
    TIMSK3 &= ~(1U << OCIE3A);
    PRR1 |= (1U << PRTIM3);
}
