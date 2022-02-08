/*
 * main.c
 *
 * Created: 2/1/2022 11:55:36 AM
 *  Author: ianjr
 */ 

//#include <xc.h>
//#include<util/delay.h>
//#include "KeyboardHID.h"
//#include "Keycodes.h"

//LED = COL12 (PD7)
//CLOCK = 2MHz

const uint16_t Tim2_Output_Compare_Val = 15625;
const uint16_t Tim2_Start_Val = 0;
int a;

int main(void)
{
	DDRD |= (1<<DDD7);
	
	PRR0 &= ~(1<<PRTIM1); //enable TIM1
	TCCR1A = 0;
	TCCR1B = ((1<<WGM12) | (1<<CS12)); //256 prescalar, Clear timer on TOP where TOP = OCR1A. see pg. 133
	OCR1A = Tim2_Output_Compare_Val;
	TCNT1 = Tim2_Start_Val;
	
    while(1)
    {
		if(TIFR1 & (1<<OCF1A)){
			PORTD ^= (1<<PORTD7);
			TIFR1 |= (1<<OCF1A); //clear flag
		}
    }
}