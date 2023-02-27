/**
 * @file USBEventHandler.h
 * @author Ian Ress
 * \brief The USB stack calls event handlers when certain occurances take place (e.g.
 * USB clock setup failure, TODO: add more examples here.) The user is able to override
 * event handlers with their own definition. If no definition is provided, the default
 * execution is an empty function.
 * @date 2023-02-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef USBEVENTHANDLER_H
#define USBEVENTHANDLER_H

#include "Attributes.h"

/**
 * \brief The default handler for all USB events. This is an empty function.
 * 
 */
void USB_Default_Handler(void);


/**
 * \brief The default handler for all USB errors. This disables all interrupts
 * and enters an infinite while loop.
 * 
 */
void USB_Default_Error_Handler(void);


/**
 * \brief When initializing the USB controller, a clock source must be selected
 * and enabled. This event occurs if the clock is not successfully enabled after
 * polling it for a user-defined amount of iterations.     
 * 
 * \note The number of times to poll the clock before calling this failure event
 * is defined by \p MAX_CLOCK_ENABLE_POLLS in USB.c
 * 
 * \note If the user does not provide a definition, the default error handler, 
 * \p USB_Default_Error_Handler() will execute. The default error handler 
 * disables all interrupts and enters an infinite while loop.
 * 
 */
void USB_EVENT_ERROR_Clock_Enable_Failure(void) GCCATTRIBUTE_WEAK_ALIAS(USB_Default_Error_Handler);


/**
 * \brief After the PLL is enabled you must wait for the PLL to lock before
 * proceeding. This event occurs if the PLL does not lock after polling it
 * for a user-defined amount of iterations.
 * 
 * \note The number of times to poll the PLL before calling this failure event
 * is defined by \p MAX_PLL_LOCK_POLLS in USB.c
 * 
 * \note If the user does not provide a definition, the default error handler, 
 * \p USB_Default_Error_Handler() will execute. The default error handler 
 * disables all interrupts and enters an infinite while loop.
 * 
 */
void USB_EVENT_ERROR_PLL_Lock_Failure(void) GCCATTRIBUTE_WEAK_ALIAS(USB_Default_Error_Handler);


/**
 * \brief Executes if the startup configuration of the Control Endpoint failed.
 * Failure modes depends on the target MCU. This will be defined in
 * \p USBReg_Is_Endpoint_Configured() in USBRegisters.h
 * 
 */
void USB_EVENT_ERROR_Endpoint_Setup_Failure(void) GCCATTRIBUTE_WEAK_ALIAS(USB_Default_Error_Handler);


/**
 * \brief Executes if the host does not send a reset signal after the device
 * boots up (either due to an internal reset or device is powered on). This
 * reset signal must be received within a user-defined amount of polling iterations
 * 
 * \note The number of polling iterations is defined by \p MAX_HOST_RESET_POLLS
 * in \p USB.c
 * 
 */
void USB_EVENT_ERROR_Host_Reset_Not_Received(void) GCCATTRIBUTE_WEAK_ALIAS(USB_Default_Error_Handler);


/**
 * \brief Executes if \p USB_Device_State ends up being changed to a value not defined
 * in the \p USB_Device_State_t enum. This could suggest a race condition since
 * \p USB_Device_State is accessed in multiple threads. 
 * 
 */
void USB_EVENT_ERROR_USB_State_Machine_Corrupted(void) GCCATTRIBUTE_WEAK_ALIAS(USB_Default_Error_Handler);


/**
 * \brief TODO: 
 * 
 */
void USB_EVENT_ERROR_Enumeration_Failure(void) GCCATTRIBUTE_WEAK_ALIAS(USB_Default_Error_Handler);


#endif /* USBEVENTHANDLER_H */