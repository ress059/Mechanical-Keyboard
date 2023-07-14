/**
 * @file bsp_pin_def.h
 * @author Ian Ress
 * @brief Defines the available pins on the ATMega16U4 and ATMega32U4 that the user can assign to a
 * Keyboard Row/Column. The Port, Pin Number, and Configuration definitions defined in kb_pin_def.h are 
 * ORed together to create the definitions in this header file. The result is a uint16_t Bitmap where the 
 * LSB is the Pin Number, the first FIVE BITS of the MSB is the Port assignment, and the last THREE BITS of
 * the MSB is the Pin configuration. See kb_pin_def.h description for more info. This ensures a compilation error 
 * will occur if the user assigns a pin that does not exist on the ATMega16U4 or ATMega32U4. to extract the Port and Pin information needed since the Keyboard Pin definitions will be used as input 
 * parameters. Excessive comments added for every definition for Intellisense purposes.
 * 
 * AVR does not support Input Pulldown or Output Open-Drain configurations
 * @date 2023-06-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef BSP_PIN_DEF_H_
#define BSP_PIN_DEF_H_

#include <kb_pin_def.h>
#include <kb_programming_config.h>


#define BSP_PIN_INPUT_PULLUP                 






/**
 * @brief Pin PB0 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This is also a SPI Chip Select pin. This pin cannot be assigned to a Keyboard 
 * Row/Column if this alternate functionality is used. It is up to the user to determine this.
 * 
 */
#define PB0_INPUT_HIZ                       (KB_PORT_B | KB_PIN_0 | KB_INPUT_HIZ)


#define PB0_INPUT_INTERNAL_PULLUP                    (KB_PORT_B | KB_PIN_0 | KB_INPUT_INTERNAL_PULLUP)

#define PB0_INPUT_EXTERNAL_PULLUP                       (KB_PORT_B | KB_PIN_0 | KB_INPUT_EXTERNAL_PULLUP)


#define PB0_OUTPUT_PUSHPULL                 (KB_PORT_B | KB_PIN_0 | KB_PIN_OUTPUT_PUSHPULL)


/**
 * @brief Pin PB1 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This is also a SPI Clock pin. This pin cannot be assigned to a Keyboard 
 * Row/Column if this alternate functionality is used. It is up to the user to determine this.
 * 
 */
#define KB_PIN_PB1     					(KB_PORT_B | KB_PIN_1)


#if ((KB_ENABLE_PDI) == 0)
    /**
     * @brief Pin PB2 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
     * a Keyboard Row/Column within kb_config.h. 
     * 
     * @attention This pin also serves as a SPI MOSI line or a PDI line which is used
     * for AVR programming/debugging (Atmel proprietary programming protocol separate 
     * from JTAG). This pin cannot be assigned to a Keyboard Row/Column if these alternate 
     * functionalities are used. It is up to the user to determine this.
     * 
     */
    #define KB_PIN_PB2     					(KB_PORT_B | KB_PIN_2)


    /**
     * @brief Pin PB3 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
     * a Keyboard Row/Column within kb_config.h. 
     * 
     * @attention This pin also serves as a SPI MISO line or a PDO line which is used
     * for AVR programming/debugging (Atmel proprietary programming protocol separate 
     * from JTAG). This pin cannot be assigned to a Keyboard Row/Column if this alternate 
     * functionality is used. It is up to the user to determine this.
     * 
     */
    #define KB_PIN_PB3     					(KB_PORT_B | KB_PIN_3)
#endif


/**
 * @brief Pin PB4 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as an ADC Channel Line. This pin cannot be assigned 
 * to a Keyboard Row/Column if this alternate functionality is used. It is up to the 
 * user to determine this.
 * 
 */
#define KB_PIN_PB4     					(KB_PORT_B | KB_PIN_4)


/**
 * @brief Pin PB5 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as a PWM Output or ADC Channel Line. This pin 
 * cannot be assigned to a Keyboard Row/Column if this alternate functionality is 
 * used. It is up to the user to determine this.
 * 
 */
#define KB_PIN_PB5     					(KB_PORT_B | KB_PIN_5)


/**
 * @brief Pin PB6 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as a PWM Output or ADC Channel Line. This pin 
 * cannot be assigned to a Keyboard Row/Column if this alternate functionality is 
 * used. It is up to the user to determine this.
 * 
 */
#define KB_PIN_PB6     					(KB_PORT_B | KB_PIN_6)


/**
 * @brief Pin PB7 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as a PWM Output or UART RTS signal. This pin 
 * cannot be assigned to a Keyboard Row/Column if this alternate functionality is 
 * used. It is up to the user to determine this.
 * 
 */
#define KB_PIN_PB7     					(KB_PORT_B | KB_PIN_7)


/**
 * @brief Pin PC6 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as a PWM Output. This pin cannot be assigned 
 * to a Keyboard Row/Column if this alternate functionality is used. It is up to 
 * the user to determine this.
 * 
 */
#define KB_PIN_PC6     					(KB_PORT_C | KB_PIN_6)


/**
 * @brief Pin PC7 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as a PWM Output and Divide System Clock line. 
 * This pin cannot be assigned to a Keyboard Row/Column if this alternate functionality 
 * is used. It is up to the user to determine this.
 * 
 */
#define KB_PIN_PC7     					(KB_PORT_C | KB_PIN_7)


/**
 * @brief Pin PD0 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as an External Interrupt or I2C SCL line. This pin 
 * cannot be assigned to a Keyboard Row/Column if this alternate functionality is used. 
 * It is up to the user to determine this.
 * 
 */
