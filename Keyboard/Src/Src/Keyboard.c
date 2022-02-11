/*
 * Keyboard.c
 *
 * Created: 2/6/2022 7:23:27 PM
 *  Author: ianjr
 */ 

/*-----------------------------------Includes-------------------------------*/
#include <Keyboard.h>
#include <UserConfig.h>

/*-----------------------------Private Function Prototypes--------------------*/
static void SetColumn(int index, bool state);
static void pinMode(uint16_t Pin, ModeTypeDef Mode);
static State_TypeDef readRow(uint8_t index);

void Keyboard_Init(){
	for (int i = 0; i < NUM_ROWS; i++){	
		pinMode(ROW_PINS[i], INPUT_PULLUP);
	}
	
	for (int i = 0; i < NUM_COLUMNS; i++){
		pinMode(COLUMN_PINS[i], OUTPUT);
		SetColumn(i, HIGH);
	}
}

void Keyscan(){
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
	
	for (int i = 0; i < NUM_COLUMNS; i++){
		SetColumn(COLUMN_PINS[i], LOW);
		
		for (int j = 0; j < NUM_ROWS; j++){
			
		}
	}
}


static void pinMode(uint16_t Pin, ModeTypeDef Mode){
	unsigned int Pin_Number = GET_PIN_NUMBER(Pin);
	GPIO_TypeDef* GPIO = GET_MEMORY_ADDRESS(Pin);
	
	if ((Pin_Number == INVALID_PIN_NUMBER) | (GPIO == NULL)){
		return;
	}
	
	switch (Mode){
		case INPUT:
			GPIO->DDRX &= ~(1<<Pin_Number);
		
		case INPUT_PULLUP:
			GPIO->DDRX &= ~(1<<Pin_Number);
			GPIO->PORTX |= (1<<Pin_Number);
		
		case OUTPUT:
			GPIO->DDRX |= (1<<Pin_Number);
	}
}

static void SetColumn(int index, State_TypeDef state){ //Start index = 0
	unsigned int Pin = COLUMN_PINS[index];	
	unsigned int Pin_Number = GET_PIN_NUMBER(Pin);
	GPIO_TypeDef* GPIO = GET_MEMORY_ADDRESS(Pin);
	
	if ((index >= NUM_COLUMNS) | (index < 0) | (Pin == INVALID_PIN_NUMBER) | (GPIO == NULL)){
		return;
	}
	
	if (GPIO->DDRX & (1<<Pin_Number)){ //verify pin is OUTPUT
		if (state == HIGH){
			GPIO->PORTX |= (1<<Pin_Number);
		}
		else if (state == LOW){
			GPIO->PORTX &= ~(1<<Pin_Number);
		}
	}
}

/* 10.2.4 - pg. 69 reading I/O */
static State_TypeDef readRow(int index){ 
	
	unsigned int Pin = ROW_PINS[index];
	unsigned int Pin_Number = GET_PIN_NUMBER(Pin);
	GPIO_TypeDef* GPIO = GET_MEMORY_ADDRESS(Pin);
	
	if ((index >= NUM_ROWS) | (index < 0) | (Pin == INVALID_PIN_NUMBER) | (GPIO == NULL)){
		return INVALID;
	}
	
	if (!(GPIO->PINX & (1<<Pin_Number))){ //key press
		return LOW;
	}
	else{
		return HIGH;
	}
}