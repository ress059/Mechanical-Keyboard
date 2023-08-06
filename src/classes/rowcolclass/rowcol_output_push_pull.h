/**
 * @file rowcol_output_push_pull.h
 * @author Ian Ress
 * @brief Rowcol Output Push Pull Class. Inherits the Base Rowcol Class and the Rowcol Output Class. Each Class Instance 
 * represents an individual Row/Column that is specifically used as a Push Pull Output that sets a Row/Column HIGH and LOW.
 * @version 0.1
 * @date 2023-07-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef ROWCOL_OUTPUT_PUSH_PULL_CLASS_H_
#define ROWCOL_OUTPUT_PUSH_PULL_CLASS_H_


/* Inherit Rowcol Output Class which inherits Base Rowcol Class */
#include "rowcol_output.h"



/*--------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------- ROWCOL OUTPUT PUSH PULL CLASS ----------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Rowcol Output Push Pull Class. Inherits the Rowcol Output Class which inherits the Base Rowcol Class. 
 * Each Class Instance represents an individual Row/Column that is specifically used as a Push Pull Output that 
 * sets a Row/Column HIGH and LOW. Note that the Keyboard's layout is only stored in the Rowcol Input Class 
 * to avoid redundancy.
 */
typedef struct
{
    /* Inherit the Rowcol Output Class which inherits the Base Rowcol Class */
    Rowcol_Output super; 

    /* Additional SubClass Members */
} Rowcol_Output_Push_Pull;



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------ PUBLIC FUNCTIONS --------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Rowcol Output Push Pull Class Constructor. Inherits the Rowcol Output Class which inherits the 
 * Base Rowcol Class. 
 * 
 * @param me Pointer to an instance of the Rowcol Output Push Pull Class. Note that SubClasses that inherit 
 * this Class will explicitly upcast to a (Rowcol_Output_Push_Pull *) to inherit this function in their own 
 * Constructors. This is guaranteed to be a legal and safe operation because the C Standard mandates that 
 * the first member of a struct and the struct itself share the same memory address. Note however that 
 * DOWNCASTING is NOT a safe operation and is undefined behavior. WARNING: The caller should also ensure 
 * this is not NULL.
 * @param mcu_pin_0 The microcontroller Port and Pin connected to this Row/Column. E.g. KB_PIN_PB1, KB_PIN_PC5, 
 * etc. Each microcontroller has a GPIO Board Support Package that defines these keys - therefore a compilation
 * error will occur if a pin the target MCU does not support is used.
 * 
 * @return True if Constructor was successful. False if failed.
 */
bool Rowcol_Output_Push_Pull_Ctor(Rowcol_Output_Push_Pull * const me, KB_PINSIZE_T mcu_pin_0);


#endif /* ROWCOL_OUTPUT_PUSH_PULL_CLASS_H_ */
