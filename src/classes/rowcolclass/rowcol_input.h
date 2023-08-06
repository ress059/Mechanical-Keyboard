/**
 * @file rowcol_input.h
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


#ifndef ROWCOL_INPUT_CLASS_H_
#define ROWCOL_INPUT_CLASS_H_


/* Base Key and Rowcol Classes */
#include "key.h"
#include "rowcol.h"



/*--------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------- ROWCOL INPUT CLASS ---------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief The Rowcol Input Class. Inherits the Base Rowcol Class. Each Class Instance represents an individual
 * Row/Column that is specifically used as an Input to detect Keypresses. The Keyboard's layout for each Row/Column
 * is also stored in this Class. Note that the layout is only stored for the Input Class and not for the Output
 * Class as this is redundant.
 */
typedef struct
{
    /* Inherit the Base Rowcol Class */
    Rowcol super; 

    /* Additional SubClass Members */
    #warning "This may be non-const in the future"
    const Key ** keys;      /* Keys connected to this Row/Column. Pointer to array of const Keys */
    uint8_t length;         /* Number of Keys connected to this Row/Column. */
} Rowcol_Input;


/**
 * @brief Rowcol Input Class Virtual Function Table for polymorphism. Declares its own Virtual Function, is_key_pressed(). 
 * This function and init() are meant to be overridden by Subclasses that inherit this Class. Full definitions for both
 * cannot be created until it is known whether an Input Internal Pullup, Input Internal Pulldown, Input External Pullup,
 * or Input External Pulldown configuration is used.
 */
struct Rowcol_Input_VTABLE
{
    /* Inherit the Base Rowcol Class VTABLE */
    struct Rowcol_VTABLE super;

    /* Additional SubClass Virtual Functions */
    bool (*is_key_pressed)(const Rowcol_Input * const me);
};



/*--------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------- LATE BINDING ---------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Virtual Call that returns if a keypress was detected. Either a HIGH or LOW reading can register a key 
 * press depending on the Input Configuration - Input Internal Pullup, Input Internal Pulldown, Input External Pullup,
 * or Input External Pulldown.
 * 
 * @warning me is dereferenced and NOT NULL-checked. It is the caller's responsiblity to ensure that me is not NULL.
 * 
 * @param me Pointer to an instance of the Rowcol Input Class. Note that SubClasses that inherit this Class will 
 * explicitly upcast to a (Rowcol_Input *) to inherit this function and perform Late Binding. This is guaranteed to 
 * be a legal and safe operation because the C Standard mandates that the first member of a struct and the struct 
 * itself share the same memory address. Note however that DOWNCASTING is NOT a safe operation and is undefined 
 * behavior. I.e. Casting an Object of type Rowcol to Rowcol_Input to call this function.
 * 
 * @return True if a key press was registered. False if no keypress was registered.
 */
static inline bool Rowcol_Input_Is_Key_Pressed_VCALL(const Rowcol_Input * const me);
static inline bool Rowcol_Input_Is_Key_Pressed_VCALL(const Rowcol_Input * const me)
{
    /**
     * Only the base Rowcol Class stores a VPTR which is of type (Rowcol_VTABLE *). Since this
     * SubClass inherits the Rowcol VTABLE we can explicitly downcast safely to access our 
     * Class's Virtual Function. Note how this is casted to a const struct since we only 
     * initialize one VTABLE per class instance in ROM within the Constructors.
     */
    const struct Rowcol_Input_VTABLE * rowcol_input_vtable = (const struct Rowcol_Input_VTABLE *)(me->super.VPTR);
    return (*rowcol_input_vtable->is_key_pressed)(me);
}



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------ PUBLIC FUNCTIONS --------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Rowcol Input Class Constructor. Inherits Rowcol Base Class.
 * 
 * @param me Pointer to an instance of the Rowcol Input Class. Note that SubClasses that inherit this Class 
 * will explicitly upcast to a (Rowcol_Input *) to inherit this function in their own Constructors. This is 
 * guaranteed to be a legal and safe operation because the C Standard mandates that the first member of a 
 * struct and the struct itself share the same memory address. Note however that DOWNCASTING is NOT a safe 
 * operation and is undefined behavior. WARNING: The caller should also ensure this is not NULL.
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
bool Rowcol_Input_Ctor(Rowcol_Input * const me, KB_PINSIZE_T mcu_pin_0, const Key ** const keys0, uint8_t length0);


#endif /* ROWCOL_INPUT_CLASS_H_ */
