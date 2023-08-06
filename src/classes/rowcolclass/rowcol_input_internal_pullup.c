/**
 * @file rowcol_input_internal_pullup.c
 * @author Ian Ress
 * @brief Rowcol Input Internal Pullup Class. Inherits Base Rowcol Class and Input Rowcol Class. Each Class
 * Instance represents a Row/Column that uses an Input with Internal Pullup Resistors to detect Keypresses.
 * @version 0.1
 * @date 2023-07-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "rowcol_input_internal_pullup.h"



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------- VIRTUAL FUNCTION DECLARATIONS (PRIVATE) --------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Initializes the Row/Column GPIO Pin as an Internal Pullup. This is a Wrapper Function that 
 * calls the GPIO Board Support Package. The Build System selects the correct Board Support Package 
 * at compile-time by updating the Include Paths to point to the appropriate MCU Drivers folder. A 
 * compilation error will occur if the target MCU does not support internal pullups as the BSP GPIO 
 * function will not be defined.
 */
static void Rowcol_Input_Internal_Pullup_Init(const Rowcol_Input_Internal_Pullup * const me);


/**
 * @brief Wrapper Function that call GPIO Board Support Package to take a pin reading. Since this 
 * Row/Column is connected to an Internal Pullup Pin, a keypress is registered when the pin has a 
 * LOW reading. Note that the Column pins must be set to LOW to detect keypresses (LOW, HIGH, HIGH, 
 * HIGH,...)
 * 
 * @return True if a keypress was detected. False if no keypress was detected.
 */
static bool Rowcol_Input_Internal_Pullup_Is_Key_Presed(const Rowcol_Input_Internal_Pullup * const me);



/*--------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------- VIRTUAL FUNCTION DEFINITIONS (PRIVATE) --------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

static void Rowcol_Input_Internal_Pullup_Init(const Rowcol_Input_Internal_Pullup * const me)
{
    BSP_GPIO_Set_Pin_Type_Input_Pullup( ((const Rowcol *)me)->mcu_pin );
}


static bool Rowcol_Input_Internal_Pullup_Is_Key_Presed(const Rowcol_Input_Internal_Pullup * const me)
{
    return !( BSP_GPIO_Read( ((const Rowcol *)me)->mcu_pin ) );
}



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------ PUBLIC FUNCTIONS --------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

bool Rowcol_Input_Internal_Pullup_Ctor(Rowcol_Input_Internal_Pullup * const me, KB_PINSIZE_T mcu_pin_0, const Key ** const keys0, uint8_t length0)
{
    bool success;

    /**
     * Ensure only one VTABLE is stored in ROM so the overhead is only ONE VTABLE for each 
     * Class declaration and a VPTR in RAM for each Class Instance created.
     */
    static const struct Rowcol_Input_VTABLE rowcol_input_internal_pullup_vtable =
    {
        .super.init         = (void (*)(const Rowcol * const me))&Rowcol_Input_Internal_Pullup_Init,
        .is_key_pressed     = (bool (*)(const Rowcol_Input * const me))&Rowcol_Input_Internal_Pullup_Is_Key_Presed
    };

    if (me != (Rowcol_Input_Internal_Pullup *)0) /* keys0 and length0 are already NULL-checked in Rowcol_Input Constructor */
    {
        success = Rowcol_Input_Ctor((Rowcol_Input *)me, mcu_pin_0, keys0, length0);

        /**
         * @warning This MUST be done only AFTER the Super Class Constructor is called: 
         * Override Rowcol_Init() with Rowcol_Input_Internal_Pullup_Init() and Rowcol_Input_Is_Key_Pressed()
         * with Rowcol_Input_Internal_Pullup_Is_Key_Presed(). Notice how Rowcol_Init_VCALL() now calls 
         * Rowcol_Input_Internal_Pullup_Init() and Rowcol_Input_Is_Key_Pressed_VCALL() calls 
         * Rowcol_Input_Internal_Pullup_Is_Key_Presed().
         */
        ((Rowcol *)me)->VPTR = (const struct Rowcol_VTABLE *)&rowcol_input_internal_pullup_vtable;
    }

    else
    {
        success = false;
    }

    return success;
}
