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

#include <avr/interrupt.h>
#include "USBEventHandler.h"

void USB_Default_Handler(void)
{
    /* Empty function call. */
}

void USB_Default_Error_Handler(void)
{
    cli();
    while(1) {};
}


