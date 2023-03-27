/**
 * @file USBHsm.h
 * @author Ian Ress
 * @brief Hierarchical State Machine for the USB Handler. Inherits the Hsm Base Class.
 * Only one USBHsm can be created.
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef USBHSM_H
#define USBHSM_H

#include "Hsm.h"
#include "USBDescriptors.h"

/* USB Hsm Event Class */
typedef struct
{
    Event event; /* Inherit Event Base Class */

    /* Private Members */
    uint8_t HIDReport[8];
} USBHsm_Event;


/* Event Signals specific to USBHsm */
enum USBHsm_Event_Sigs
{
    HOST_RESET_REQ = USER_SIG,          /*  USB Host resetting the bus. */
    SOFTWARE_RESET_REQ,                 /*  Event dispatched by software to reset the USB State Machine. 
                                            Example use-case could be a software error handler calling to 
                                            reset the USB device. */
    POWER_CYCLE_REQ,                    /*  Event dispatched by software that permanently stops the USB
                                            State Machine, requiring a power cycle to reset. */
    CONTROL_TRANSFER_REQ,               /*  USB Host sending Control Transfer */
    SET_CONFIGURATION_REQ,              /*  USB Host sending a Set Configuration request. This is also done
                                            via a Control Transfer. However when we receive this request,
                                            the Host has recognized the device and we can use it as an indicator
                                            to transition into the Operational State and start sending 
                                            HID Reports to the Host. */
    KEYPRESS_EVENT                      /*  User presses key */
};


void USBHsm_Begin(void);
void USBHsm_Dispatch(const USBHsm_Event * const e);

#endif /* USBFSM_H */