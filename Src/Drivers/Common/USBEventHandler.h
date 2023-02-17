/**
 * @file USBEventHandler.h
 * @author Ian Ress
 * @brief The USB stack calls event handlers when certain occurances take place (e.g.
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
 * @brief The default handler for all events. This is an empty function.
 * 
 */
void USB_Default_Handler(void);


/**
 * @brief When initializing the USB controller, a clock source must be selected
 * and enabled. This event occurs if the clock is not successfully enabled after
 * polling it for a user-defined amount of iterations.
 * 
 * \note The number of times to poll the clock before calling this failure event
 * is defined by \p MAX_CLOCK_ENABLE_POLLS in USB.c
 * 
 */
void USB_EVENT_Clock_Enable_Failure(void) GCCATTRIBUTE_WEAK_ALIAS(USB_Default_Handler);


/**
 * @brief After the PLL is enabled you must wait for the PLL to lock before
 * proceeding. This event occurs if the PLL does not lock after polling it
 * for a user-defined amount of iterations.
 * 
 * \note The number of times to poll the PLL before calling this failure event
 * is defined by \p MAX_PLL_LOCK_POLLS in USB.c
 * 
 */
void USB_EVENT_PLL_Lock_Failure(void) GCCATTRIBUTE_WEAK_ALIAS(USB_Default_Handler);


#endif /* USBEVENTHANDLER_H */