/*
 * UserConfig.h
 *
 * Created: 2/8/2022 11:30:01 AM
 *  Author: ianjr
 */ 

#ifndef USERCONFIG_H_
#define USERCONFIG_H_

/*-----------------------------------Includes-------------------------------*/
#include <Keyboard.h>

/*-----------------------------------User Defines-----------------------------*/
/*Configure your keyboard settings here. Ensure the number of entries in 
* KEYBOARD_ROW_PINS and KEYBOARD_COLUMN_PINS equals NUM_ROWS and NUM_COLUMNS.
* 
*/
#define DEBOUNCE_TIME				5 //ms
#define NUM_ROWS					4
#define NUM_COLUMNS					14

#define KEYBOARD_ROW_PINS			{_PD0, _PD1, _PD2, _PD3} //TODO - add _PD3 and PD2 after debugging
#define KEYBOARD_COLUMN_PINS		{_PF0, _PF1, _PF4, _PF5, _PF6, _PF7, _PC7, _PC6, _PB6, _PB5, _PB4, _PD6, _PD4, _PD5} //TODO - add _PD7 after testing
	
#define KEY_LAYOUT
	
#endif /* USERCONFIG_H_ */