/**
 * @file USBFsm.h
 * @author Ian Ress
 * @brief Finite State Machine for the USB Handler. Inherits the Fsm Base Class.
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef USBFSM_H
#define USBFSM_H

#include "Fsm.h"
#include "USBDescriptors.h"

typedef struct
{
    Fsm super; /* Inherit the Base Fsm Class */
    

    /* Additional Members */
    // enum
    // {
    //     RESET,
    //     OPERATIONAL,
    //     ERROR
    // } USB_Device_State;

    const USB_Device_Descriptor_t * const USB_Device_Descriptor_Ptr;
    const USB_Configuration_Descriptor_t * const USB_Configuration_Descriptor_Ptr;
    const USB_Interface_Descriptor_t * const USB_Interface_Descriptor_Ptr;
    const USB_Endpoint_Descriptor_t * const USB_Endpoint_Descriptor_Ptr;
    /* TODO: Add HID Descriptor */
} USBFsm;


/* Define Event Signals specifically for USBFsm */
enum EventSignals
{
    RESET_REQUEST_RECEIVED = USER_SIG,  /* USB Host resetting the bus. */
    CONTROL_TRANSFER_RECEIVED,          /* USB Host sending Control Transfer */
    KEYPRESS_EVENT                      /* User presses key */
};


typedef struct
{
    Event super; /* Inherit Base Event Class */

    /* Additional Members */
    uint8_t keycodes[8];
} Keypress_Event;


typedef struct
{
    Event super; /* Inherit Base Event Class */

    /* Additional Members */
    enum
    {
        GET_STATUS = 0x00,
        CLEAR_FEATURE = 0x01,
        SET_FEATURE = 0x03,
        SET_ADDRESS = 0x05,
        GET_DESCRIPTOR = 0x06,
        SET_DESCRIPTOR = 0x07,
        GET_CONFIGURATION = 0x08,
        SET_CONFIGURATION = 0x09
    } Control_Transfer_Request;

    enum
    {
        DEVICE_DESCRIPTOR = 0x01,
        CONFIGURATION_DESCRIPTOR = 0x02,
        STRING_DESCRIPTOR = 0x03,
        INTERFACE_DESCRIPTOR = 0x04,
        ENDPOINT_DESCRIPTOR = 0x05
        /* TODO: Add HID Descriptor */
    } Descriptor_Type;
} Control_Transfer_Event;


void USBFsm_Ctor(USBFsm * const me);
void USBFsm_Init(USBFsm * const me);
/* Inherit TRAN(target) macro */
/* Inherit Fsm_Dispatch() function */

#endif /* USBFSM_H */