/**
 * @file USBHsm.c
 * @author Ian Ress
 * @brief Hierarchical State Machine for the USB Handler. Inherits the Hsm Base Class.
 * Only one USBHsm can be created.
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <avr/interrupt.h>
#include <string.h> /* memset */
#include "USBHsm.h"


// typedef struct
// {
//     Event super; /* Inherit Base Event Class */

//     /* Additional Members */
//     enum
//     {
//         GET_STATUS = 0x00,
//         CLEAR_FEATURE = 0x01,
//         SET_FEATURE = 0x03,
//         SET_ADDRESS = 0x05,
//         GET_DESCRIPTOR = 0x06,
//         SET_DESCRIPTOR = 0x07,
//         GET_CONFIGURATION = 0x08,
//         SET_CONFIGURATION = 0x09
//     } Control_Transfer_Request;

//     enum
//     {
//         DEVICE_DESCRIPTOR = 0x01,
//         CONFIGURATION_DESCRIPTOR = 0x02,
//         STRING_DESCRIPTOR = 0x03,
//         INTERFACE_DESCRIPTOR = 0x04,
//         ENDPOINT_DESCRIPTOR = 0x05
//         /* TODO: Add HID Descriptor */
//     } Descriptor_Type;
// } Control_Transfer_Event;


/**
 * USB Hsm Class declared here because only one USBHsm object is meant to be created.
 * This requires that the USB Descriptors are all defined at compile-time.
 * 
 */
typedef struct
{
    Hsm hsm; /* Inherit Hsm Base Class */

    /* Private Members */
    const USB_Device_Descriptor_t * const USB_Device_Descriptor_Ptr;
    const USB_Configuration_Descriptor_t * const USB_Configuration_Descriptor_Ptr;
    const USB_Interface_Descriptor_t * const USB_Interface_Descriptor_Ptr;
    const USB_Endpoint_Descriptor_t * const USB_Endpoint_Descriptor_Ptr;
    /* TODO: Add HID Descriptor */
} USBHsm;

static USBHsm USBHsm_Me = 
{
    .hsm = {.state = (State *)0}, /* Used to throw error if more than one USBHsm object is ever defined. */
    .USB_Configuration_Descriptor_Ptr = NULL,
    .USB_Device_Descriptor_Ptr = NULL,
    .USB_Endpoint_Descriptor_Ptr = NULL,
    .USB_Interface_Descriptor_Ptr = NULL
    #error "TODO: Add private USBHsm members."
};


/**
 * Substate Objects and State Handler function prototypes.
 * 
 */
static Status USBHsm_Top_State_Hndlr(USBHsm * const me, const Event * const e);
static const State USBHsm_Top_State = 
{
    (State *)0,
    &USBHsm_Top_State_Hndlr
};


static Status USBHsm_PreOperational_State_Hndlr(USBHsm * const me, const Event * const e);
static const State USBHsm_PreOperational_State =
{
    (State *)&USBHsm_Top_State,
    &USBHsm_PreOperational_State_Hndlr
};


static Status USBHsm_Operational_State_Hndlr(USBHsm * const me, const Event * const e);
static const State USBHsm_Operational_State =
{
    (State *)&USBHsm_PreOperational_State,
    &USBHsm_Operational_State_Hndlr
};


static Status USBHsm_Error_State_Hndlr(USBHsm * const me, const Event * const e);
static const State USBHsm_Error_State =
{
    (State *)&USBHsm_Top_State,
    &USBHsm_Error_State_Hndlr
};
// static void Process_Control_Transfer(USBHsm * const me, const Control_Transfer_Event * const e); /* TODO: */


/**
 * @brief Initial transition into the USB Hsm. This transitions the state 
 * into the Pre-Operational State. Only called once when the State Machine
 * first starts up.
 * 
 */
static Status USBHsm_Initial_State_Hndlr(USBHsm * const me, const Event * const e);
static Status USBHsm_Initial_State_Hndlr(USBHsm * const me, const Event * const e)
{
    (void)me;
    (void)e;
    return TRAN(USBHsm_PreOperational_State);
}


/**
 * @brief Event Handler function when the USB Hsm is in the Top State. This is a container
 * for all of the USB Hsm's substates and does not handle any events or transitions. 
 * Therefore all events dispatched to this state are ignored. 
 * 
 * @note This state does not have an Entry Event, as all of the USB initializations 
 * are contained within the Entry Event of the Pre-Operational State. This state
 * does not have an Exit Event because the USB Hsm is always running. The Error
 * State, which stops the USB Hsm, is contained within the Top State.
 * 
 */
static Status USBHsm_Top_State_Hndlr(USBHsm * const me, const Event * const e)
{
    (void)me;
    (void)e;
    return IGNORED_STATUS;
}


/**
 * @brief Event Handler function when the USB Hsm is in the Pre-Operational State.
 * This is the state first transitioned into when the USB Hsm starts up.
 * This state is for processing Control Transfers, handling the Enumeration Phase, 
 * handling USB resets, and handling a Power Cycle request.
 * 
 * The USB reset will be dispatched to the Hsm if the Host requests a reset 
 * or from our application software's Error Handling functions.
 * If a USB Reset occurs, we simply transition out of and back into this state.
 * The Hsm Dispatcher will figure out the necessary exit and entry events to run.
 * It is guaranteed that the Exit and Entry Events of this handler will always 
 * execute in this scenario. This resets and re-initializes the USB hardware and 
 * endpoint configurations. This also re-enumerates the device.
 * 
 * A Power Cycle request is dispatched to the Hsm if a major error occurs. This
 * will be dispatched via our application software's Error Handling functions.
 * This causes a transition into the Error State, which never exits. Thus requiring
 * a power cycle to reset.
 * 
 * We do not send any HID Reports until the Host sends back a SET_CONFIGURATION
 * request via a Control Transfer. When we receive this request, the Host has 
 * recognized the device and we can use it as an indicator to transition into 
 * the Operational State, where we start sending HID Reports to the Host.
 *  
 */
