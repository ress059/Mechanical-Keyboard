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

/*-----------------------------------Globals-------------------------------*/
extern const uint16_t ROW_PINS[NUM_ROWS];
extern const uint16_t COLUMN_PINS[NUM_COLUMNS];

/*-----------------------------------User Defines-----------------------------*/
#define DEBOUNCE_TIME				5 //ms
#define NUM_ROWS					4
#define NUM_COLUMNS					15
	
#endif /* USERCONFIG_H_ */