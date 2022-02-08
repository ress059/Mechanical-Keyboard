/*
 * Keyboard.c
 *
 * Created: 2/6/2022 7:23:27 PM
 *  Author: ianjr
 */ 
#include "Keyboard.h"
#include <stdbool.h>

static void SetColumn(int index, bool state);

PinNumber_TypeDef RowPins[ROW_PINS] = ROW_PINS;
PinNumber_TypeDef ColumnPins[NUM_COLUMNS] = COLUMN_PINS;

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

void begin(){
	//Row input
	DDRD &= ~((1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0));
	PORTD |= ((1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0)); //enable PULL-UP resistors on rows
	
	//Column outputs
	DDRF |= ((1<<DDF7) | (1<<DDF6) | (1<<DDF5) | (1<<DDF4) | (1<<DDF1) | (1<<DDF0));
	DDRC |= ((1<<DDC7) | (1<<DDC6));
	DDRB |= ((1<<DDB6) | (1<<DDB5) | (1<<DDB4));
	DDRD |= ((1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4));
	
	//Set all columns HIGH (LOW means we are scanning that column for press)
	PORTF |= ((1<<PORTF7) | (1<<PORTF6) | (1<<PORTF5) | (1<<PORTF4) | (1<<PORTF1) | (1<<PORTF0));
	PORTC |= ((1<<PORTC7) | (1<<PORTC6));
	PORTB |= ((1<<PORTB6) | (1<<PORTB5) | (1<<PORTB4));
	PORTD |= ((1<<PORTD7) | (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4));
}

void keyscan(){
	/*
	*1) Set COL1 LOW to scan it
	*2) Read Rows 1 to 4
	*3) If Row input = LOW, register a press
	*4) Store column and row index press occured
	*5) Map to keycode matrix to figure out which key was pressed.
	*6) Store in uint8_t buffer
	*7) Repeat for rest of columns
	*8) Send buffer over USB 
	*/
	

}


static void SetColumn(int index, bool state){ //Start index = 0
	PinNumber_TypeDef Pin = ColumnPins[index];
	
	if ((index >= NUM_COLUMNS) | (index <= 0)){
		return;
	}
	
	else{
		switch(Pin){
			case: PORTB_
				//do stuff
				break;
				
			case: PORTC_
				//do stuff
				break;
				
			case: PORTD_
				//do stuff
				break;
			
			case: PORTE_
				//do stuff
				break;
				
			case: PORTF_
				//do stuff
				break;
		}
	}
	//COL1, COL3
}