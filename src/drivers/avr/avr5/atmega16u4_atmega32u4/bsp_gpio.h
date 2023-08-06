/**
 * @file bsp_gpio.h
 * @author Ian Ress
 * @brief ATMega16U4 and ATMega32U4 GPIO Driver. See README within the top-level drivers folder that explains 
 * how each target's GPIO Driver must be designed. It is not a requirement but for ATMega16U4 and ATMega32U4
 * all functions are inlined. This greatly reduces overhead since the Keyboard will spend the majority of its
 * time conducting GPIO Reads and Writes while Matrix Scanning.
 * 
 * Typical Memory Mapped I/O structs are not used because these should not be visible to the Application. 
 * To explain the alternate method used, a GPIO Memory Map for ATMega16U4 and ATMega32U4 is shown below:
 * 
 * 
 * 			   Description					  PINx                 DDRx               PORTx
 * -----------------------------------------------------------------------------------------------
 * |	RESERVED - NEVER ACCESSED    |    BASE = 0x20    |    BASE = 0x21    |    BASE = 0x22    |
 * |---------------------------------|-------------------|-------------------|-------------------|
 * |	GPIO B Peripheral (0x23)     |    PINB = 0x23    |    DDRB = 0x24    |    PORTB = 0x25   |
 * |---------------------------------|-------------------|-------------------|-------------------|
 * |	GPIO C Peripheral (0x26)	 |    PINC = 0x26    |    DDRC = 0x27    |    PORTC = 0x28   |
 * |---------------------------------|-------------------|-------------------|-------------------|
 * |	GPIO D Peripheral (0x29)     |    PIND = 0x29    |    DDRD = 0x2A    |    PORTD = 0x2B   |
 * |---------------------------------|-------------------|-------------------|-------------------|
 * |	GPIO D Peripheral (0x2C)     |    PINE = 0x2C    |    DDRE = 0x2D    |    PORTE = 0x2E   |
 * |---------------------------------|-------------------|-------------------|-------------------|
 * |	GPIO F Peripheral (0x2F)     |    PINF = 0x2F    |    DDRF = 0x30    |    PORTF = 0x31   |
 * -----------------------------------------------------------------------------------------------
 * 
 * 
 * Notice how each GPIO Peripheral is evenly incremented by 0x03. For example GPIO B Peripheral begins at 0x23, 
 * GPIO C Peripheral begins at 0x26, GPIO D Peripheral begins at 0x29, etc. Also notice that the order of PINx, 
 * DDRx, and PORTx registers are the same for each peripheral. Therefore we can use the following formulas to 
 * access all registers:
 * 
 * 
 * PINx  = (0x20 + (0x03 * BSP_GET_PORT(KB_PIN_Pxx)))
 * DDRx  = (0x21 + (0x03 * BSP_GET_PORT(KB_PIN_Pxx)))
 * PORTx = (0x22 + (0x03 * BSP_GET_PORT(KB_PIN_Pxx)))
 * 
 * 
 * The BSP_GET_PORT() macro is explained in detail within the file description of bsp_pin_def.h. To summarize,
 * each Microcontroller defines it's available GPIOs within it's kb_pin_def.h file. This produces a set of 
 * KB_PIN_Pxx definitions that can be input into BSP_GET_PORT() and BSP_GET_PIN() macros. Inputting this into 
 * BSP_GET_PORT() returns the hardware-agnostic Port Information: 0 = PORTA, 1 = PORTB, 2 = PORTC,.... 25 = PORTZ. 
 * All we are doing is mapping this value to the correct I/O Address with the formulas above.
 * 
 * It is guaranteed that only values 1 to 5 inclusive will be returned because only GPIO Peripheral B to GPIO 
 * Peripheral F are available on ATMega16U4/ATMega32U4. I.e. only KB_PIN_PBx to KB_PIN_PFx are defined within 
 * kb_pin_def.h for ATMega16U4/ATMega32U4.
 * 
 * To make things a little easier to read, the values returned from the BSP_GET_PORT() and BSP_GET_PIN() macros
 * are stored in local variables instead of cramming everything into one line. This does not add any additional
 * overhead. The code disassembles to the exact same Machine Instructions as the single-line equivalent which 
 * would use no local variables. See Images in doc/images/bsp/avr/atmega32u4/
 * 
 * To put everything together, the full example of a DDRx Register Write for KB_PIN_PB4 is shown below:
 * 
 * ```
 * uint8_t port = BSP_GET_PORT(KB_PIN_PB4);
 * uint8_t pin = BSP_GET_PIN(KB_PIN_PB4);
 * *( (volatile uint8_t *)(0x21 + (0x03 * port)) ) &= ~(1U << pin);
 * ```
 * 
 * This simplifies to the following:
 * ```
 * uint8_t port = 1;
 * uint8_t pin = 4;
 * *( (volatile uint8_t *)(0x21 + (0x03 * 1)) ) &= ~(1U << 4);
 * ```
 * 
 * Which evaluates to:
 * ```
 * *( (volatile uint8_t *)(0x24) ) &= ~(1U << 4);
 * ```
 * 
 * Notice how this correctly maps to DDRB register.
 * 
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef BSP_GPIO_H_
#define BSP_GPIO_H_


/* STD-C Libraries */
#include <stdbool.h>
#include <stdint.h>

