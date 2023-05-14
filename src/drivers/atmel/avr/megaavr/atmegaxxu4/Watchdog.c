/**
 * @file Watchdog.c
 * @author Ian Ress
 * @brief See Watchdog.h description.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <avr/interrupt.h>
#include "../../Attributes.h" /* TODO: Cleanup */
#include "Watchdog.h"

static void (*wdt_isr)(void);

static void watchdog_reset(void) GCC_ATTRIBUTE_NAKED \
    GCCATTRIBUTE_SECTION(3) \
    GCC_ATTRIBUTE_USED;

/** TODO: CLEANUP INLINE ASM CALL
 * @brief This disables the watchdog as soon as possible on startup in order to prevent 
 * a never ending loop of system resets from occuring during initialization. For example
 * if this code were not here and the watchdog timer was set to 16ms, this timer may go off
 * before we reach main(). This would cause the MCU to perpetually reset without reaching the
 * application code.
 * 
 * This code is made to execute in the .init3 section so it disables the watchdog as soon
 * as possible on startup. Since AND and OR instructions with zero are involved, we want to 
 * have this code execute only after the zero register is initialized in .init2. The naked
 * attribute is used because we don't want the compiler saving context as this code executes
 * once in the .init3 section. The used attribute prevents the compiler from optimizing
 * this code out.
 * 
 */
static void watchdog_reset(void) {
    asm volatile(
        "wdr                                                    \n\t"
        "in     r16, MCUSR                                      \n\t"
        "andi   r16, (0xff & (0<<WDRF))                         \n\t"
        "out    MCUSR, r16                                      \n\t"
        "in     r16, WDTCSR                                     \n\t"
        "ori    r16, (1<<WDCE) | (1<<WDE)                       \n\t"
        "out    WDTCSR, r16                                     \n\t" //4 clock cycles remaining
        "in     r16, WDTSCR                                     \n\t"
        "andi   r16, (0xff & (0<<WDCE) | (0<<WDE) | (0<<WDIE))  \n\t"
        "out    WDTCSR, r16                                     \n\t"
    );
}

/**
 * @brief ISR that executes on a watchdog timeout.
 * 
 */
ISR(WDT_vect) 
{
    if (wdt_isr) 
    {
        wdt_isr();
    }
}

/**
 * @brief Sets up the watchdog and starts it. 
 * 
 * @param[in] prescalar One of the wdt_timeout_t enum options for the watchdog timeout. For ATMega32U4, the 
 * watchdog can be set to timeout after 16ms, 32ms, 64ms, 125ms, 250ms, 500ms, 1sec, 2sec, 4sec, or 8 sec.
 * 
 * @param[in] mode One of the wdt_mode_t enum options that determines what the watchdog does after a timeout.
 * After timeout the watchdog can be set to fire an interrupt, perform a system reset, or do both.
 * 
 */
void watchdog_enable(wdt_timeout_t prescalar, wdt_mode_t mode)
{
    cli();
    wdt_feed();
    MCUSR &= ~(1<<WDRF); /* Clear reset flag. */
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    WDTCSR = ((uint8_t)prescalar | (uint8_t)mode);
    sei();
}

/**
 * @brief Disables the watchdog but keeps the old timeout value.
 * 
 */
void watchdog_disable(void)
{
    cli();
    wdt_feed();
    MCUSR &= ~(1<<WDRF);
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    WDTCSR &= ~((1<<WDIE) | (1<<WDCE) | (1<<WDE)); /* Disable watchdog interrupt and system reset enable, keep the prescalar. */
    sei(); 
}

/**
 * @brief Sets an ISR function to execute during the watchdog timer interrupt.
 * 
 * @param[in] isr Pointer to an ISR function that executes during a watchdog interrupt.
 * 
 */
void watchdog_set_interrupt(void (*isr)(void))
{
    wdt_isr = isr;
}

/**
 * @brief Placeholder
 * 
 * @param[in] placeholder.
 * 
 */
// void watchdog_set_timeout(wdt_timeout_t ms)
// {

// }

/**
 * @brief Placeholder
 * 
 * @param[in] placeholder.
 * 
 */
// void watchdog_set_mode(wdt_mode_t mode)
// {
    
// }
