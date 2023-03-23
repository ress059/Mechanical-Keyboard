/**
 * @file USBFsm.c
 * @author Ian Ress
 * @brief Finite State Machine for the USB Handler. Inherits the Fsm Base Class.
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "USBFsm.h"

static State USBFsm_Initial(USBFsm * const me, const Event * const e);
static State USBFsm_Setup(USBFsm * const me, const Event * const e);
static State USBFsm_PreOperational(USBFsm * const me, const Event * const e);
static State USBFsm_Operational(USBFsm * const me, const Event * const e);
static void Process_Control_Transfer(USBFsm * const me, const Control_Transfer_Event * const e);


/**
 * @brief Runs Fsm_Ctor(). This will run USBFsm_Initial() which is the 
 * Initial Transition of the USB State Machine. All USBFsm members
 * are then initialized.
 * 
 * @param me Pointer to Fsm object.
 * 
 */
void USBFsm_Ctor(USBFsm * const me)
{
    Fsm_Ctor((Fsm *)me, (StateHandler)USBFsm_Initial);
    me->USB_Device_State = RESET;
    /* TODO: HAVE TO SET POINTERS TO DESCRIPTORS DEFINED AT RUN-TIME. Can also have descriptors
    defined at compile-time but that is less robust. */
    // me->USB_Device_Descriptor_Ptr
    // me->USB_Configuration_Descriptor_Ptr
    // me->USB_Endpoint_Descriptor_Ptr
}


/**
 * @brief Executes Initial Transition function assign in Fsm_Ctor(). Then
 * executes the entry event of the next state transitioned into.
 * 
 * @param me Pointer to Fsm object.
 * 
 */
void USBFsm_Init(USBFsm * const me)
{
    Fsm_Init((Fsm *)me, (Event *)0);
}


/**
 * @brief Initial transition when the USBFsm first starts up.
 * 
 * @param me Pointer to Fsm object.
 * @param e Event Signal dispatched to the Fsm.
 * @return Fsm status. In this case we will return TRAN_STATUS which tells the
 * dispatch function we just went through a state transition.
 * 
 */
static State USBFsm_Initial(USBFsm * const me, const Event * const e)
{
    return TRAN(USBFsm_Setup);
}


/**
 * @brief This state is entered either on startup or when the USB host issues a reset 
 * (a @p RESET_REQUEST_RECEIVED event is dispatched to the Fsm). The device's status
 * is set to reset and we transition to the pre-operational state. 
 * 
 * @param me Pointer to Fsm object.
 * @param e Event Signal dispatched to the Fsm.
 * @return Fsm status.
 * 
 */
static State USBFsm_Setup(USBFsm * const me, const Event * const e)
{
    State status;

    switch (e->sig)
    {
        case ENTRY_EVENT:
            /* Reset and Initialize USB controller/endpoint hardware. */
            me->USB_Device_State = RESET;
            status = TRAN(USBFsm_PreOperational);
            break;

        default:
            status = IGNORED_STATUS;
            break;
    }
    return status;
}



/**
 * @brief 
 * 
 * @param me 
 * @param e 
 * @return State 
 */
static State USBFsm_PreOperational(USBFsm * const me, const Event * const e)
{
    State status;

    switch (e->sig)
    {
        case CONTROL_TRANSFER_RECEIVED:
            Process_Control_Transfer(me, ((Control_Transfer_Event *)e));

            if (me->USB_Device_State == OPERATIONAL)
            {
                status = TRAN(USBFsm_Operational);
            }
            else
            {
                status = HANDLED_STATUS;
            }
            break;

        case RESET_REQUEST_RECEIVED:
            status = TRAN(USBFsm_Setup);
            break;

        default:
            status = IGNORED_STATUS;
            break;
    }
    return status;
}

/**
 * @brief 
 * 
 * @param me 
 * @param e 
 * @return State 
 */
static State USBFsm_Operational(USBFsm * const me, const Event * const e);



void Process_Control_Transfer(USBFsm * const me, const Control_Transfer_Event * const e)
{
    switch (e->Control_Transfer_Request)
    {
        case GET_STATUS:
            /* TODO: Handle GET_STATUS request. */
            break;

        case CLEAR_FEATURE:
            /* TODO: Handle CLEAR_FEATURE request*/
            break;

        case SET_FEATURE:
            /* TODO: Handle SET_FEATURE request*/
            break;

        case SET_ADDRESS:
            /* TODO: Handle SET_ADDRESS request*/
            break;

        case GET_DESCRIPTOR:
            switch(e->Descriptor_Type)
            {
                case DEVICE_DESCRIPTOR:
                    /* TODO: Send contents dereferenced in me->USB_Device_Descriptor_Ptr */
                    break;

                case CONFIGURATION_DESCRIPTOR:
                    /* TODO: Send contents dereferenced by me->USB_Configuration_Descriptor_Ptr */
                    break;

                case STRING_DESCRIPTOR:
                    /* TODO: May be trickier. */
                    break;

                case INTERFACE_DESCRIPTOR:
                    /* TODO: Send contents dereferenced by me->USB_Interface_Descriptor_Ptr */
                    break;
                
                case ENDPOINT_DESCRIPTOR:
                    /* TODO: Send contents dereferenced by me->USB_Endpoint_Descriptor_Ptr */
                    break;

                /* TODO: HID Descriptor */

                default:
                    break;

                
            }
            break;

        case SET_DESCRIPTOR:
            /* TODO: */

        case GET_CONFIGURATION:
            /* TODO: Handle GET_CONFIGURATION request. Should be just one byte. */

        case SET_CONFIGURATION:
            /* TODO: Handle SET_CONFIGURATION request. Should be just one byte. */
    }


    enum
    {
        DEVICE_DESCRIPTOR = 0x01,
        CONFIGURATION_DESCRIPTOR = 0x02,
        STRING_DESCRIPTOR = 0x03,
        INTERFACE_DESCRIPTOR = 0x04,
        ENDPOINT_DESCRIPTOR = 0x05
        /* TODO: Add HID Descriptor */
    } Descriptor_Type;

}


