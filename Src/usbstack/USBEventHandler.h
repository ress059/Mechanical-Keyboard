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

typedef enum
{
    /* ERRORS */
    ERROR_CLOCK_ENABLE_FAILURE = 0,
    ERROR_PLL_LOCK_FAILURE,
    ERROR_ENDPOINT_SETUP_FAILURE,
    ERROR_HOST_RESET_NOT_RECEIVED,
    ERROR_USB_STATE_MACHINE_CORRUPTED,
    ERROR_ENUMERATION_FAILURE,

    /* EVENTS */
    /* Add events here */

    /************************/
    NUMBER_OF_EVENTS
} USB_EVENT;

void USB_Default_Error_Handler(void);
void USB_EVENT_HANDLER(const USB_EVENT e);


#endif /* USBEVENTHANDLER_H */