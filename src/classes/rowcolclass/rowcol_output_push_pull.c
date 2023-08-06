/**
 * @file rowcol_output_push_pull.c
 * @author Ian Ress
 * @brief Rowcol Output Push Pull Class. Inherits the Base Rowcol Class and the Rowcol Output Class. Each Class Instance 
 * represents an individual Row/Column that is specifically used as a Push Pull Output that sets a Row/Column HIGH and LOW.
 * @version 0.1
 * @date 2023-07-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "rowcol_output_push_pull.h"



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------- VIRTUAL FUNCTION DECLARATIONS (PRIVATE) --------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Sets the GPIO connected to the Row/Column as a Push-pull Output. This is a wrapper function
 * that calls the GPIO Board Support Package. If the hardware target does not support Push-pull outputs
 * then a compilation error will occur due to the function not being defined.
 */
static void Rowcol_Output_Push_Pull_Init(const Rowcol_Output_Push_Pull * const me);


/**
 * @brief Sets the GPIO connected to the Row/Column HIGH. This is a wrapper function that calls the 
 * GPIO Board Support Package. If the hardware target does not support Push-pull outputs then a compilation 
 * error will occur due to the function not being defined.
 */
static void Rowcol_Output_Push_Pull_Set_High(const Rowcol_Output_Push_Pull * const me);


/**
 * @brief Sets the GPIO connected to the Row/Column LOW. This is a wrapper function that calls the 
 * GPIO Board Support Package. If the hardware target does not support Push-pull outputs then a compilation 
 * error will occur due to the function not being defined.
 */
static void Rowcol_Output_Push_Pull_Set_Low(const Rowcol_Output_Push_Pull * const me);



/*--------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------- VIRTUAL FUNCTION DEFINITIONS (PRIVATE) --------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

static void Rowcol_Output_Push_Pull_Init(const Rowcol_Output_Push_Pull * const me)
{
    BSP_GPIO_Set_Pin_Type_Output_Push_Pull( ((const Rowcol *)me)->mcu_pin );
}


static void Rowcol_Output_Push_Pull_Set_High(const Rowcol_Output_Push_Pull * const me)
{
    BSP_GPIO_Set_Output_Push_Pull_High( ((const Rowcol *)me)->mcu_pin );
}


static void Rowcol_Output_Push_Pull_Set_Low(const Rowcol_Output_Push_Pull * const me)
{
    BSP_GPIO_Set_Output_Push_Pull_Low( ((const Rowcol *)me)->mcu_pin );
}



/*--------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------- PUBLIC FUNCTIONS ----------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

bool Rowcol_Output_Push_Pull_Ctor(Rowcol_Output_Push_Pull * const me, KB_PINSIZE_T mcu_pin_0)
{
    bool success;

    /**
     * Ensure only one VTABLE is stored in ROM so the overhead is only ONE VTABLE for each 
     * Class declaration and a VPTR in RAM for each Class Instance created.
     */
    static const struct Rowcol_Output_VTABLE rowcol_output_push_pull_vtable = 
    {
        .super.init     = (void (*)(const Rowcol * const me))&Rowcol_Output_Push_Pull_Init,
        .set_high       = (void (*)(const Rowcol_Output * const me))&Rowcol_Output_Push_Pull_Set_High,
        .set_low        = (void (*)(const Rowcol_Output * const me))&Rowcol_Output_Push_Pull_Set_Low
    };

    if (me != (Rowcol_Output_Push_Pull *)0)
    {
        success = Rowcol_Output_Ctor(&me->super, mcu_pin_0);

        /**
         * @warning This MUST be done only AFTER the Super Class Constructor is called: 
         * Override Rowcol_Init() with Rowcol_Output_Push_Pull_Init(). Note how Rowcol_Init_VCALL()
         * now calls Rowcol_Output_Push_Pull_Init(), Rowcol_Output_Set_High_VCALL() calls 
         * Rowcol_Output_Push_Pull_Set_High(), and Rowcol_Output_Set_Low_VCALL() calls
         * Rowcol_Output_Push_Pull_Set_Low().
         */
        ((Rowcol *)me)->VPTR = (const struct Rowcol_VTABLE *)&rowcol_output_push_pull_vtable;
    }

    else
    {
        success = false;
    }

    return success;
}
