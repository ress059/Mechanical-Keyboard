/*
 * Keyboard.h
 *
 * Created: 2/6/2022 6:41:30 PM
 *  Author: ianjr
 */ 

#ifndef 
#define KEYBOARD_H_

/*-----------------------------------Includes-------------------------------*/
//#include <avr/io.h>

/*-----------------------------------User Defines-------------------------------*/
#define NUM_ROWS			4
#define NUM_COLUMNS			15

#define ROW_PINS			{PD0, PD1, PD2, PD3}
#define COLUMN_PINS			{PF0, PF1, PF4, PF5, PF6, PF7, PC7, PC6, PB6, PB5, PB4, PD7, PD6, PD5}


/*-----------------------------------Driver Defines-------------------------------*/
#define PORTB_				0
#define PORTC_				1
#define PORTD_				2
#define PORTE_				3
#define PORTF_				4

/*1) Define Keyboard col to pins (PF0,...)
* 2) Create enum with PD5, PD6, PD7,...
 *2) Create struct for each pin storing DDRx, PINx, and PORTx addresses
 
*/

/*-----------------------------------Enums-------------------------------*/
typedef enum{
	PB0 = PORTB_,
	PB1 = PORTB_,
	PB2 = PORTB_,
	PB3 = PORTB_,
	PB4 = PORTB_,
	PB5 = PORTB_,
	PB6 = PORTB_,
	PB7 = PORTB_,
	
	PC6 = PORTC_,
	PC7 = PORTC_,
	
	PD0 = PORTD_,
	PD1 = PORTD_,
	PD2 = PORTD_,
	PD3 = PORTD_,
	PD4 = PORTD_,
	PD5 = PORTD_,
	PD6 = PORTD_,
	PD7 = PORTD_,
	
	PE2 = PORTE_,
	PE6 = PORTE_,
	
	PF0 = PORTF_,
	PF1 = PORTF_,
	PF4 = PORTF_,
	PF5 = PORTF_,
	PF6 = PORTF_,
	PF7 = PORTF_,
} PinNumber_TypeDef;


/*-----------------------------------Driver Defines-------------------------------*/
typedef struct{
	volatile uint8_t PIND;
	volatile uint8_t DDRD;
	volatile uint8_t PORTD;
} GPIOD_TypeDef;

#define GPIOD ((GPIOD_TypeDef*) 0x09)

(*(volatile uint8_t *)(mem_addr))

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
void begin(void);

void keyscan(void);

#endif /* KEYBOARDHID_H_ */