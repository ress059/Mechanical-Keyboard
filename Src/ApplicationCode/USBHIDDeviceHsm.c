/**
 * @file USBHIDDeviceHsm.c
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
#include "Compatibility.h"
#include "Endian.h"
#include "USBConfig.h"
#include "USBHIDDeviceHsm.h"


/**
 * @brief This sets the maximum allowable current draw for every USBHID_Device_Hsm 
 * Object created. bMaxPower of the Configuration Descriptor must be less than
 * this value or else the USBHID_Device_Hsm Constructor will return False.
 * 
 */
#define USBHID_DEVICE_HSM_MAX_CURRENT                       SET_MAX_CURRENT(500)


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
 * Default Descriptors used for USB HID Device in Hsm.
 */
static const uint8_t Default_Report_Descriptor[] = 
{
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xA1, 0x01,                    // COLLECTION (Application)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0xE0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xE7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x15, 0x01,                    //   LOGICAL_MINIMUM (1)
    0x25, 0x63,                    //   LOGICAL_MAXIMUM (99)
    0x19, 0x01,                    //   USAGE_MINIMUM (Keyboard ErrorRollOver)
    0x29, 0x63,                    //   USAGE_MAXIMUM (Keypad . and Delete)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xC0                           // END_COLLECTION
};

static const USB_Std_Device_Descriptor_t Default_Device_Descriptor = 
{
    .bLength                    = sizeof(USB_Std_Device_Descriptor_t),
    .bDescriptionType           = DEVICE_DESCRIPTOR_TYPE,
    .bcdUSB                     = LE16_COMPILETIME(USB_VERSION),
    .bDeviceClass               = 0x00,                             /* HID Class is defined in the Interface Descriptor */
    .bDeviceClass               = 0x00,                             /* HID Class is defined in the Interface Descriptor */
    .bDeviceProtocol            = 0x00,                             /* HID Class is defined in the Interface Descriptor */
    .bMaxPacketSize0            = CONTROL_ENDPOINT_SIZE,
    .idVendor                   = LE16_COMPILETIME(0xFF00),         /* Use 0xFF00 to 0xFFFF for development */
    .idProduct                  = LE16_COMPILETIME(0x1234),         /* Can be anything */
    .bcdDevice                  = LE16_COMPILETIME(0x0100),         /* Release Version 1.0 */
    .iManufacturer              = 0,
    .iProduct                   = 0,
    .iSerialNumber              = 0,
    .bNumConfigurations         = 1
};

static const USB_Std_Configuration_Descriptor_t Default_Configuration_Descriptor =
{
    .bLength                    = sizeof(USB_Std_Configuration_Descriptor_t),
    .bDescriptionType           = CONFIGURATION_DESCRIPTOR_TYPE,
    .wTotalLength               = LE16_COMPILETIME(   sizeof(USB_Std_Configuration_Descriptor_t) \  /* This Configuration Descriptor */
                                                    + sizeof(USB_Std_Interface_Descriptor_t) \      /* We are only assigning One Interface Descriptor to this Configuration. */
                                                    + sizeof(USB_Std_Endpoint_Descriptor_t) \       /* Endpoint 1 IN Descriptor */
                                                    + sizeof(USB_HID_Std_HID_Descriptor_t) \        /* HID Descriptor. We are only assigning One Report Descriptor to this HID Descriptor. */
                                                    + sizeof(Default_Report_Descriptor)   ),        /* Report Descriptor */
    .bNumInterfaces             = 1,
    .bConfigurationValue        = 1,
    .iConfiguration             = 0,
    .bmAttributes               = 0b1010000,                        /* Remote Wakeup */
    .bMaxPower                  = 50,                               /* 100mA max */
};

