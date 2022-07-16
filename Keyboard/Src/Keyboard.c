/*
 * Keyboard.c
 *
 * Created: 2/6/2022 7:23:27 PM
 *  Author: ianjr
 */ 

/*-----------------------------------Includes-------------------------------*/
#include <Keyboard.h>
#include <UserConfig.h>

/*--------------------------------Private Variables--------------------------*/
const uint16_t ROW_PINS[NUM_ROWS] = KEYBOARD_ROW_PINS;
const uint16_t COLUMN_PINS[NUM_COLUMNS] = KEYBOARD_COLUMN_PINS;
const uint16_t KEY_MATRIX[NUM_ROWS][NUM_COLUMNS] = KEY_LAYOUT;
int keypress_index[2]; //TODO - delete after debugging

/*-----------------------------Private Function Prototypes--------------------*/
static void SetColumn(int index, StateTypeDef state);
static void SetRow(int index, ModeTypeDef mode);
static StateTypeDef ReadRow(int index);

void keyboardInit(){
	cli();
	/* Disable JTAG or else PF4, PF5, PF6, and PF7 will be pulled up HIGH permanently */
	MCUCR |= (1<<7);
	MCUCR |= (1<<7);	
	
	for (int i = 0; i < NUM_ROWS; i++){
		SetRow(i, INPUT_PULLUP);
	}
	
	for (int i = 0; i < NUM_COLUMNS; i++){
		SetColumn(i, HI_Z);
	}
	
	DDRD |= (1<<DDD7); //TODO - delete after testing debug LED*/
	sei();
}

void keyScan(){
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
	
	for (int i = 0; i < NUM_COLUMNS; i++){
		SetColumn(i, LOW);
		
		for (int j = 0; j < NUM_ROWS; j++){ 
			if (ReadRow(j) == LOW){
				//record the index
				keypress_index[0] = j;
				keypress_index[1] = i;
				//PORTD ^= (1<<PORTD7); //TODO - delete after testing debug LED
				//_delay_ms(1000);
			}
		}
		SetColumn(i, HI_Z);
	}
}


static void SetRow(int index, ModeTypeDef mode){
	if ((index >= NUM_ROWS) | (index < 0)){
		return;
	}
	
	unsigned int pin = ROW_PINS[index];
	unsigned int pin_number = GET_PIN_NUMBER(pin);
	GPIOTypeDef* GPIO = GET_MEMORY_ADDRESS(pin);
	
	if ((pin_number == INVALID_PIN_NUMBER) | (GPIO == NULL)){
		return;
	}
	
	switch (mode){
		case INPUT:
			GPIO->DDRX &= ~(1<<pin_number);
			GPIO->PORTX &= ~(1<<pin_number);
			break;
		
		case INPUT_PULLUP:
			GPIO->DDRX &= ~(1<<pin_number);
			GPIO->PORTX |= (1<<pin_number);
			break;
		
		default:
			break;
	}
}

static void SetColumn(int index, StateTypeDef state){ //Start index = 0
	if ((index >= NUM_COLUMNS) | (index < 0)){
		return;
	}
	
	unsigned int pin = COLUMN_PINS[index];	
	unsigned int pin_number = GET_PIN_NUMBER(pin);
	GPIOTypeDef* GPIO = GET_MEMORY_ADDRESS(pin);
	
	if ((pin == INVALID_PIN_NUMBER) | (GPIO == NULL)){
		return;
	}
	
	switch (state){ //Hi Z to prevent short circuits between columns
		case HI_Z:
			GPIO->DDRX &= ~(1<<pin_number); //DDR set to 0 first so input pullup still enabled in intermediate state if PORT is HIGH
			GPIO->PORTX &= ~(1<<pin_number);
			break;
		
		case LOW:
			GPIO->DDRX |= (1<<pin_number);
			GPIO->PORTX &= ~(1<<pin_number);
			break;
		
		default:
			break;
	}
}

/* 10.2.4 - pg. 69 reading I/O */
static StateTypeDef ReadRow(int index){ //Start index = 0
	if ((index >= NUM_ROWS) | (index < 0)){
		return INVALID;
	}
		
	unsigned int pin = ROW_PINS[index];
	unsigned int pin_number = GET_PIN_NUMBER(pin);
	GPIOTypeDef* GPIO = GET_MEMORY_ADDRESS(pin);
	
	if ((pin == INVALID_PIN_NUMBER) | (GPIO == NULL)){
		return INVALID;
	}
	
	if (!(GPIO->PINX & (1<<pin_number))){ //key press
		return LOW;
	}
	else{
		return HIGH;
	}
}
