/**
 * @file bsp_gpio.h
 * @author Ian Ress
 * @brief ATMega16U4 and ATMega32U4 GPIO Driver. The GPIO Drivers for ALL microcontrollers MUST define only these 5
 * functions for use within the Application Code:
 * 
 * 1) void BSP_GPIO_Set_Input(const KB_PINSIZE_T BSP_PIN);
 * 
 * 2) void BSP_GPIO_Set_Output(const KB_PINSIZE_T BSP_PIN);
 * 
 * 3) void BSP_GPIO_Set_Output_High(const KB_PINSIZE_T BSP_PIN);
 * 
 * 4) void BSP_GPIO_Set_Output_Low(const KB_PINSIZE_T BSP_PIN);
 * 
 * 5) bool BSP_GPIO_Is_Key_Pressed(const KB_PINSIZE_T BSP_PIN);
 * 
 * 
 * All GPIO functions are inlined and included in this Header File to reduce function call overhead. It is important 
 * to do this since most of the time the Keyboard will be scanning and repeatedly calling these functions.
 * 
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef BSP_GPIO_H_
#define BSP_GPIO_H_

#include <kb_pin_def.h>
#include <stdbool.h>
#include <stdint.h>


/*----------------------------------------------------------------------------------------------------------------*/
/*------------ HELPER DEFINITIONS. DO NOT USE IN THE APPLICATION. SOLELY FOR MAKING THIGNS EASIER TO READ --------*/
/*---------------------- HAVE TO INCLUDE HERE IN ORDER TO INLINE GPIO DRIVER FUNCTIONS ---------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/

/**
 * @warning Do NOT use this in the Application Code. This is meant to be internal to the ATMega16U4/ATMega32U4
 * GPIO Driver.
 * 
 */
typedef struct
{
	volatile uint8_t PINx;
	volatile uint8_t DDRx;
	volatile uint8_t PORTx;
} AVR_GPIO_Reg_t;


/**
 * @warning Do NOT use this in the Application Code. This is meant to be internal to the ATMega16U4/ATMega32U4
 * GPIO Driver. GPIO_PORTS[0] = do not use, GPIO_PORTS[1] = Port B, GPIO_PORTS[2] = Port C, GPIO_PORTS[3] = Port D, 
 * GPIO_PORTS[4] = Port E, and GPIO_PORTS[5] = Port F.
 * 
 */
typedef AVR_GPIO_Reg_t GPIO_PORTS[6];


/**
 * @warning Do NOT use this in the Application Code. This is meant to be internal to the ATMega16U4/ATMega32U4
 * GPIO Driver. GPIO_PORT_BASES[1].PINx = PINB = Address 0x23, GPIO_PORT_BASES[1].DDRx = DDRB = Address 0x24,
 * GPIO_PORT_BASES[1].PORTx = PORTB = Address 0x25, GPIO_PORT_BASES[2].PINx = PINC = Address 0x26, etc.
 * GPIO_PORTS[0] starts at Address 0x20 and will never be used since it is a Reserved Space. 
 * 
 */
#define GPIO_PORT_BASES							(*((GPIO_PORTS *)0x20))



/*----------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------- PUBLIC GPIO DRIVER FUNCTIONS ------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Sets the GPIO as either Input Hi-Z or Input Pullup. A compilation error will occur if
 * Input Pulldown is used as this is not a possible configuration for ATMega16U4/ATMega32U4.
 * 
 * @param BSP_PIN One of the BSP Pin definitions found in drivers../atmegaxxu4/bsp_pin_def.h. This 
 * MUST be used as the input as this is a standardized format that all microcontrollers can follow to 
 * extract the Port, Pin Number, and Configuration information.
 * 
 */
static inline void BSP_GPIO_Set_Input(const KB_PINSIZE_T BSP_PIN);
static inline void BSP_GPIO_Set_Input(const KB_PINSIZE_T BSP_PIN)
{
	uint8_t port = KB_GET_PORT(BSP_PIN);
	uint8_t pin = KB_GET_PIN(BSP_PIN);

	GPIO_PORT_BASES[port].DDRx &= ~(1U << pin);

	if (KB_GET_PIN_TYPE(BSP_PIN) == KB_INPUT_INTERNAL_PULLUP)
	{
		GPIO_PORT_BASES[port].PORTx |= (1U << pin);
	}
}