static const USB_Std_Interface_Descriptor_t Default_Interface_Descriptor =
{
    .bLength                    = sizeof(USB_Std_Interface_Descriptor_t),
    .bDescriptorType            = INTERFACE_DESCRIPTOR_TYPE,
    .bInterfaceNumber           = 0,
    .bAlternateSetting          = 0,
    .bNumEndpoints              = 1,                                /* Endpoint 1 IN */
    .bInterfaceClass            = HID_CLASS_CODE,
    .bInterfaceSubClass         = 0x00,                             /* TODO: Set to 0x01 when development work to support UEFI/BIOS operation is started */
    .bInterfaceProtocol         = 0x00,                             /* TODO: Set to HID_KEYBOARD_INTERFACE_CODE when development work to support UEFI/BIOS operation is started */
    .iInterface                 = 0,
};

static const USB_HID_Std_HID_Descriptor_t Default_HID_Descriptor =
{
    .bLength                    = sizeof(USB_HID_Std_HID_Descriptor_t),
    .bDescriptorType            = HID_DESCRIPTOR_TYPE,
    .bcdHID                     = LE16_COMPILETIME(HID_CLASS_VERSION),
    .bCountryCode               = 33,                               /* U.S. Country Code. See USB HID Spec Section 6.1.2 - HID Descriptor */
    .bNumDescriptors            = 1,                                /* Report Descriptor */
    .bDescriptorType2           = HID_REPORT_DESCRIPTOR_TYPE,
    .wDescriptorLength          = sizeof(Default_Report_Descriptor)
};

static const USB_Std_Endpoint_Descriptor_t Default_Endpoint_Descriptor =
{
    .bLength                    = sizeof(USB_Std_Endpoint_Descriptor_t),
    .bDescriptorType            = ENDPOINT_DESCRIPTOR_TYPE,
    .bEndpointAddress           = 0b10000001,                       /* Endpoint 1 IN */
    .bmAttributes               = 0b00000011,                       /* Interrupt Endpoint */
    .wMaxPacketSize             = LE16_COMPILETIME(HID_ENDPOINT_SIZE),
    .bInterval                  = 5                                 /* 5ms Polling */
};


/**
 * State Objects and State Handler function prototypes. Note that we will upcast
 * (Hsm *) to (USBHID_Device_Hsm *) within the State Handler function definition
 * and downcast (USBHID_Device_Hsm *) to (Hsm *) whenever calling Hsm_Dispatch().
 * This follows Strict Aliasing rules and allows us to access members in
 * USBHID_Device_Hsm class.
 */

/* Top-most State. Contains USB_Superstate and Error_State */
static HsmStatus USBHID_Device_Hsm_Top_State_Hndlr(Hsm * const me, const Event * const e);
static const HsmState USBHID_Device_Hsm_Top_State = 
{
    .superstate = (HsmState *)0,                       /* Hsm Dispatcher uses NULL pointer to identify Top State. */
    .hndlr = USBHID_Device_Hsm_Top_State_Hndlr
};


static HsmStatus USBHID_Device_Hsm_Error_State_Hndlr(Hsm * const me, const Event * const e);
static const HsmState USBHID_Device_Hsm_Error_State =
{
    .superstate = (HsmState *)&USBHID_Device_Hsm_Top_State,
    .hndlr = USBHID_Device_Hsm_Error_State_Hndlr
};


/* Contains Default_State, Address_State, and Configured_State in accordance with USB 2.0 spec - Chapter 9 */
static HsmStatus USBHID_Device_Hsm_USB_Superstate_Hndlr(Hsm * const me, const Event * const e);
static const HsmState USBHID_Device_Hsm_USB_Superstate =
{
    .superstate = (HsmState *)&USBHID_Device_Hsm_Top_State,
    .hndlr = USBHID_Device_Hsm_USB_Superstate_Hndlr
};


static HsmStatus USBHID_Device_Hsm_Default_State_Hndlr(Hsm * const me, const Event * const e);
static const HsmState USBHID_Device_Hsm_Default_State =
{
    .superstate = (HsmState *)&USBHID_Device_Hsm_USB_Superstate,
    .hndlr = USBHID_Device_Hsm_Default_State_Hndlr
};


static HsmStatus USBHID_Device_Hsm_Address_State_Hndlr(Hsm * const me, const Event * const e);
static const HsmState USBHID_Device_Hsm_Address_State =
{
    .superstate = (HsmState *)&USBHID_Device_Hsm_USB_Superstate,
    .hndlr = USBHID_Device_Hsm_Address_State_Hndlr
};


