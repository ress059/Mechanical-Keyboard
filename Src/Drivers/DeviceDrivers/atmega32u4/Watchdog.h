/**
 * @file Watchdog.h
 * @author Ian Ress
 * \brief Basic watchdog timer driver for ATmega32U4. Care must be taken whenever the watchdog registers are 
 * changed. In all functions, a "wdr" instruction is first sent. This resets the watchdog timer and prevents it 
 * from accidently firing. The WDRF flag must then be cleared since it overwrites the WDE bit. 
 * The watchdog registers are then edited in the necessary sequence outlined in ATMega32U4 pg. 56:
 * 
 * 1) In the same operation, write a logic one to the Watchdog change enable bit (WDCE) and WDE. A logic
 * one must be written to WDE regardless of the previous value of the WDE bit.
 * 2) Within the next four clock cycles, write the WDE and Watchdog prescaler bits (WDP) as desired, but with
 * the WDCE bit cleared. This must be done in one operation.
 * 
 * To ensure step 2 always executes, all interrupts are disabled whenever the watchdog registers are changed.
 * This ensures an interrupt does not occur during the 4 clock cycles we have to edit the register. 
 * TODO: Set WDTON bit in AVR Fuses in make file.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* TODO: Cleanup and work */
#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <stdint.h>
#include <avr/io.h>

#define wdt_feed()                      asm volatile ("wdr") /* Resets the watchdog counter */

typedef enum {
    WDT_TIMEOUT_16MS                    = (0<<WDP3) | (0<<WDP2) | (0<<WDP1) | (0<<WDP0), /* Milliseconds */
    WDT_TIMEOUT_32MS                    = (0<<WDP3) | (0<<WDP2) | (0<<WDP1) | (1<<WDP0),
    WDT_TIMEOUT_64MS                    = (0<<WDP3) | (0<<WDP2) | (1<<WDP1) | (0<<WDP0),
    WDT_TIMEOUT_125MS                   = (0<<WDP3) | (0<<WDP2) | (1<<WDP1) | (1<<WDP0),
    WDT_TIMEOUT_250MS                   = (0<<WDP3) | (1<<WDP2) | (0<<WDP1) | (0<<WDP0),
    WDT_TIMEOUT_500MS                   = (0<<WDP3) | (1<<WDP2) | (0<<WDP1) | (1<<WDP0),
    WDT_TIMEOUT_1S                      = (0<<WDP3) | (1<<WDP2) | (1<<WDP1) | (0<<WDP0), /* Seconds */
    WDT_TIMEOUT_2S                      = (0<<WDP3) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0),
    WDT_TIMEOUT_4S                      = (1<<WDP3) | (0<<WDP2) | (0<<WDP1) | (0<<WDP0),
    WDT_TIMEOUT_8S                      = (1<<WDP3) | (0<<WDP2) | (0<<WDP1) | (1<<WDP0),
} wdt_timeout_t;

typedef enum {
    WDT_MODE_INTERRUPT                  = (0<<WDIE) | (0<<WDE),
    WDT_MODE_SYSRESET                   = (1<<WDIE) | (0<<WDE),
    WDT_MODE_INTERRUPT_AND_SYSRESET     = (1<<WDIE) | (1<<WDE)
} wdt_mode_t;

void watchdog_enable(wdt_timeout_t prescalar, wdt_mode_t mode);
void watchdog_disable(void);
void watchdog_set_interrupt(void (*isr)(void));
// void watchdog_set_timeout(wdt_timeout_t ms);
// void watchdog_set_mode(wdt_mode_t mode);

#endif /* WATCHDOG_H */