static Status USBHsm_PreOperational_State_Hndlr(USBHsm * const me, const Event * const e)
{
    Status status;

    switch(e->sig)
    {
        case ENTRY_EVENT:
            // Disable watchdog
            #error "TODO: Make function that Resets and Initializes USB Hardware."
            // Enable global Interrupts
            status = HANDLED_STATUS;
            break;

        case EXIT_EVENT:
            status = HANDLED_STATUS;
            break;

        case CONTROL_TRANSFER_REQ:
            // Figure out Control Transfer request type
            #error "TODO: Make function that handles Control Transfers."
            break;

        case SET_CONFIGURATION_REQ:
            status = TRAN(USBHsm_Operational_State);
            break;

        case HOST_RESET_REQ:
        case SOFTWARE_RESET_REQ:
            status = TRAN(USBHsm_PreOperational_State);
            break;

        case POWER_CYCLE_REQ:
            status = TRAN(USBHsm_Error_State);
            break;

        default:
            status = SUPER(USBHsm_Top_State);
            break;
    }
    return status;
}


/**
 * @brief Event Handler function when the USB Hsm is in the Operational State. This
 * state is primarily for sending HID Reports back to the host when keys are pressed.
 * It is assumed that the matrix scanning function places data into the HIDReport 
 * buffer following the proper format outlined in the keyboard's HID Report Descriptor.
 * 
 * If a Control Transfer request, USB Reset, or Power Cycle request occurs, we exit 
 * the Operational State and handle the event in the Pre-Operational State. 
 * The Hsm Dispatcher will figure out the necessary exit and entry events to run. 
 * It is guaranteed that the Exit and Entry Events of this handler will always execute 
 * in this scenario. This resets the HIDReport buffer.
 * 
 */
static Status USBHsm_Operational_State_Hndlr(USBHsm * const me, const Event * const e)
{
    Status status;

    switch(e->sig)
    {
        case ENTRY_EVENT:
            #error "TODO: Enable watchdog."
            memset( ((USBHsm_Event *)e)->HIDReport, 0, sizeof(((USBHsm_Event *)e)->HIDReport) );
            status = HANDLED_STATUS;
            break;

        case EXIT_EVENT:
            memset( ((USBHsm_Event *)e)->HIDReport, 0, sizeof(((USBHsm_Event *)e)->HIDReport) );
            status = HANDLED_STATUS;
            break;

        case KEYPRESS_EVENT:
            #error "TODO: Process HID Report"
            status = HANDLED_STATUS;
            break;

        default:
            status = SUPER(USBHsm_PreOperational_State);
            break;
    }
    return status;
}


/**
 * @brief Event Handler function when the USB Hsm is in the Error State. This
 * is transitioned into when a Power Cycle request is dispatched to the Hsm.
 * This will be dispatched via our application software's Error Handling functions.
 * 
 * The Hsm Dispatcher will figure out the necessary exit events to run.
 * It is guaranteed that the Entry Event of this handler will always execute in
 * this scenario. This disables the watchdog, global interrupts, and 
 * enters an infinite while loop. 
 * 
 * This logic can be removed if the user wishes to have the rest of the
 * application code still execute, with the USB Hsm permanently disabled.
 * If this is the case, any events dispatched to the Hsm will enter the 
 * default case and always be ignored. No transitions occur in this state, 
 * so the Error State never exits. 
 * 
 */
static Status USBHsm_Error_State_Hndlr(USBHsm * const me, const Event * const e)
{
    State status;

    switch(e->sig)
    {
        case ENTRY_EVENT:
            #error "TODO: Disable Watchdog."
            cli();
            #error "TODO: Run Error Handler function."
            while(1){}  /* Can remove if the rest of the application code  */
            status = HANDLED_STATUS;
            break;

        default:
            status = IGNORED_STATUS;
            break;
    }
    return status;
}


/**
 * @brief Calls the USBHsm Constructor and runs the Initial State Handler 
 * function of the USB Hsm. This function transitions the USB Hsm state 
 * to the Pre-Operational State then runs the Entry Event of the 
 * Pre-Operational State Handler. This resets and initializes the USB hardware.
 * 
 * @note Meant to only be called once at startup since only one USBHsm
 * object can be defined. If this is called again the function will 
 * simply return and no changes will be applied to the USB Hsm.
 * 
 */
void USBHsm_Begin(void)
{
    if (USBHsm_Me.hsm.state != (State *)0)
    {
        return;
    }
    else
    {
        Hsm_Ctor((Hsm *)&USBHsm, &USBHsm_Initial_State_Hndlr);
        Hsm_Begin((Hsm *)&USBHsm, (Event *)0);
    }
}


void Process_Control_Transfer(USBHsm * const me, const Control_Transfer_Event * const e)
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