static HsmStatus USBHID_Device_Hsm_Configured_State_Hndlr(Hsm * const me, const Event * const e);
static const HsmState USBHID_Device_Hsm_Configured_State =
{
    .superstate = (HsmState *)&USBHID_Device_Hsm_USB_Superstate,
    .hndlr = USBHID_Device_Hsm_Configured_State_Hndlr
};


/**
 * Control Transfers must be processed differently depending on the State you are in.
 * See USB 2.0 Spec Chapter 9.4 - Standard Device Requests
 */

/**
 * @brief Processes Control Transfers while the USBHID_Hsm is in the Default State.
 * In the Default State the HID Device is powered, attached to the bus, and has
 * been reset by the Host. However it has not been assigned a unique address.
 * 
 */
static HsmStatus USBHID_Device_Hsm_Default_State_Process_Control_Transfer(USBHID_Device_Hsm * const me);
static HsmStatus USBHID_Device_Hsm_Default_State_Process_Control_Transfer(USBHID_Device_Hsm * const me)
{
    HsmStatus status;
    #error "TODO: Figure out Control Transfer request. Store in local variable 'Standard_Device_Request'."

    switch (Standard_Device_Request)
    {
        case GET_DESCRIPTOR:
        {
            #error "TODO: Process this"
            status = HSM_HANDLED_STATUS;
            break;
        }

        case SET_ADDRESS:
        {
            #error "TODO: Process this"
            if (address > 0) 
            {
                me->Address = address;
                status = HSM_TRAN(USBHID_Device_Hsm_Address_State);
            }
            else
            {
                status = HSM_IGNORED_STATUS;
            }
            break;
        }

        case SET_FEATURE:
        {
            #error "TODO: Process SET_FEATURE(TEST_MODE) and SET_FEATURE(TEST_SELECTOR). Otherwise ignore"
            if (TEST_MODE || TEST_SELECTOR)
            {
                status = HSM_HANDLED_STATUS;
            }
            else
            {
                status = HSM_IGNORED_STATUS;
            }
            break;
        }
        
        /*  CLEAR_FEATURE, GET_CONFIGURATION, GET_INTERFACE, GET_STATUS, SET_CONFIGURATION, 
            SET_DESCRIPTOR, SET_INTERFACE, and SYNCH_FRAME requests are ignored. */
        default:
        {
            status = HSM_IGNORED_STATUS;
            break;
        }
    }
    return status;
}


/**
 * @brief Processes Control Transfers while the USBHID_Hsm is in the Address State.
 * In the Address State the HID Device has been assigned a unique address by the
 * Host but has not been enumerated.
 * 
 */
static HsmStatus USBHID_Device_Hsm_Address_State_Process_Control_Transfer(USBHID_Device_Hsm * const me);
static HsmStatus USBHID_Device_Hsm_Address_State_Process_Control_Transfer(USBHID_Device_Hsm * const me)
{
    HsmStatus status = HSM_HANDLED_STATUS;
    #error "TODO: Figure out Control Transfer request. Store in local variable 'Standard_Device_Request'."

    switch (Standard_Device_Request)
    {
        case CLEAR_FEATURE:
        {
            if (referring to endpoint 0)
            {
                #error "TODO: Process this."
            }
            else
            {
                #error "TODO: Respond to Host with a Request Error."
            }
            break;
        }

        case GET_CONFIGURATION:
        {
            #error "TODO: Return a value of 0 to the Host."
            break;
        }

        case GET_DESCRIPTOR:
        {
            #error "TODO: Process this."
            break;
        }

        case GET_INTERFACE:
        {
            #error "TODO: Respond to Host with Request Error."
            break;
        }

        case GET_STATUS:
        {
            if (referring to endpoint 0)
            {
                #error "TODO: Process this."
            }
            else
            {
                #error "TODO: Respond to Host with a Request Error."
            }
            break;
        }

        case SET_ADDRESS:
        {
            #error "TODO: Process this"
            if (address == 0) 
            {
                status = HSM_TRAN(USBHID_Device_Hsm_Default_State);
            }
            else
            {
                me->Address = address;
            }
            break;
        }

        case SET_CONFIGURATION:
        {
            #error "TODO: Process this"
            if (configuration == 0)
            {
                status = HSM_IGNORED_STATUS;
            }
            else if (configuration value matches value from a configuration descriptor in this device)
            {
                me->Configuration_Index = configuration;
                status = HSM_TRAN(USBHID_Device_Hsm_Configured_State);
            }
            else
            {
                #error "TODO: Respond to Host with a Request Error."
            }
            break;
        }

        case SET_DESCRIPTOR:
        {
            #error "TODO: Process this"
            break;
        }

        case SET_FEATURE:
        {
            if (referring to endpoint 0)
            {
                #error "TODO: Process this."
            }
            else
            {
                #error "TODO: Respond to Host with a Request Error."
            }
            break;
        }

        case SET_INTERFACE:
        {
            #error "TODO: Respond to Host with a Request Error."
            break;
        }

        case SYNCH_FRAME:
        {
            #error "TODO: Respond to Host with a Request Error."
            break;
        }

        default:
        {
            status = HSM_IGNORED_STATUS;
            break;
        }
    }
    return status;
}