/* Available GPIOs on ATMega16U4 and ATMega32U4 */
#include "kb_pin_def.h"



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------ PUBLIC FUNCTIONS --------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Sets the ATMega16U4/ATMega32U4 GPIO connected to the Keyboard Row/Column as an Input HiZ. 
 * 
 * @attention The user MUST have external pullup or pulldown resistors populated on their Keyboard PCB
 * in order to use this configuration.
 * 
 * @param KB_PIN The ATMega16U4/ATMega32U4 GPIO connected to the Keyboard Row/Column. This MUST be one of 
 * the KB_PIN_Pxx definitions found in kb_pin_def.h. See the file descriptions of kb_pin_def.h within the 
 * atmega16u4/atmega32u4 drivers folder and bsp_pin_def.h for more details.
 */
static inline void BSP_GPIO_Set_Pin_Type_Input_HiZ(KB_PINSIZE_T KB_PIN);
static inline void BSP_GPIO_Set_Pin_Type_Input_HiZ(KB_PINSIZE_T KB_PIN)
{
	uint8_t port = BSP_GET_PORT(KB_PIN);
	uint8_t pin = BSP_GET_PIN(KB_PIN);

	/* DDRx Write - see file description for more details. */
	*( (volatile uint8_t *)(0x21 + (0x03 * port)) ) &= ~(1U << pin);
}


/**
 * @brief Sets the ATMega16U4/ATMega32U4 GPIO connected to the Keyboard Row/Column as an Input with an Internal 
 * Pullup Resistor. 
 * 
 * @attention The PUD bit in the MCUCR Register MUST be written to 0 to enable internal pullups. This
 * function assumes this has already beeen done. See Section 10.4.1 MCU Control Register – MCUCR of
 * the ATMega16U4/ATMega32U4 datasheet for more details.
 * 
 * @param KB_PIN The ATMega16U4/ATMega32U4 GPIO connected to the Keyboard Row/Column. This MUST be one of 
 * the KB_PIN_Pxx definitions found in kb_pin_def.h. See the file descriptions of kb_pin_def.h within the 
 * atmega16u4/atmega32u4 drivers folder and bsp_pin_def.h for more details.
 */
static inline void BSP_GPIO_Set_Pin_Type_Input_Pullup(KB_PINSIZE_T KB_PIN);
static inline void BSP_GPIO_Set_Pin_Type_Input_Pullup(KB_PINSIZE_T KB_PIN)
{
	uint8_t port = BSP_GET_PORT(KB_PIN);
	uint8_t pin = BSP_GET_PIN(KB_PIN);

	/* DDRx and PORTx Write - see file description for more details. */
	*( (volatile uint8_t *)(0x21 + (0x03 * port)) ) &= ~(1U << pin);
	*( (volatile uint8_t *)(0x22 + (0x03 * port)) ) |= (1U << pin);
}


/*----------------------------------------------------------------------------------------------------------------*/
/*--------------- Internal Pulldown Resistors are NOT supported on ATMega16U4/ATMega32U4. Therefore --------------*/
/*---------- BSP_GPIO_Set_Pin_Type_Input_Pulldown() is NOT defined to force a compilation error if this ----------*/
/*----------------------------- used when compiling for ATMega16U4 or ATMega32U4 ---------------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Sets the ATMega16U4/ATMega32U4 GPIO connected to the Keyboard Row/Column as an Output Pushpull.
 * 
 * @param KB_PIN The ATMega16U4/ATMega32U4 GPIO connected to the Keyboard Row/Column. This MUST be one of 
 * the KB_PIN_Pxx definitions found in kb_pin_def.h. See the file descriptions of kb_pin_def.h within the 
 * atmega16u4/atmega32u4 drivers folder and bsp_pin_def.h for more details.
 */
static inline void BSP_GPIO_Set_Pin_Type_Output_Push_Pull(KB_PINSIZE_T KB_PIN);
static inline void BSP_GPIO_Set_Pin_Type_Output_Push_Pull(KB_PINSIZE_T KB_PIN)
{
	uint8_t port = BSP_GET_PORT(KB_PIN);
	uint8_t pin = BSP_GET_PIN(KB_PIN);

	/* DDRx Write - see file description for more details. */
	*( (volatile uint8_t *)(0x21 + (0x03 * port)) ) |= (1U << pin);
}


