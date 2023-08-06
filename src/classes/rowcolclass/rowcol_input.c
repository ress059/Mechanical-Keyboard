/**
 * @file rowcol_input.c
 * @author Ian Ress
 * @brief Rowcol Input Class. Inherits the Base Rowcol Class. Each Class Instance represents an individual
 * Row/Column that is specifically used as an Input to detect Keypresses. Note that the other corresponding
 * Row/Column must be an Output. For example if Rows are assigned as Inputs then Columns must be assigned as
 * Outputs and vise-versa.
 * @version 0.1
 * @date 2023-07-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "rowcol_input.h"



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------- VIRTUAL FUNCTION DECLARATIONS (PRIVATE) --------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Does nothing since the initialization process is unknown until we know the specific pin configuration - 
 * Internal Input Pullup, Internal Input Pulldown, External Input Pullup, or External Input Pulldown.
 */
static void Rowcol_Input_Init(const Rowcol_Input * const me);


/**
 * @brief Does nothing since either a HIGH or LOW reading can register a keypress depending on the pin
 * configuration - Internal Input Pullup, Internal Input Pulldown, External Input Pullup, or External 
 * Input Pulldown. Always returns that a press was not detected.
 */
static bool Rowcol_Input_Is_Key_Pressed(const Rowcol_Input * const me);



/*--------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------- VIRTUAL FUNCTION DEFINITIONS (PRIVATE) --------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

static void Rowcol_Input_Init(const Rowcol_Input * const me)
{
    (void)me;
}


static bool Rowcol_Input_Is_Key_Pressed(const Rowcol_Input * const me)
{
    (void)me;
    return false;
}



/*--------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------- PUBLIC FUNCTIONS ----------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

bool Rowcol_Input_Ctor(Rowcol_Input * const me, KB_PINSIZE_T mcu_pin_0, const Key ** const keys0, uint8_t length0)
{
    bool success;

    /**
     * Ensure only one VTABLE is stored in ROM so the overhead is only ONE VTABLE for each 
     * Class declaration and a VPTR in RAM for each Class Instance created.
     */
    static const struct Rowcol_Input_VTABLE rowcol_input_vtable = 
    {
        .super.init         = (void (*)(const Rowcol * const me))&Rowcol_Input_Init,
        .is_key_pressed     = &Rowcol_Input_Is_Key_Pressed
    };

    if ((me != (Rowcol_Input *)0) && (keys0 != (Key *)0) && (length0 != 0))
    {
        #warning "Should Key Class constructor be called on keys0 array?"
        #warning "Is it possible to have a row/column with no keys? Should this be supported?"
        success = Rowcol_Ctor(&me->super, mcu_pin_0);

        /**
         * @warning This MUST be done only AFTER the Super Class Constructor is called: 
         * Override Rowcol_Init() with Rowcol_Input_Init(). Note how Rowcol_Init_VCALL()
         * now calls Rowcol_Input_Init() and Rowcol_Input_Is_Key_Pressed_VCALL() calls
         * Rowcol_Input_Is_Key_Pressed().
         */
        ((Rowcol *)me)->VPTR    = (const struct Rowcol_VTABLE *)&rowcol_input_vtable;
        me->keys                = keys0;
        me->length              = length0;
    }

    else
    {
        success = false;
    }

    return success;
}