/**
 * @brief Processes Control Transfers while the USBHID_Hsm is in the Confiured State.
 * In the Configured State the HID Device has completed the Enumeration Phase and is
 * fully functional.
 * 
 */
static HsmStatus USBHID_Device_Hsm_Configured_State_Process_Control_Transfer(USBHID_Device_Hsm * const me);
static HsmStatus USBHID_Device_Hsm_Configured_State_Process_Control_Transfer(USBHID_Device_Hsm * const me)
{
    HsmStatus status = HSM_HANDLED_STATUS;

    #error "TODO: Figure out Control Transfer request. Store in local variable 'Standard_Device_Request'."
    switch (Standard_Device_Request)
    {
        case CLEAR_FEATURE:
        {
            #error "TODO: Process this."
            break;
        }

        case GET_CONFIGURATION:
        {
            #error "TODO: Send me->Configuration_Index."
            break;
        }

        case GET_DESCRIPTOR:
        {
            #error "TODO: Process this."
            break;
        }

        case GET_INTERFACE:
        {
            #error "TODO: Process this."
            break;
        }

        case GET_STATUS:
        {
            if (interface/endpoint specified exists)
            {
                #error "TODO: Process this."
            }
            else
            {
                #error "TODO: Send Request Error."
            }
            break;
        }

        case SET_CONFIGURATION:
        {
            if (configuration == 0)
            {
                status = HSM_TRAN(USBHID_Device_Hsm_Address_State);
            }
            else if (configuration value matches value from a configuration descriptor in this device)
            {
                me->Configuration_Index = configuration;
            }
            else
            {
                #error "TODO: Respond to Host with a Request Error."
            }
            break;
        }

        case SET_DESCRIPTOR:
        {
            #error "TODO: Process this."
            break;
        }

        case SET_FEATURE:
        {
            #error "TODO: Process this."
            break;
        }

        case SET_INTERFACE:
        {
            #error "TODO: Process this."
            break;
        }

        case SYNCH_FRAME:
        {
            #error "TODO: Process this."
            break;
        }

        default: /* SET_ADDRESS is ignored. */
        {
            status = HSM_IGNORED_STATUS;
            break;
        }
    }
    return status;
}


/**
 * State Handler function definitions
 */

/**
 * @brief Initial Transition of the USBHID Hsm. Enters when the Constructor and
 * USBHID_Device_Hsm_Begin() are called. This will start up the Hsm and transition
 * into the USB Default State. The Dispatcher will figure out the appropriate 
 * Entry Event sequence to execute. In this case this is: 
 * Entry(USBHID_Device_Hsm_Top_State_Hndlr) -> Entry(USBHID_Device_Hsm_USB_Superstate_Hndlr) 
 * -> Entry(USBHID_Device_Hsm_Default_State_Hndlr)
 * 
 */
