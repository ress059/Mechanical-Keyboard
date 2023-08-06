/**
 * @file rowcol_output.h
 * @author Ian Ress
 * @brief Rowcol Output Class. Inherits the Base Rowcol Class. Each Class Instance represents an individual
 * Row/Column that is specifically used as an Output that sets a Row/Column HIGH and LOW.
 * @version 0.1
 * @date 2023-07-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef ROWCOL_OUTPUT_CLASS_H_
#define ROWCOL_OUTPUT_CLASS_H_


/* Inherit Base Rowcol Class */
#include "rowcol.h"



/*--------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------- ROWCOL OUTPUT CLASS --------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Rowcol Output Class. Inherits the Base Rowcol Class. Each Class Instance represents an individual
 * Row/Column that is specifically used as an Output that sets a Row/Column HIGH and LOW. Note that the Keyboard's 
 * layout is only stored in the Rowcol Input Class to avoid redundancy.
 */
typedef struct
{
    /* Inherit the Base Rowcol Class */
    Rowcol super; 

    /* Additional SubClass Members */
} Rowcol_Output;


/**
 * @brief Rowcol Output Class Virtual Function Table for polymorphism. Declares its own Virtual Functions, set_high() and
 * set_low(). These functions and init() are meant to be overridden by Subclasses that inherit this Class. Full definitions 
 * cannot be created until it is known whether an Output Pushpull or Output Opendrain configuration is used.
 */
struct Rowcol_Output_VTABLE
{
    /* Inherit the Base Rowcol Class VTABLE */
    struct Rowcol_VTABLE super;

    /* Additional SubClass Virtual Functions */
    void (*set_high)(const Rowcol_Output * const me);
    void (*set_low)(const Rowcol_Output * const me);
};



/*--------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------- LATE BINDING ---------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Virtual Call that sets a Row/Column HIGH. This can correspond to a LOW or HIGH write depending on if the pin
 * is Open Drain or Push Pull, as well as the internal GPIO block diagram. 
 * 
 * @warning me is dereferenced and NOT NULL-checked. It is the caller's responsiblity to ensure that me is not NULL.
 * 
 * @param me Pointer to an instance of the Rowcol Output Class. Note that SubClasses that inherit this Class will 
 * explicitly upcast to a (Rowcol_Output *) to inherit this function and perform Late Binding. This is guaranteed to 
 * be a legal and safe operation because the C Standard mandates that the first member of a struct and the struct 
 * itself share the same memory address. Note however that DOWNCASTING is NOT a safe operation and is undefined 
 * behavior. I.e. Casting an Object of type Rowcol to Rowcol_Output to call this function.
 */
static inline void Rowcol_Output_Set_High_VCALL(const Rowcol_Output * const me);
static inline void Rowcol_Output_Set_High_VCALL(const Rowcol_Output * const me)
{
    /**
     * Only the base Rowcol Class stores a VPTR which is of type (Rowcol_VTABLE *). Since this
     * SubClass inherits the Rowcol VTABLE we can explicitly downcast safely to access our 
     * Class's Virtual Function. Note how this is casted to a const struct since we only 
     * initialize one VTABLE per class instance in ROM within the Constructors.
     */
    const struct Rowcol_Output_VTABLE * rowcol_output_vtable = (const struct Rowcol_Output_VTABLE *)(me->super.VPTR);
    (*rowcol_output_vtable->set_high)(me);
}


/**
 * @brief Virtual Call that sets a Row/Column LOW. This can correspond to a LOW or HIGH write depending on if the pin
 * is Open Drain or Push Pull, as well as the internal GPIO block diagram. 
 * 
 * @warning me is dereferenced and NOT NULL-checked. It is the caller's responsiblity to ensure that me is not NULL.
 * 
 * @param me Pointer to an instance of the Rowcol Output Class. Note that SubClasses that inherit this Class will 
 * explicitly upcast to a (Rowcol_Output *) to inherit this function and perform Late Binding. This is guaranteed to 
 * be a legal and safe operation because the C Standard mandates that the first member of a struct and the struct 
 * itself share the same memory address. Note however that DOWNCASTING is NOT a safe operation and is undefined 
 * behavior. I.e. Casting an Object of type Rowcol to Rowcol_Output to call this function.
 */
static inline void Rowcol_Output_Set_Low_VCALL(const Rowcol_Output * const me);
static inline void Rowcol_Output_Set_Low_VCALL(const Rowcol_Output * const me)
{
    /**
     * Only the base Rowcol Class stores a VPTR which is of type (Rowcol_VTABLE *). Since this
     * SubClass inherits the Rowcol VTABLE we can explicitly downcast safely to access our 
     * Class's Virtual Function. Note how this is casted to a const struct since we only 
     * initialize one VTABLE per class instance in ROM within the Constructors.
     */
    const struct Rowcol_Output_VTABLE * rowcol_output_vtable = (const struct Rowcol_Output_VTABLE *)(me->super.VPTR);
    (*rowcol_output_vtable->set_low)(me);
}



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------ PUBLIC FUNCTIONS --------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Rowcol Output Class Constructor. Inherits Rowcol Base Class.
 * 
 * @param me Pointer to an instance of the Rowcol Output Class. Note that SubClasses that inherit this Class 
 * will explicitly upcast to a (Rowcol_Output *) to inherit this function in their own Constructors. This is 
 * guaranteed to be a legal and safe operation because the C Standard mandates that the first member of a 
 * struct and the struct itself share the same memory address. Note however that DOWNCASTING is NOT a safe 
 * operation and is undefined behavior. WARNING: The caller should also ensure this is not NULL.
 * @param mcu_pin_0 The microcontroller Port and Pin connected to this Row/Column. E.g. KB_PIN_PB1, KB_PIN_PC5, 
 * etc. Each microcontroller has a GPIO Board Support Package that defines these keys - therefore a compilation
 * error will occur if a pin the target MCU does not support is used.
 * 
 * @return True if Constructor was successful. False if failed.
 */
bool Rowcol_Output_Ctor(Rowcol_Output * const me, KB_PINSIZE_T mcu_pin_0);


#endif /* ROWCOL_OUTPUT_CLASS_H_ */