/**
 * @brief Sets the ATMega16U4/ATMega32U4 GPIO connected to the Keyboard Row/Column HIGH.
 * 
 * @attention The pin must be configured as an Output Pushpull by calling BSP_GPIO_Set_Pin_Type_Output_Push_Pull() 
 * before this function can be used.
 * 
 * @param KB_PIN The ATMega16U4/ATMega32U4 GPIO connected to the Keyboard Row/Column. This MUST be one of 
 * the KB_PIN_Pxx definitions found in kb_pin_def.h. See the file descriptions of kb_pin_def.h within the 
 * atmega16u4/atmega32u4 drivers folder and bsp_pin_def.h for more details.
 */
static inline void BSP_GPIO_Set_Output_Push_Pull_High(KB_PINSIZE_T KB_PIN);
static inline void BSP_GPIO_Set_Output_Push_Pull_High(KB_PINSIZE_T KB_PIN)
{
	uint8_t port = BSP_GET_PORT(KB_PIN);
	uint8_t pin = BSP_GET_PIN(KB_PIN);

	/* PORTx Write - see file description for more details. */
	*( (volatile uint8_t *)(0x22 + (0x03 * port)) ) |= (1U << pin);
}


/**
 * @brief Sets the ATMega16U4/ATMega32U4 GPIO connected to the Keyboard Row/Column LOW.
 * 
 * @attention The pin must be configured as an Output Pushpull by calling BSP_GPIO_Set_Pin_Type_Output_Push_Pull() 
 * before this function can be used.
 * 
 * @param KB_PIN The ATMega16U4/ATMega32U4 GPIO connected to the Keyboard Row/Column. This MUST be one of 
 * the KB_PIN_Pxx definitions found in kb_pin_def.h. See the file descriptions of kb_pin_def.h within the 
 * atmega16u4/atmega32u4 drivers folder and bsp_pin_def.h for more details.
 */
static inline void BSP_GPIO_Set_Output_Push_Pull_Low(KB_PINSIZE_T KB_PIN);
static inline void BSP_GPIO_Set_Output_Push_Pull_Low(KB_PINSIZE_T KB_PIN)
{
	uint8_t port = BSP_GET_PORT(KB_PIN);
	uint8_t pin = BSP_GET_PIN(KB_PIN);

	/* PORTx Write - see file description for more details. */
	*( (volatile uint8_t *)(0x22 + (0x03 * port)) ) &= ~(1U << pin);
}


/*----------------------------------------------------------------------------------------------------------------*/
/*------------------ Open Drain Outputs are NOT supported on ATMega16U4 or ATMega32U4. Therefore -----------------*/
/*------------- BSP_GPIO_Set_Pin_Type_Output_Open_Drain(), BSP_GPIO_Set_Output_Open_Drain_High(), and ------------*/
/*----------- BSP_GPIO_Set_Output_Open_Drain_LOW() are NOT defined to force a compilation error if this is -------*/
/*---------------------------- used when compiling for ATMega16U4 or ATMega32U4 ----------------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Takes a raw reading of the ATMega16U4/ATMega32U4 GPIO Input connected to the Keyboard Row/Column.
 * 
 * @attention The pin must be configured as an Input by calling BSP_GPIO_Set_Pin_Type_Input_HiZ()
 * or BSP_GPIO_Set_Pin_Type_Input_Pullup() before this function can be used.
 * 
 * @param KB_PIN The ATMega16U4/ATMega32U4 GPIO connected to the Keyboard Row/Column. This MUST be one of 
 * the KB_PIN_Pxx definitions found in kb_pin_def.h. See the file descriptions of kb_pin_def.h within the 
 * atmega16u4/atmega32u4 drivers folder and bsp_pin_def.h for more details.
 * 
 * @return True for a HIGH reading. False for a LOW reading. Note that this function only returns
 * the raw reading - it does not convert this into Keypress logic as a HIGH or LOW reading can 
 * correspond to a press depending on the Keyboard Configuration. The Virtual Calls in the Rowcol
 * Class handle this.
 */
static inline bool BSP_GPIO_Read(KB_PINSIZE_T KB_PIN);
static inline bool BSP_GPIO_Read(KB_PINSIZE_T KB_PIN)
{
	uint8_t port = BSP_GET_PORT(KB_PIN);
	uint8_t pin = BSP_GET_PIN(KB_PIN);

	/* PINx Read - see file description for more details. */
	return ( *( (volatile uint8_t *)(0x20 + (0x03 * port)) ) & (1U << pin) );
}


#endif /* BSP_GPIO_H_ */
