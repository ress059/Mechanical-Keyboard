/*
 * Keyboard.h
 *
 * Created: 2/6/2022 6:41:30 PM
 *  Author: ianjr
 */ 

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

/*-----------------------------------Includes-------------------------------*/
#include <stdbool.h>
#include <stddef.h>
#include <xc.h> //TODO - delete after debugging
#include <util/delay.h> //TODO - delete after debugging

/*-----------------------------------GPIO Registers-------------------------------*/
typedef struct{
	volatile uint8_t PINX;
	volatile uint8_t DDRX;
	volatile uint8_t PORTX;
} GPIOTypeDef;

/*-----------------------------------Defines-------------------------------*/
#define GPIOB							((GPIOTypeDef*) 0x23)
#define GPIOC							((GPIOTypeDef*) 0x26)
#define GPIOD							((GPIOTypeDef*) 0x29)
#define GPIOE							((GPIOTypeDef*) 0x2C)
#define GPIOF							((GPIOTypeDef*) 0x2F)

#define _PORTB							(1U<<8)
#define _PORTC							(1U<<9)
#define _PORTD							(1U<<10)
#define _PORTE							(1U<<11)
#define _PORTF							(1U<<12)

#define _PIN0							(1U<<0)
#define _PIN1							(1U<<1)
#define _PIN2							(1U<<2)
#define _PIN3							(1U<<3)
#define _PIN4							(1U<<4)
#define _PIN5							(1U<<5)
#define _PIN6							(1U<<6)
#define _PIN7							(1U<<7)

#define _PB0							(_PORTB | _PIN0)
#define _PB1							(_PORTB | _PIN1)
#define _PB2							(_PORTB | _PIN2)
#define _PB3							(_PORTB | _PIN3)
#define _PB4							(_PORTB | _PIN4)
#define _PB5							(_PORTB | _PIN5)
#define _PB6							(_PORTB | _PIN6)
#define _PB7							(_PORTB | _PIN7)

#define _PC6							(_PORTC | _PIN6)
#define _PC7							(_PORTC | _PIN7)

#define _PD0							(_PORTD | _PIN0)
#define _PD1							(_PORTD | _PIN1)
#define _PD2							(_PORTD | _PIN2)
#define _PD3							(_PORTD | _PIN3)
#define _PD4							(_PORTD | _PIN4)
#define _PD5							(_PORTD | _PIN5)
#define _PD6							(_PORTD | _PIN6)
#define _PD7							(_PORTD | _PIN7)

#define _PE2							(_PORTE | _PIN2)
#define _PE6							(_PORTE | _PIN6)

#define _PF0							(_PORTF | _PIN0)
#define _PF1							(_PORTF | _PIN1)
#define _PF4							(_PORTF | _PIN4)
#define _PF5							(_PORTF | _PIN5)
#define _PF6							(_PORTF | _PIN6)
#define _PF7							(_PORTF | _PIN7)

#define INVALID_PIN_NUMBER				8U
#define MCU_CLOCK						2000000 //Hz

/*-----------------------------------Macros-------------------------------*/
#define GET_PIN_NUMBER(X)				(((X) & _PIN0) ? 0U : \
										((X) & _PIN1) ? 1U : \
										((X) & _PIN2) ? 2U : \
										((X) & _PIN3) ? 3U : \
										((X) & _PIN4) ? 4U : \
										((X) & _PIN5) ? 5U : \
										((X) & _PIN6) ? 6U : \
										((X) & _PIN7) ? 7U : INVALID_PIN_NUMBER)\
											

#define GET_MEMORY_ADDRESS(X)			(((X) & _PORTB) ? GPIOB : \
										((X) & _PORTC) ? GPIOC : \
										((X) & _PORTD) ? GPIOD : \
										((X) & _PORTE) ? GPIOE : \
										((X) & _PORTF) ? GPIOF : NULL)


/*-----------------------------------Enums-------------------------------*/
typedef enum{
	INPUT,
	OUTPUT,
	INPUT_PULLUP
} ModeTypeDef;

typedef enum{
	HI_Z,
	HIGH,
	LOW,
	INVALID
} StateTypeDef;

/*-----------------------------------Current pin configuration-------------------------------*/

/*
*	COL1 = PF0
*	COL2 = PF1
*	COL3 = PF4
*	COL4 = PF5
*	COL5 = PF6
*	COL6 = PF7
*
*	COL7 = PC7
*	COL8 = PC6
*	
*	COL9 = PB6
*	COL10 = PB5
*	COL11 = PB4
*
*	COL12 = PD7
*	COL13 = PD6
*	COL14 = PD4
*	COL15 = PD5
*	
*	ROW1 = PD0
*	ROW2 = PD1
*	ROW3 = PD2
*	ROW4 = PD3
*/


/*-----------------------------------Prototypes-------------------------------*/
void keyboardInit(void);
void keyScan(void);

#endif /* KEYBOARDHID_H_ */