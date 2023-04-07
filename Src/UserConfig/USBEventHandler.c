/**
 * @file USBEventHandler.c
 * @author Ian Ress
 * @brief The USB stack calls event handlers when certain occurances take place (e.g.
 * USB clock setup failure, TODO: add more examples here.) The user is able to override
 * event handlers with their own definition in this file. If no definition is provided, 
 * the default execution is an empty function.
 * @date 2023-02-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// #include <avr/interrupt.h>
#include "Attributes.h"
#include "USBEventHandler.h"

typedef struct
{
    USB_EVENT e;
    void (*Event_Handler)(void);
} USB_EVENT_Lookup_Table_t;


/************************************************************************************************************
 ***************************************** DEFAULT HANDLER FUNCTIONS ****************************************
 * 
 * If a USB event occurs and it's handler is not defined by the user, the default handlers shown here 
 * will execute.
 * 
 ************************************************************************************************************/

/**
 * @brief The default handler for all USB events. Currently an empty function, but can
 * be defined differently by the user.
 * 
 */
static void USB_Default_Handler(void)
{
    /* Empty function call. */
}


/**
 * @brief The default handler for all USB errors. Currently disables all interrupts
 * and enters an infinite while loop, but can be defined differently by the user.
 * 
 */
void USB_Default_Error_Handler(void)
{
    cli();
    while(1) {};
}


/************************************************************************************************************
 ************************************** USER-DEFINABLE HANDLER FUNCTIONS ************************************
 * 
 * The user can define a function that executes when a certain USB event occurs. The definition can be placed
 * right below the appropriate function declaration. See the descriptions for when each event occurs.
 * 
 ************************************************************************************************************/

/**
 * @brief When initializing the USB controller, a clock source must be selected
 * and enabled. This event occurs if the clock is not successfully enabled after
 * polling it for a user-defined amount of iterations.     
 * 
 * @note The number of times to poll the clock before calling this failure event
 * is defined by @p MAX_CLOCK_ENABLE_POLLS in USB.c
 * 
 * @note If the user does not provide a definition, the default error handler, 
 * @p USB_Default_Error_Handler() will execute. The default error handler 
 * disables all interrupts and enters an infinite while loop.
 * 
 */
static void USB_EVENT_ERROR_Clock_Enable_Failure(void) GCC_ATTRIBUTE_WEAK_ALIAS(USB_Default_Error_Handler);


/**
 * @brief After the PLL is enabled you must wait for the PLL to lock before
 * proceeding. This event occurs if the PLL does not lock after polling it
 * for a user-defined amount of iterations.
 * 
 * @note The number of times to poll the PLL before calling this failure event
 * is defined by @p MAX_PLL_LOCK_POLLS in USB.c
 * 
 * @note If the user does not provide a definition, the default error handler, 
 * @p USB_Default_Error_Handler() will execute. The default error handler 
 * disables all interrupts and enters an infinite while loop.
 * 
 */
static void USB_EVENT_ERROR_PLL_Lock_Failure(void) GCC_ATTRIBUTE_WEAK_ALIAS(USB_Default_Error_Handler);


/**
 * @brief Executes if the startup configuration of the Control Endpoint failed.
 * Failure modes depends on the target MCU. This will be defined in
 * @p USBReg_Is_Endpoint_Configured() in USBRegisters.h
 * 
 */
static void USB_EVENT_ERROR_Endpoint_Setup_Failure(void) GCC_ATTRIBUTE_WEAK_ALIAS(USB_Default_Error_Handler);


/**
 * @brief Executes if the host does not send a reset signal after the device
 * boots up (either due to an internal reset or device is powered on). This
 * reset signal must be received within a user-defined amount of polling iterations
 * 
 * @note The number of polling iterations is defined by @p MAX_HOST_RESET_POLLS
 * in @p USB.c
 * 
 */
static void USB_EVENT_ERROR_Host_Reset_Not_Received(void) GCC_ATTRIBUTE_WEAK_ALIAS(USB_Default_Error_Handler);


/**
 * @brief Executes if @p USB_Device_State ends up being changed to a value not defined
 * in the @p USB_Device_State_t enum. This could suggest a race condition since
 * @p USB_Device_State is accessed in multiple threads. 
 * 
 */
static void USB_EVENT_ERROR_USB_State_Machine_Corrupted(void) GCC_ATTRIBUTE_WEAK_ALIAS(USB_Default_Error_Handler);


/**
 * @brief TODO: 
 * 
 */
static void USB_EVENT_ERROR_Enumeration_Failure(void) GCC_ATTRIBUTE_WEAK_ALIAS(USB_Default_Error_Handler);



/************************************************************************************************************
 ************************************** DEFINITION OF EVENT LOOKUP TABLE ************************************
 * 
 * Contains collection of all USB Event Handler functions that can be indexed via enum USB_EVENT. This way
 * USB Event Handler functions can be executed through this table, and the definitions are hidden from the
 * application. 
 * 
 ************************************************************************************************************/

static const USB_EVENT_Lookup_Table_t USB_EVENT_Lookup_Table[NUMBER_OF_EVENTS] =
/*------------------------------------------------------------------------------------------------------------
            INDEX                                               POINTER TO HANDLER FUNCTION
------------------------------------------------------------------------------------------------------------*/                
{
    {ERROR_CLOCK_ENABLE_FAILURE,                        USB_EVENT_ERROR_Clock_Enable_Failure},
    {ERROR_PLL_LOCK_FAILURE,                            USB_EVENT_ERROR_PLL_Lock_Failure},
    {ERROR_ENDPOINT_SETUP_FAILURE,                      USB_EVENT_ERROR_Endpoint_Setup_Failure},
    {ERROR_HOST_RESET_NOT_RECEIVED,                     USB_EVENT_ERROR_Host_Reset_Not_Received},
    {ERROR_USB_STATE_MACHINE_CORRUPTED,                 USB_EVENT_ERROR_USB_State_Machine_Corrupted},
    {ERROR_ENUMERATION_FAILURE,                         USB_EVENT_ERROR_Enumeration_Failure}
};


/**
 * @brief The actual USB Event Handler function available to the application.
 * Executes the function stored in the index passed to this function.
 * 
 * @param e USB_EVENT enum. This is the index in Event Lookup Table that stores
 * the appropriate Event Handler to execute.
 *  
 */
void USB_EVENT_HANDLER(const USB_EVENT e);
{
    USB_EVENT_Lookup_Table[e].
}