static HsmStatus USBHID_Device_Hsm_Init_State_Hndlr(Hsm * const me)
{
    return HSM_TRAN(USBHID_Device_Hsm_Default_State);
}


/**
 * @brief The Top-most State is just a container for all of the other substates in the USBHID Device
 * Hsm. Therefore it ignores all events dispatched to it. This State does not have an Entry Event
 * because the Default_State is entered when the USBHID Device Hsm is initialized. This State does
 * not have an Exit Event because the USBHID Device Hsm is always running and never exits.
 * 
 */
static Status USBHID_Device_Hsm_Top_State_Hndlr(USBHID_Device_Hsm * const me, const Event * const e)
{
    (void)me;
    (void)e;
    return (Status)IGNORED_STATUS;
}


/**
 * @brief Entering this State signifies a major error has occured and requies
 * a power cycle in order to exit this State. This will be entered
 * when a Power Cycle request event is dispatched via our application software's 
 * Error Handling functions.
 * 
 * The Hsm Dispatcher will figure out the necessary Exit Events to run.
 * It is also guaranteed that the Entry Event of this handler will 
 * execute after this initial transition. The current Entry Event disables the 
 * watchdog, global interrupts, and enters an infinite while loop.
 * 
 * This logic can be removed if the user wishes to have the rest of the
 * application code still execute, with this USBHID Device Hsm instance 
 * permanently disabled. If this is the case, any events dispatched 
 * will simply be ignored.
 * 
 */
static Status USBHID_Device_Hsm_Error_State_Hndlr(USBHID_Device_Hsm * const me, const Event * const e)
{
    Status status;

    switch(e->sig)
    {
        case ENTRY_EVENT:
        {
            #error "TODO: Disable Watchdog."
            cli();
            #error "TODO: Run Error Handler function."
            while(1){}
            status = HANDLED_STATUS;
            break;
        }

        case EXIT_EVENT:
        {
            status = HANDLED_STATUS;
            break;
        }

        /* Best practice to look for event handler in the superstate (the Top State) instead of 
        ignoring right away in case the State Tree changes in the future. */
        default:
        {
            status = SUPER(USBHID_Device_Hsm_Top_State);
            break;
        }
    }
    return status;
}


/**
 * @brief This is a container for the Default_State, Address_State, and Configured_State. This is
 * used to handle USB Reset and Power Cycle events dispatched to the USB HID Device Hsm.
 * 
 * Consider you are in State S which is either the Default_State, Address_State, and Configured_State.
 * If a USB Reset is dispatched, the Hsm transitions to the Default_State and the following sequence 
 * of events occur:
 * Exit Event(S) -> Exit Event(USB_Superstate) -> Entry Event(USB_Superstate) -> Entry Event(Default_State)
 * 
 * If a Power Cycle request is dispatched, the Hsm transitions to the Error_State and the following 
 * sequence of events take place:
 * Exit Event(S) -> Exit Event(USB_Superstate) -> Entry Event(Error_State)
 * 
 * This transition is automatically handled by the Hsm Dispatcher. All other events are ignored.
 * 
 */
static Status USBHID_Device_Hsm_USB_Superstate_Hndlr(USBHID_Device_Hsm * const me, const Event * const e)
{
    Status status;

    switch(e->sig)
    {
        case ENTRY_EVENT:
        {
            me->Device_State = USBHID_DEVICE_POWERED_STATE;
            #error "TODO: Reset and Initialize USB Hardware and Endpoint Configurations."
            status = HANDLED_STATUS;
            break;
        }

        case EXIT_EVENT:
        {
            #error "TODO: Detach USB Device from bus."
            me->Address = 0;
            me->Configuration_Index = 0;
            me->Device_State = USBHID_DEVICE_DISABLED_STATE;
            status = HANDLED_STATUS;
            break;
        }

        case POWER_CYCLE_REQ:
        {
            status = TRAN(USBHID_Device_Hsm_Error_State);
            break;
        }

        case HOST_RESET_REQ:
        case SOFTWARE_RESET_REQ:
        {
            status = TRAN(USBHID_Device_Hsm_Default_State);
            break;
        }

        /* Best practice to look for event handler in the superstate (the Top State) instead of 
        ignoring right away in case the State Tree changes in the future. */
        default:
        {
            status = SUPER(USBHID_Device_Hsm_Top_State);
            break;
        }
    }
    return status;
}


