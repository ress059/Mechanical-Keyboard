/**
 * @file rowcol.h
 * @author Ian Ress
 * @brief The Row/Column Base Class. Each instance of this Class represent an individual Row or Column on the
 * Keyboard.
 * @version 0.1
 * @date 2023-07-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef ROWCOL_BASE_CLASS_H_
#define ROWCOL_BASE_CLASS_H_


/* GPIO Board Support Package for Target MCU */
#include <bsp_gpio.h>



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------- ROW COLUMN BASE CLASS --------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief The Base Rowcol Class. Each Class Instance represents an individual Row or Column on the Keyboard.
 */
typedef struct
{
    /* Base Rowcol Class Members that all other SubClasses inherit */
    const struct Rowcol_VTABLE * VPTR;      /* Pointer to Virtual Table. Note how all Virtual Tables will be in ROM */
    KB_PINSIZE_T mcu_pin;                   /* Microcontroller Port and Pin connected to the Row/Column. */

    /* Additional SubClass Members */
} Rowcol;


/**
 * @brief Base Rowcol Class Virtual Function Table for polymorphism. SubClasses that inherit this Base Class
 * will override init() with their own definition. This cannot be done until we know whether the Row/Column
 * is an Input or an Output.
 */
struct Rowcol_VTABLE
{
    void (*init)(const Rowcol * const me);
};



/*--------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------- LATE BINDING ---------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Virtual Call that initializes the Row/Column as an Input or Output. Multiple GPIO configurations are 
 * possible - Internal Input Pullup, Internal Input Pulldown, External Input Pullup, External Input Pulldown, 
 * Output Pushpull, or Output Open Drain.
 * 
 * @warning me is dereferenced and NOT NULL-checked. It is the caller's responsiblity to ensure that me is not NULL.
 * 
 * @param me Pointer to an instance of the Base Rowcol Class. Note that SubClasses that inherit this Base Class 
 * will explicitly upcast to a (Rowcol *) to inherit this function and perform Late Binding. This is guaranteed to 
 * be a legal and safe operation because the C Standard mandates that the first member of a struct and the struct 
 * itself share the same memory address. 
 */
static inline void Rowcol_Init_VCALL(const Rowcol * const me);
static inline void Rowcol_Init_VCALL(const Rowcol * const me)
{
    (*me->VPTR->init)(me);
}



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------ PUBLIC FUNCTIONS --------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Rowcol Base Class Constructor. 
 * 
 * @param me Pointer to an instance of the Rowcol Base Class. Note that SubClasses that inherit this Base Class 
 * will explicitly upcast to a (Rowcol *) to inherit this function in their own Constructors. This is guaranteed to 
 * be a legal and safe operation because the C Standard mandates that the first member of a struct and the struct 
 * itself share the same memory address. WARNING: The caller should ensure this is not NULL.
 * @param mcu_pin_0 The microcontroller Port and Pin connected to this Row/Column. E.g. KB_PIN_PB1, KB_PIN_PC5, 
 * etc. Each microcontroller has a GPIO Board Support Package that defines these keys - therefore a compilation
 * error will occur if a pin the target MCU does not support is used.
 * 
 * @return True if Constructor was successful. False if failed.
 */
bool Rowcol_Ctor(Rowcol * const me, KB_PINSIZE_T mcu_pin_0);

#warning "TODO: Come up with a way to mandate that \
1) Rows == PULLUP, Columns must output LOW to detect press (LOW, HI, HI,...) \
2) Rows == PULLDOWN, Columns must output HIGH to detect press (HI, LOW, LOW,...) \
Ideally compile-time error"

#endif /* ROWCOL_BASE_CLASS_H_ */
