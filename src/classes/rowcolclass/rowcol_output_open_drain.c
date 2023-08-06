/**
 * @file rowcol_output_open_drain.c
 * @author Ian Ress
 * @brief Rowcol Output Open Drain Class. Inherits the Base Rowcol Class and the Rowcol Output Class. Each Class Instance 
 * represents an individual Row/Column that is specifically used as an Open Drain Output that sets a Row/Column HIGH and LOW.
 * @version 0.1
 * @date 2023-07-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "rowcol_output_open_drain.h"



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------- VIRTUAL FUNCTION DECLARATIONS (PRIVATE) --------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Sets the GPIO connected to the Row/Column as an Open Drain Output. This is a wrapper function
 * that calls the GPIO Board Support Package. If the hardware target does not support Open Drain Outputs
 * then a compilation error will occur due to the function not being defined.
 */
static void Rowcol_Output_Open_Drain_Init(const Rowcol_Output_Open_Drain * const me);


/**
 * @brief Sets the GPIO connected to the Row/Column HIGH. This is a wrapper function that calls the GPIO
 * Board Support Package. If the hardware target does not support Open Drain Outputs then a compilation error 
 * will occur due to the function not being defined.
 */
static void Rowcol_Output_Open_Drain_Set_High(const Rowcol_Output_Open_Drain * const me);


/**
 * @brief Sets the GPIO connected to the Row/Column LOW. This is a wrapper function that calls the GPIO
 * Board Support Package. If the hardware target does not support Open Drain Outputs then a compilation error 
 * will occur due to the function not being defined.
 */
static void Rowcol_Output_Open_Drain_Set_Low(const Rowcol_Output_Open_Drain * const me);



/*--------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------- VIRTUAL FUNCTION DEFINITIONS (PRIVATE) --------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

static void Rowcol_Output_Open_Drain_Init(const Rowcol_Output_Open_Drain * const me)
{
    BSP_GPIO_Set_Pin_Type_Output_Open_Drain( ((const Rowcol *)me)->mcu_pin );
}


static void Rowcol_Output_Open_Drain_Set_High(const Rowcol_Output_Open_Drain * const me)
{
    BSP_GPIO_Set_Output_Open_Drain_High( ((const Rowcol *)me)->mcu_pin );
}


static void Rowcol_Output_Open_Drain_Set_Low(const Rowcol_Output_Open_Drain * const me)
{
    BSP_GPIO_Set_Output_Open_Drain_Low( ((const Rowcol *)me)->mcu_pin );
}



/*--------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------- PUBLIC FUNCTIONS ----------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

bool Rowcol_Output_Open_Drain_Ctor(Rowcol_Output_Open_Drain * const me, KB_PINSIZE_T mcu_pin_0)
{
    bool success;

    /**
     * Ensure only one VTABLE is stored in ROM so the overhead is only ONE VTABLE for each 
     * Class declaration and a VPTR in RAM for each Class Instance created.
     */
    static const struct Rowcol_Output_VTABLE rowcol_output_open_drain_vtable = 
    {
        .super.init     = (void (*)(const Rowcol * const me))&Rowcol_Output_Open_Drain_Init,
        .set_high       = (void (*)(const Rowcol_Output * const me))&Rowcol_Output_Open_Drain_Set_High,
        .set_low        = (void (*)(const Rowcol_Output * const me))&Rowcol_Output_Open_Drain_Set_Low
    };

    if (me != (Rowcol_Output_Open_Drain *)0)
    {
        success = Rowcol_Output_Ctor(&me->super, mcu_pin_0);

        /**
         * @warning This MUST be done only AFTER the Super Class Constructor is called: 
         * Override Rowcol_Init() with Rowcol_Output_Open_Drain_Init(). Note how Rowcol_Init_VCALL()
         * now calls Rowcol_Output_Open_Drain_Init(), Rowcol_Output_Set_High_VCALL() calls 
         * Rowcol_Output_Open_Drain_Set_High(), and Rowcol_Output_Set_Low_VCALL() calls
         * Rowcol_Output_Open_Drain_Set_Low().
         */
        ((Rowcol *)me)->VPTR = (const struct Rowcol_VTABLE *)&rowcol_output_open_drain_vtable;
    }

    else
    {
        success = false;
    }

    return success;
}