/**
 * @brief In this State, the USB device has been attached to the bus, powered, and reset. However it
 * has not been assigned a unique address yet. The device must only process GET_DESCRIPTOR, SET_ADDRESS,
 * and SET_FEATURE Control Transfers. If the host sets the device to a unique, nonzero address via
 * a SET_ADDRESS request the Hsm transitions to the Address_State.
 * 
 */
static Status USBHID_Device_Hsm_Default_State_Hndlr(USBHID_Device_Hsm * const me, const Event * const e)
{
    Status status;

    switch(e->sig)
    {
        case ENTRY_EVENT:
        {
            me->Device_State = USBHID_DEVICE_DEFAULT_STATE;
            me->Address = 0;
            me->Configuration_Index = 0;
            status = HANDLED_STATUS;
            break;
        }

        case EXIT_EVENT:
        {
            status = HANDLED_STATUS;
            break;
        }

        case CONTROL_TRANSFER_REQ:
        {
            status = USBHID_Device_Hsm_Default_State_Process_Control_Transfer(me);
            break;
        }

        default:
        {
            status = SUPER(USBHID_Device_Hsm_USB_Superstate);
            break;
        }
    }
    return status;
}


/**
 * @brief In this State, the USB Device is attached, powered, and has been assigned a unique address.
 * However the device has not been configured. See USB 2.0 Spec - Chapter 9.4 for how the device 
 * must process Control Transfers while in this State. 
 * 
 * If the Host sets the device's address back to 0 via a SET_ADDRESS request, the Hsm transitions
 * to the Default_State. If the Host sets the device's configuration to a valid Configuration
 * Descriptor via a SET_CONFIGURATION request, the Hsm transitions to the Configured_State.
 * 
 */
static Status USBHID_Device_Hsm_Address_State_Hndlr(USBHID_Device_Hsm * const me, const Event * const e)
{
    Status status;

    switch(e->sig)
    {
        case ENTRY_EVENT:
        {
            me->Device_State = USBHID_DEVICE_ADDRESS_STATE;
            me->Configuration_Index = 0;
            status = HANDLED_STATUS;
            break;
        }

        case EXIT_EVENT:
        {
            status = HANDLED_STATUS;
            break;
        }

        case CONTROL_TRANSFER_REQ:
        {
            status = USBHID_Device_Hsm_Address_State_Process_Control_Transfer(me);
            break;
        }

        default:
        {
            status = SUPER(USBHID_Device_Hsm_USB_Superstate);
            break; 
        }
    }
    return status;
}


/**
 * @brief In this State, the USB Device is attached, powered, has been assigned a unique address,
 * and has been configured. Therefore the device is fully operational and able to send
 * HID reports to the Host. 
 * 
 * See USB 2.0 Spec - Chapter 9.4 for how the device must process Control Transfers while in this State.
 * If the Host sets the device's configuration back to 0 via a SET_CONFIGURATION request, the Hsm
 * transitions to the Address_State.
 * 
 */
static Status USBHID_Device_Hsm_Configured_State_Hndlr(USBHID_Device_Hsm * const me, const Event * const e)
{
    Status status;

    switch(e->sig)
    {
        case ENTRY_EVENT:
        {
            me->Device_State = USBHID_DEVICE_CONFIGURED_STATE;
            memset( ((USBHID_Device_Hsm_Event *)e)->HIDReport, 0, sizeof(((USBHID_Device_Hsm_Event *)e)->HIDReport) );
            status = HANDLED_STATUS;
            break;
        }

        case EXIT_EVENT:
        {
            memset( ((USBHID_Device_Hsm_Event *)e)->HIDReport, 0, sizeof(((USBHID_Device_Hsm_Event *)e)->HIDReport) );
            status = HANDLED_STATUS;
            break;
        }

        case CONTROL_TRANSFER_REQ:
        {
            status = USBHID_Device_Hsm_Configured_State_Process_Control_Transfer(me);
            break;
        }

        case KEYPRESS_EVENT:
        {
            #error "TODO: Send HID Report"
            status = HANDLED_STATUS;
            break;
        }

        default:
        {
            status = SUPER(USBHID_Device_Hsm_USB_Superstate);
            break;
        }
    }
    return status;
}



