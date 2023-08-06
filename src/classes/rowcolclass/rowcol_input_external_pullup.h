/**
 * @file rowcol_input_external_pullup.h
 * @author Ian Ress
 * @brief Rowcol Input External Pullup Class. Inherits Base Rowcol Class and Input Rowcol Class. Each Class
 * Instance represents a Row/Column that uses an Input with External Pullup Resistors to detect Keypresses.
 * @version 0.1
 * @date 2023-07-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef ROWCOL_INPUT_EXTERNAL_PULLUP_CLASS_H_
#define ROWCOL_INPUT_EXTERNAL_PULLUP_CLASS_H_


/* Inherit Rowcol Input Class which inherits Base Rowcol Class */
#include "rowcol_input.h"



/*--------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------- ROWCOL INPUT EXTERNAL PULLUP CLASS ------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief The Rowcol Input External Pullup Class. Inherits the Base Rowcol Class and the Input Rowcol Class. Each 
 * Class Instance represents a Row/Column that uses an Input with External Pullup Resistors to detect Keypresses.
 */
typedef struct
{
    /* Inherit Rowcol Input Class which inherits Base Rowcol Class */
    Rowcol_Input super;

    /* Additional SubClass Members */
} Rowcol_Input_External_Pullup;



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------ PUBLIC FUNCTIONS --------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Rowcol Input External Pullup Class Constructor. Inherits the Base Rowcol Class and the Input Rowcol Class.
 * 
 * @param me Pointer to an instance of the Rowcol Input External Pullup Class. Note that SubClasses that inherit 
 * this Class will explicitly upcast to a (Rowcol_Input_External_Pullup *) to inherit this function in their own 
 * Constructors. This is guaranteed to be a legal and safe operation because the C Standard mandates that the first 
 * member of a struct and the struct itself share the same memory address. Note however that DOWNCASTING is NOT a 
 * safe operation and is undefined behavior. WARNING: The caller should also ensure this is not NULL.
 * @param mcu_pin_0 The microcontroller Port and Pin connected to this Row/Column. E.g. KB_PIN_PB1, KB_PIN_PC5, 
 * etc. Each microcontroller has a GPIO Board Support Package that defines these keys - therefore a compilation
 * error will occur if a pin the target MCU does not support is used.
 * @param keys0 Array of Key Classes. This is the actual keymap connected to the Row/Column. Storing an array
 * of Key Classes allows the user to customize each individual key.
 * @param length0 The number of keys that are connected to the Row/Column. WARNING: This MUST be equal to 
 * the length of the array pointed to by parameter keys0.
 * 
 * @return True if Constructor was successful. False if failed.
 */
bool Rowcol_Input_External_Pullup_Ctor(Rowcol_Input_External_Pullup * const me, KB_PINSIZE_T mcu_pin_0, const Key ** const keys0, uint8_t length0);


#endif /* ROWCOL_INPUT_External_PULLUP_CLASS_H_ */
