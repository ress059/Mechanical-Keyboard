/** @file keyscan.c
*
* @brief Keyboard scanning logic to detect keypresses. Author: Ian Ress
*
*/

#include "keyscan.h"

static set_row_high(void);
static set_column_hi(void);
static clear_buf(uint8_t * buf, uint8_t bufsize);
static buf_init(uint8_t * buf, uint8_t bufsize);

static buf_init(uint8_t * buf, uint8_t bufsize) {
	memset(buf, '\0', bufsize*sizeof(char));
}

void keyscan(void) {
    	/*
	*1) Set COL0 LOW to scan it
	*2) Read Rows 0 to 3
	*3) If Row input = LOW, register a press
	*4) Store column and row index press occurred
	*5) Map to keycode matrix to figure out which key was pressed.
	*6) Store in uint8_t buffer
	*7) Repeat for rest of columns
	*8) Send buffer over USB 
	*/
}

