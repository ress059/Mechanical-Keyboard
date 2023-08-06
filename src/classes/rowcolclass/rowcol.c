/**
 * @file rowcol.c
 * @author Ian Ress
 * @brief The Row/Column Base Class. Each instance of this Class represent an individual Row or Column on the
 * Keyboard.
 * @version 0.1
 * @date 2023-07-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "rowcol.h"



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------- VIRTUAL FUNCTION DECLARATIONS (PRIVATE) --------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Does nothing since this is the Base Rowcol Class. The initialization process is unknown until we know 
 * the specific pin configuration - Internal Input Pullup, Internal Input Pulldown, External Input Pullup, 
 * External Input Pulldown, Output Pushpull, or Output Open Drain.
 */
static void Rowcol_Init(const Rowcol * const me);



/*--------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------- VIRTUAL FUNCTION DEFINITIONS (PRIVATE) --------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

static void Rowcol_Init(const Rowcol * const me)
{
    (void)me;
}



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------ PUBLIC FUNCTIONS --------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

bool Rowcol_Ctor(Rowcol * const me, KB_PINSIZE_T mcu_pin_0)
{
    bool success;

    /**
     * Ensure only one VTABLE is stored in ROM so the overhead is only ONE VTABLE for each 
     * Class declaration and a VPTR in RAM for each Class Instance created.
     */
    static const struct Rowcol_VTABLE rowcol_vtable = 
    {
        .init = &Rowcol_Init
    };

    if (me != (Rowcol *)0)
    {
        me->VPTR                = &rowcol_vtable;
        me->mcu_pin             = mcu_pin_0;
        success                 = true;
    }

    else
    {
        success = false;
    }

    return success;
}
