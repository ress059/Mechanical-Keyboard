/**
 * @file Gpio.h
 * @author Ian Ress
 * @brief Basic GPIO driver for ATxMega64B3. Pins specific to the microcontroller are also declared here
 * and are defined as a pinmap_t type in userconfig.h. The pinmap_t struct contains two members:
 * 
 * 1) index = index in the gpio array defined in gpio.c. This array contains the base address
 * of each GPIO port. So this maps the pin to the correct port address (port B, port C, etc.)
 * 
 * 2) mask. AVR does not have a barrel shifter so storing each pin's pin mask at compile time
 * saves clock cycles whenever the gpio driver is used.
 * 
 * Declaring the pins this way also makes it easy for the end user to define the column/row pins of
 * their keyboard in userconfig.h, while abstracting away the lower-level info needed for the gpio
 * driver. E.g. #define ROW_PINS {PIN_PD0, PIN_PD1, PIN_PD2, PIN_PD3}. Therefore the keyboard settings 
 * in userconfig.h and application code are microcontroller-agnostic. Only the gpio driver needs to be 
 * changed for each microcontroller. It should also be noted that the user will get a compiler error 
 * if an invalid pin is used (pin that doesn't exist/can't be used for their microcontroller).
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef struct {
	uint8_t index;
    uint8_t mask;
} pinmap_t;

/* ATXMEGA64B3 has SET and CLR registers (e.g. OUTSET, OUTCLR). These perform register
writes via hardware with a single atomic instruction instead of a read-modify-write. The original
plan was to use this for context switching safety. However this is now not necessary since AVR-GCC 
compiler automatically saves the MCU context before being pre-empted. */
typedef struct {
    volatile uint8_t DIR;  /* I/O Port Data Direction */
    volatile uint8_t DIRSET;  /* I/O Port Data Direction Set */
    volatile uint8_t DIRCLR;  /* I/O Port Data Direction Clear */
    volatile uint8_t DIRTGL;  /* I/O Port Data Direction Toggle */
    volatile uint8_t OUT;  /* I/O Port Output */
    volatile uint8_t OUTSET;  /* I/O Port Output Set */
    volatile uint8_t OUTCLR;  /* I/O Port Output Clear */
    volatile uint8_t OUTTGL;  /* I/O Port Output Toggle */
    volatile uint8_t IN;  /* I/O port Input */
    volatile uint8_t INTCTRL;  /* Interrupt Control Register */
    volatile uint8_t INT0MASK;  /* Port Interrupt 0 Mask */
    volatile uint8_t INT1MASK;  /* Port Interrupt 1 Mask */
    volatile uint8_t INTFLAGS;  /* Interrupt Flag Register */
    volatile uint8_t reserved_0x0D;
    volatile uint8_t REMAP;  /* I/O Port Pin Remap Register */
    volatile uint8_t reserved_0x0F;
    volatile uint8_t PIN0CTRL;  /* Pin 0 Control Register */
    volatile uint8_t PIN1CTRL;  /* Pin 1 Control Register */
    volatile uint8_t PIN2CTRL;  /* Pin 2 Control Register */
    volatile uint8_t PIN3CTRL;  /* Pin 3 Control Register */
    volatile uint8_t PIN4CTRL;  /* Pin 4 Control Register */
    volatile uint8_t PIN5CTRL;  /* Pin 5 Control Register */
    volatile uint8_t PIN6CTRL;  /* Pin 6 Control Register */
    volatile uint8_t PIN7CTRL;  /* Pin 7 Control Register */
} gpioreg_t;

/* ATxMega64B3 gpio registers. See ATxMega64B3 datasheet chapter 31. */
#define GPIOB    						((gpioreg_t *) ((uint16_t)0x0620))
#define GPIOC    						((gpioreg_t *) ((uint16_t)0x0640))
#define GPIOD    						((gpioreg_t *) ((uint16_t)0x0660))
#define GPIOG    						((gpioreg_t *) ((uint16_t)0x06C0))
#define GPIOM    						((gpioreg_t *) ((uint16_t)0x0760))