/**
 * Public Functions
 */

/** 
 * TODO: Want to architect this so user is able to assign any Descriptor Configuration to the
 * HID Device. Right now it just sets the Device to the Default Configuration.
 * 
 * @brief Initialize a USBHID_Device Hsm Object with the Default Descriptor Configuration defined
 * at the beginning of this file. Starts the Hsm at the Init State.
 * 
 * @param me Pointer to USBHID_Device_Hsm type.
 * 
 * Please not that the user supplies their own descriptors. If an invalid descriptor configuration
 * is provided, the default descriptors are assigned.
 * 
 * @note The descriptors are packed structs but we can access the members directly because
 * GCC guarentees that misalignment will be handled by the compiler. Therefore this will
 * work even on targets that have strict alignment requirements.
 * 
 * 
 * Note that bcdUSB member is apart of a Packed Struct with potentially misaligned memory. GCC
 * compiler handles memory misalignment when accessing packed struct members directly but not 
 * via pointer access. The Run-time Endianness Swapping macro does use pointer access. However 
 * the macro expands to an inlined function (if compiling on Big Endian target) where we pass 
 * bcdUSB by value and make a copy of it. Therefore we do not access potentially misaligned 
 * memory directly.
 * 
 */
bool USBHID_Device_Hsm_Ctor(    
                                USBHID_Device_Hsm                           * const me,
                                const USB_Std_Device_Descriptor_t           * const Device_Descriptor,
                                const USB_Std_Configuration_Descriptor_t    * const Configuration_Descriptor,
                                const USB_Std_Interface_Descriptor_t        * const Interface_Descriptor,
                                const USB_HID_Std_HID_Descriptor_t          * const HID_Descriptor,
                                const USB_Std_Endpoint_Descriptor_t         * const Endpoint_Descriptor,
                                const uint8_t                               * const Report_Descriptor,
                                const uint8_t                               Report_Descriptor_Size
                            )
{
    /* TODO: Think going to change so user just supplies Endpoint, HID, and Report/Physical Descriptors 
        Device, Configuration, and Interface will be set to Default. 
        TODO: Possibly separate out Descriptor Checks into separate functions. */

    /* Used for Endianness Checks. */
    uint16_t bcdUSB;
    uint16_t wTotalLength;

    /* NULL Checks */
    if (!me || !Device_Descriptor || !Configuration_Descriptor || !Interface_Descriptor || !HID_Descriptor || \
        !Endpoint_Descriptor || !Report_Descriptor || !Report_Descriptor_Size)
    {
        return false;
    }
    else
    {
        bcdUSB          = LE16_RUNTIME(Device_Descriptor->bcdUSB);
        wTotalLength    = LE16_RUNTIME(Configuration_Descriptor->wTotalLength);
    }

    /* Valid Device Descriptor Check */
    if ((Device_Descriptor->bLength != sizeof(USB_Std_Device_Descriptor_t)) || \
        (Device_Descriptor->bDescriptionType != DEVICE_DESCRIPTOR_TYPE) || \
        (!(bcdUSB & 0x0F00)) || \   /*  Must be Little Endian. bcdUSB will always contain a Major Version in BCD format
                                        so we mask against that. On Little Endian targets the LE16_RUNTIME macro does 
                                        nothing so bcdUSB should be stored in the form 0x0V00 where V is the Major 
                                        Version. On Big Endian targets bcdUSB should be stored in the form 0x000V so it 
                                        is sent across the bus in Little Endian. */
        (bcdUSB > USB_VERSION) || \
        (Device_Descriptor->bDeviceClass != 0) || \
        (Device_Descriptor->bSubClass != 0) || \
        (Device_Descriptor->bDeviceProtocol != 0) || \
        (Device_Descriptor->bMaxPacketSize0 != 8 &&  Device_Descriptor->bMaxPacketSize0 != 16 && \
            Device_Descriptor->bMaxPacketSize0 != 32 && Device_Descriptor->bMaxPacketSize0 != 64) || \
        (Device_Descriptor->bNumConfigurations != 1))
    {
        return false;
    }

    /* Valid Configuration Descriptor Check */
    if ((Configuration_Descriptor->bLength != sizeof(USB_Std_Configuration_Descriptor_t)) || \
        (Configuration_Descriptor->bDescriptionType != CONFIGURATION_DESCRIPTOR_TYPE) || \
        (wTotalLength !=   (  sizeof(USB_Std_Configuration_Descriptor_t) \  /* This also indirectly checks if wTotalLength is in Little Endian. */
                            + sizeof(USB_Std_Interface_Descriptor_t) \
                            + sizeof(USB_Std_Endpoint_Descriptor_t) \
                            + sizeof(USB_HID_Std_HID_Descriptor_t) \
                            + Report_Descriptor_Size)) || \
        (Configuration_Descriptor->bNumInterfaces != 1) || \
        (Configuration_Descriptor->bmAttributes & 0b10011111 != 0b10000000) || \ /* Bits 0 to 4 are Zero. Bit 7 is set. */
        (Configuration_Descriptor->bMaxPower > USBHID_DEVICE_HSM_MAX_CURRENT))
    {
        return false;
    }

    /* Valid Interface Descriptor Check */

}