/**
 * @brief Sets the GPIO as Output Pushpull. A compilation error will occur if Output Open-Drain
 * is used as this is not a possible configuration for ATMega16U4/ATMega32U4.
 * 
 * @param BSP_PIN One of the BSP Pin definitions found in drivers../atmegaxxu4/bsp_pin_def.h. This 
 * MUST be used as the input as this is a standardized format that all microcontrollers can follow to 
 * extract the Port, Pin Number, and Configuration information.
 * 
 */
static inline void BSP_GPIO_Set_Output(const KB_PINSIZE_T BSP_PIN);
static inline void BSP_GPIO_Set_Output(const KB_PINSIZE_T BSP_PIN)
{
	uint8_t port = KB_GET_PORT(BSP_PIN);
	uint8_t pin = KB_GET_PIN(BSP_PIN);

	GPIO_PORT_BASES[port].DDRx |= (1U << pin);
}


/**
 * @brief Sets the GPIO to a HIGH voltage. 
 * 
 * @attention BSP_GPIO_Set_Output() must be called before using this function.
 * 
 * @param BSP_PIN One of the BSP Pin definitions found in drivers../atmegaxxu4/bsp_pin_def.h. This 
 * MUST be used as the input as this is a standardized format that all microcontrollers can follow to 
 * extract the Port, Pin Number, and Configuration information.
 * 
 */
static inline void BSP_GPIO_Set_Output_High(const KB_PINSIZE_T BSP_PIN);
static inline void BSP_GPIO_Set_Output_High(const KB_PINSIZE_T BSP_PIN)
{
	uint8_t port = KB_GET_PORT(BSP_PIN);
	uint8_t pin = KB_GET_PIN(BSP_PIN);

	GPIO_PORT_BASES[port].PORTx |= (1U << pin);
}


/**
 * @brief Sets the GPIO to a LOW voltage. 
 * 
 * @attention BSP_GPIO_Set_Output() must be called before using this function.
 * 
 * @param BSP_PIN One of the BSP Pin definitions found in drivers../atmegaxxu4/bsp_pin_def.h. This 
 * MUST be used as the input as this is a standardized format that all microcontrollers can follow to 
 * extract the Port, Pin Number, and Configuration information.
 * 
 */
static inline void BSP_GPIO_Set_Output_Low(const KB_PINSIZE_T BSP_PIN);
static inline void BSP_GPIO_Set_Output_Low(const KB_PINSIZE_T BSP_PIN)
{
	uint8_t port = KB_GET_PORT(BSP_PIN);
	uint8_t pin = KB_GET_PIN(BSP_PIN);

	GPIO_PORT_BASES[port].PORTx &= ~(1U << pin);
}


/**
 * @brief The GPIO reading that corresponds to a keypress can either be HIGH or LOW depending on
 * the user's pin configuration. I.e. A LOW reading for an Input Pullup corresponds to a keypress
 * but a HIGH reading for an Input Pulldown corresponds to a keypress. This function will handle these
 * dependencies to avoid potential conflicts in the Application Code. Instead of returning a raw GPIO 
 * reading, this function will instead return true if a keypress occured and false otherwise.
 * 
 * @attention BSP_GPIO_Set_Input() must be called before using this function.
 * 
 * @param BSP_PIN One of the BSP Pin definitions found in drivers../atmegaxxu4/bsp_pin_def.h. This 
 * MUST be used as the input as this is a standardized format that all microcontrollers can follow to 
 * extract the Port, Pin Number, and Configuration information.
 * 
 * @return True if a keypress occured. False otherwise.
 *  
 */
static inline bool BSP_GPIO_Is_Key_Pressed(const KB_PINSIZE_T BSP_PIN);
static inline bool BSP_GPIO_Is_Key_Pressed(const KB_PINSIZE_T BSP_PIN)
{
	uint8_t port = KB_GET_PORT(BSP_PIN);
	uint8_t pin = KB_GET_PIN(BSP_PIN);
	uint8_t reading = (GPIO_PORT_BASES[port].PINx & pin);
	bool keypress = false;

	if ((KB_GET_PIN_TYPE(BSP_PIN) == KB_INPUT_INTERNAL_PULLUP) && (reading == 0))
	{
		keypress = true;
	}
	else if (reading)
	{
		keypress = true;
	}
	return keypress;
}


#endif /* BSP_GPIO_H_ */