/* MCU specific pinouts */
#define PORTB_INDEX                     0
#define PORTC_INDEX                     1
#define PORTD_INDEX                     2
#define PORTG_INDEX                     3
#define PORTM_INDEX                     4

#define PIN0_MASK					    (1U << 0)
#define PIN1_MASK					    (1U << 1)
#define PIN2_MASK					    (1U << 2)
#define PIN3_MASK					    (1U << 3)
#define PIN4_MASK					    (1U << 4)
#define PIN5_MASK					    (1U << 5)
#define PIN6_MASK					    (1U << 6)
#define PIN7_MASK					    (1U << 7)

/* #define Pin                          {Index in gpio array (see gpio.c), Pin mask} */ 
#define PIN_PB0                         {PORTB_INDEX, (PIN0_MASK)}                       
#define PIN_PB1     					{PORTB_INDEX, (PIN1_MASK)}
#define PIN_PB2     					{PORTB_INDEX, (PIN2_MASK)}
#define PIN_PB3     					{PORTB_INDEX, (PIN3_MASK)}
#define PIN_PB4     					{PORTB_INDEX, (PIN4_MASK)}
#define PIN_PB5     					{PORTB_INDEX, (PIN5_MASK)}
#define PIN_PB6     					{PORTB_INDEX, (PIN6_MASK)}
#define PIN_PB7     					{PORTB_INDEX, (PIN7_MASK)}

#define PIN_PC0     					{PORTC_INDEX, (PIN0_MASK)}
#define PIN_PC1     					{PORTC_INDEX, (PIN1_MASK)}
#define PIN_PC2     					{PORTC_INDEX, (PIN2_MASK)}
#define PIN_PC3     					{PORTC_INDEX, (PIN3_MASK)}
#define PIN_PC4     					{PORTC_INDEX, (PIN4_MASK)}
#define PIN_PC5     					{PORTC_INDEX, (PIN5_MASK)}
#define PIN_PC6     					{PORTC_INDEX, (PIN6_MASK)}
#define PIN_PC7     					{PORTC_INDEX, (PIN7_MASK)}

#define PIN_PD0     					{PORTD_INDEX, (PIN0_MASK)}
#define PIN_PD1     					{PORTD_INDEX, (PIN1_MASK)}

#define PIN_PG0                         {PORTG_INDEX, (PIN0_MASK)}                       
#define PIN_PG1     					{PORTG_INDEX, (PIN1_MASK)}
#define PIN_PG2     					{PORTG_INDEX, (PIN2_MASK)}
#define PIN_PG3     					{PORTG_INDEX, (PIN3_MASK)}
#define PIN_PG4     					{PORTG_INDEX, (PIN4_MASK)}
#define PIN_PG5     					{PORTG_INDEX, (PIN5_MASK)}
#define PIN_PG6     					{PORTG_INDEX, (PIN6_MASK)}
#define PIN_PG7     					{PORTG_INDEX, (PIN7_MASK)}

#define PIN_PM0                         {PORTM_INDEX, (PIN0_MASK)}                       
#define PIN_PM1     					{PORTM_INDEX, (PIN1_MASK)}
#define PIN_PM2     					{PORTM_INDEX, (PIN2_MASK)}
#define PIN_PM3     					{PORTM_INDEX, (PIN3_MASK)}
#define PIN_PM4     					{PORTM_INDEX, (PIN4_MASK)}
#define PIN_PM5     					{PORTM_INDEX, (PIN5_MASK)}
#define PIN_PM6     					{PORTM_INDEX, (PIN6_MASK)}
#define PIN_PM7     					{PORTM_INDEX, (PIN7_MASK)}

void gpio_set_input(pinmap_t pin);
void gpio_set_output(pinmap_t pin);
void gpio_output_low(pinmap_t pin);
void gpio_output_high(pinmap_t pin);
void gpio_toggle(pinmap_t pin);
uint8_t gpio_read(pinmap_t pin);

#endif /* GPIO_H */
