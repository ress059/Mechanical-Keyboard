/**
 * @file rowcol_output.c
 * @author Ian Ress
 * @brief Rowcol Output Class. Inherits the Base Rowcol Class. Each Class Instance represents an individual
 * Row/Column that is specifically used as an Output that sets a Row/Column HIGH and LOW.
 * @version 0.1
 * @date 2023-07-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "rowcol_output.h"



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------- VIRTUAL FUNCTION DECLARATIONS (PRIVATE) --------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Does nothing since the initialization process is unknown until we know if the pin is Open Drain 
 * or Push Pull.
 */
static void Rowcol_Output_Init(const Rowcol_Output * const me);


/**
 * @brief Does nothing since this can correspond to a LOW or HIGH write depending on if the pin is Open Drain 
 * or Push Pull, as well as the internal GPIO block diagram.
 */
static void Rowcol_Output_Set_High(const Rowcol_Output * const me);


/**
 * @brief Does nothing since this can correspond to a LOW or HIGH write depending on if the pin is Open Drain 
 * or Push Pull, as well as the internal GPIO block diagram.
 */
static void Rowcol_Output_Set_Low(const Rowcol_Output * const me);



/*--------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------- VIRTUAL FUNCTION DEFINITIONS (PRIVATE) --------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

static void Rowcol_Output_Init(const Rowcol_Output * const me)
{
    (void)me;
}


static void Rowcol_Output_Set_High(const Rowcol_Output * const me)
{
    (void)me;
}


static void Rowcol_Output_Set_Low(const Rowcol_Output * const me)
{
    (void)me;
}



/*--------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------- PUBLIC FUNCTIONS ----------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

bool Rowcol_Output_Ctor(Rowcol_Output * const me, KB_PINSIZE_T mcu_pin_0)
{
    bool success;

    /**
     * Ensure only one VTABLE is stored in ROM so the overhead is only ONE VTABLE for each 
     * Class declaration and a VPTR in RAM for each Class Instance created.
     */
    static const struct Rowcol_Output_VTABLE rowcol_output_vtable = 
    {
        .super.init     = (void (*)(const Rowcol * const me))&Rowcol_Output_Init,
        .set_high       = &Rowcol_Output_Set_High,
        .set_low        = &Rowcol_Output_Set_Low
    };

    if (me != (Rowcol_Output *)0)
    {
        success = Rowcol_Ctor(&me->super, mcu_pin_0);

        /**
         * @warning This MUST be done only AFTER the Super Class Constructor is called: 
         * Override Rowcol_Init() with Rowcol_Output_Init(). Note how Rowcol_Init_VCALL()
         * now calls Rowcol_Output_Init(), Rowcol_Output_Set_High_VCALL() calls 
         * Rowcol_Output_Set_High(), and Rowcol_Output_Set_Low_VCALL() calls
         * Rowcol_Output_Set_Low().
         */
        ((Rowcol *)me)->VPTR = (const struct Rowcol_VTABLE *)&rowcol_output_vtable;
    }

    else
    {
        success = false;
    }

    return success;
}