#define KB_PIN_PD0     					(KB_PORT_D | KB_PIN_0)


/**
 * @brief Pin PD1 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as an External Interrupt or I2C SDA line. This pin 
 * cannot be assigned to a Keyboard Row/Column if this alternate functionality is used. 
 * It is up to the user to determine this.
 * 
 */
#define KB_PIN_PD1     					(KB_PORT_D | KB_PIN_1)


/**
 * @brief Pin PD2 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as an External Interrupt or UART RX line. This pin 
 * cannot be assigned to a Keyboard Row/Column if this alternate functionality is used. 
 * It is up to the user to determine this.
 * 
 */
#define KB_PIN_PD2     					(KB_PORT_D | KB_PIN_2)


/**
 * @brief Pin PD3 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as an External Interrupt or UART TX line. This pin 
 * cannot be assigned to a Keyboard Row/Column if this alternate functionality is used. 
 * It is up to the user to determine this.
 * 
 */
#define KB_PIN_PD3     					(KB_PORT_D | KB_PIN_3)


/**
 * @brief Pin PD4 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as a Timer trigger or ADC Channel line. This pin 
 * cannot be assigned to a Keyboard Row/Column if this alternate functionality is used. 
 * It is up to the user to determine this.
 * 
 */
#define KB_PIN_PD4     					(KB_PORT_D | KB_PIN_4)


/**
 * @brief Pin PD5 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as a UART External Clock or UART CTS line. This pin 
 * cannot be assigned to a Keyboard Row/Column if this alternate functionality is used. 
 * It is up to the user to determine this.
 * 
 */
#define KB_PIN_PD5     					(KB_PORT_D | KB_PIN_5)


/**
 * @brief Pin PD6 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as a Timer Clock Input, PWM Output, or ADC Channel
 * line. This pin cannot be assigned to a Keyboard Row/Column if this alternate 
 * functionality is used. It is up to the user to determine this.
 * 
 */
#define KB_PIN_PD6     					(KB_PORT_D | KB_PIN_6)


/**
 * @brief Pin PD7 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as a Timer Clock Input, PWM Output, or ADC Channel
 * line. This pin cannot be assigned to a Keyboard Row/Column if this alternate 
 * functionality is used. It is up to the user to determine this.
 * 
 */
#define KB_PIN_PD7     					(KB_PORT_D | KB_PIN_7)


/**
 * @brief Pin PE2 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as a Bootloader Activation line. This pin cannot 
 * be assigned to a Keyboard Row/Column if this alternate functionality is used. It 
 * is up to the user to determine this.
 * 
 */
#define KB_PIN_PE2     					(KB_PORT_E | KB_PIN_2)


/**
 * @brief Pin PE6 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as an External Interrupt or Analog Comparitor
 * Positive Input line. This pin cannot be assigned to a Keyboard Row/Column if 
 * this alternate functionality is used. It is up to the user to determine this.
 * 
 */
#define KB_PIN_PE6     					(KB_PORT_E | KB_PIN_6)


/**
 * @brief Pin PF0 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as an ADC Channel line. This pin cannot be 
 * assigned to a Keyboard Row/Column if this alternate functionality is used. 
 * It is up to the user to determine this.
 * 
 */
#define KB_PIN_PF0     					(KB_PORT_F | KB_PIN_0)


/**
 * @brief Pin PF1 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
 * a Keyboard Row/Column within kb_config.h. 
 * 
 * @attention This pin also serves as an ADC Channel line. This pin cannot be 
 * assigned to a Keyboard Row/Column if this alternate functionality is used. 
 * It is up to the user to determine this.
 * 
 */
#define KB_PIN_PF1     					(KB_PORT_F | KB_PIN_1)


#if ((KB_ENABLE_JTAG) == 0)
    /**
     * @brief Pin PF4 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
     * a Keyboard Row/Column within kb_config.h.
     * 
     * @attention This pin also serves as a JTAG TCK or ADC Channel line. This pin cannot 
     * be assigned to a Keyboard Row/Column if this alternate functionality is used. 
     * It is up to the user to determine this.
     * 
     */
    #define KB_PIN_PF4     					(KB_PORT_F | KB_PIN_4)


    /**
     * @brief Pin PF5 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
     * a Keyboard Row/Column within kb_config.h.
     * 
     * @attention This pin also serves as a JTAG TMS or ADC Channel line. This pin cannot 
     * be assigned to a Keyboard Row/Column if this alternate functionality is used. 
     * It is up to the user to determine this.
     * 
     */
    #define KB_PIN_PF5     					(KB_PORT_F | KB_PIN_5)


    /**
     * @brief Pin PF6 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
     * a Keyboard Row/Column within kb_config.h.
     * 
     * @attention This pin also serves as a JTAG TDO or ADC Channel line. This pin cannot 
     * be assigned to a Keyboard Row/Column if this alternate functionality is used. 
     * It is up to the user to determine this.
     * 
     */
    #define KB_PIN_PF6     					(KB_PORT_F | KB_PIN_6)


    /**
     * @brief Pin PF7 GPIO on the ATMega16U4 and ATMega32U4 that can be assigned to
     * a Keyboard Row/Column within kb_config.h.
     * 
     * @attention This pin also serves as a JTAG TDI or ADC Channel line. This pin cannot 
     * be assigned to a Keyboard Row/Column if this alternate functionality is used. 
     * It is up to the user to determine this.
     * 
     */
    #define KB_PIN_PF7     					(KB_PORT_F | KB_PIN_7)
#endif


#endif /* BSP_PIN_DEF_H_ */