/**
 * @brief Initializes a USBHID_Device Hsm Object with the Default descriptor
 * configuration defined at the start of USBHIDDeviceHsm.c. This is a standard
 * US HID Keyboard Device with a max current draw of 100mA. There is 1 Endpoint
 * Descriptor for Endpoint 1 IN. Interrupt Transfers with 5ms Polling are used.
 * This is also a Remote Wakeup capable device.
 * 
 * @warning The USBHID_Device_Hsm Object supplied to the Constructor must be
 * initialized at compile-time. Dynamic Memory Allocation is not used.
 * 
 * @param me Pointer to an initialized USBHID_Device_Hsm Object.
 * 
 * @return True if USBHID_Device_Hsm Object supplied to the Constructor
 * was previously initialized. False otherwise.
 * 
 */
bool USBHID_Device_Hsm_Default_Ctor(USBHID_Device_Hsm * const me)
{
    bool sucess = false;

    if (me)
    {
        me->Descriptors.Device_Descriptor               = &Default_Device_Descriptor;
        me->Descriptors.Configuration_Descriptor        = &Default_Configuration_Descriptor;
        me->Descriptors.Interface_Descriptor            = &Default_Interface_Descriptor;
        me->Descriptors.HID_Descriptor                  = &Default_HID_Descriptor;
        me->Descriptors.Endpoint_Descriptor             = &Default_Endpoint_Descriptor;
        me->Descriptors.Report_Descriptor               = Default_Report_Descriptor; /* uint8_t array */
        me->Descriptors.Report_Descriptor_Size          = sizeof(Default_Report_Descriptor);
        me->Device_State                                = USBHID_DEVICE_DISABLED_STATE;
        me->Address                                     = 0;
        me->Configuration_Index                         = 0;
        Hsm_Ctor((Hsm *)me, USBHID_Device_Hsm_Top_State_Hndlr);
        success = true;
    }
    return success;
}


/**
 * @brief Runs the Initial State Handler function. This runs the Entry Events from
 * the Top State to the Default State (USBHID_Device_Hsm_Default_State).
 * 
 * @note Meant to only be called once at startup after the USBHID_Device_Hsm 
 * Constructor is called. Will do nothing if it is called any time afterwards.
 * 
 */
void USBHID_Device_Hsm_Begin(USBHID_Device_Hsm * const me)
{
    if ( ((Hsm *)me)->state == (StateHandler)USBHID_Device_Hsm_Init_State )
    {
        Hsm_Dispatch((Hsm *)me, (Event *)0);
    }
}

