/*
 * main.c
 *
 * Created: 2/1/2022 11:55:36 AM
 *  Author: ianjr
 */ 

//#include <util/delay.h>
#include "Keyboard.h"
#include "UserConfig.h"
//LED = COL12 (PD7)

int main(void)
{
	keyboardInit();
    while(1)
    {
		keyScan();
		if ((keypress_index[0] == 1) & (keypress_index[1] == 2)){//S18
			PORTD ^= (1<<PORTD7);
			_delay_ms(1000);
		}		 
    }
}
