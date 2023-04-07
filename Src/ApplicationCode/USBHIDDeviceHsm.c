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
#include "Endian.h"
#include "USBConfig.h"
#include "USBHIDDeviceHsm.h"


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

/**
 * Start from bottom up (Endpoint -> Interface -> Configuration -> Device)
 */

/**
 * Endpoint Descriptor(s)
 */
static const USB_Std_Endpoint_Descriptor_t Default_Endpoint_Descriptor =
{
    .bLength                    = sizeof(USB_Std_Endpoint_Descriptor_t),
    .bDescriptorType            = ENDPOINT_DESCRIPTOR_TYPE,
    .bEndpointAddress           = 0b10000001,                       /* Endpoint 1 IN */
    .bmAttributes               = 0b00000011,                       /* Interrupt Endpoint */
    .wMaxPacketSize             = LE16_COMPILETIME(HID_ENDPOINT_SIZE),
    .bInterval                  = 5                                 /* 5ms Polling */
};
static const USB_Std_Endpoint_Descriptor_t * Default_Endpoint_Descriptors[] = {&Default_Endpoint_Descriptor};


/**
 * Report (and Physical) Descriptor(s)
 */
static const USB_HID_Report_And_Physical_Descriptors Default_Report_Descriptors[] =
{
    {
        .bDescriptorType            = HID_REPORT_DESCRIPTOR_TYPE,
        .wDescriptorLength          = LE16_COMPILETIME(sizeof(Default_Report_Descriptors)),
        .Report_Descriptor          = &Default_Report_Descriptor
    };
};


/**
 * HID Descriptor(s)
 */
static const USB_HID_Dynamic_HID_Descriptor_t Default_HID_Descriptor = 
{
    .HID_Descriptor_Header = 
    {
        .bLength                                    = (sizeof(struct USB_HID_Std_HID_Descriptor_Header) + 3),
        .bDescriptorType                            = HID_DESCRIPTOR_TYPE,
        .bcdHID                                     = LE16_COMPILETIME(HID_CLASS_VERSION),
        .bCountryCode                               = 33,                               /* U.S. Country Code. See USB HID Spec Section 6.1.2 - HID Descriptor */
        .bNumDescriptors                            = 1                                 /* Report Descriptor */
    },

    .Report_And_Physical_Descriptors                = &Default_Report_Descriptors       /* Assigning Report and Physical Descriptors to this specific HID Descriptor */
};
static const USB_HID_Dynamic_HID_Descriptor_t * Default_HID_Descriptors[] = {&Default_HID_Descriptor};


/**
 * Interface Descriptor(s)
 */
static const USB_HID_Dynamic_Interface_Descriptor_t Default_Interface_Descriptor = 
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
    .Endpoint_Descriptors       = &Default_Endpoint_Descriptors,    /* Assigning Endpoint Descriptors to this specific Interface Descriptor */
    .HID_Descriptors            = &Default_HID_Descriptors          /* Assigning HID Descriptors to this specific Interface Descriptor */
};
static const USB_HID_Dynamic_Interface_Descriptor_t Default_Interface_Descriptors[] = {&Default_Interface_Descriptor};


/**
 * Configuration Descriptor(s)
 */
static const USB_HID_Dynamic_Configuration_Descriptor_t Default_Configuration_Descriptor =
{
    .bLength                    = sizeof(USB_Std_Configuration_Descriptor_t),
    .bDescriptionType           = CONFIGURATION_DESCRIPTOR_TYPE,
    .wTotalLength               = LE16_COMPILETIME(   sizeof(USB_Std_Configuration_Descriptor_t) \              /* This Configuration Descriptor */
                                                    + sizeof(USB_Std_Interface_Descriptor_t) \                  /* We are only assigning One Interface Descriptor to this Configuration. */
                                                    + sizeof(USB_Std_Endpoint_Descriptor_t) \                   /* Endpoint 1 IN Descriptor */
                                                    + (sizeof(struct USB_HID_Std_HID_Descriptor_Header) + 3) \  /* HID Descriptor. We are only assigning One Report Descriptor to this HID Descriptor. */
                                                    + sizeof(Default_Report_Descriptor) ),                      /* Report Descriptor */
    .bNumInterfaces             = 1,
    .bConfigurationValue        = 1,
    .iConfiguration             = 0,
    .bmAttributes               = 0b0010000,                        /* Remote Wakeup */
    .bMaxPower                  = 50,                               /* 100mA max */
    .Interface_Descriptors      = &Default_Interface_Descriptors    /* Assigning Interface Descriptors to this specific Configuration Descriptor */
};
static const USB_HID_Dynamic_Configuration_Descriptor_t Default_Configuration_Descriptors[] = {&Default_Configuration_Descriptor};


/**
 * The Default Descriptor Configuration for the HID Device in the USB_HID Hsm Class.
 */
static const USB_HID_Descriptors_Collection Default_HID_Device = 
{
    .Device_Descriptor          = &Default_Device_Descriptor,
    .Configuration_Descriptors  = &Default_Configuration_Descriptors
};


// typedef struct
// {
//     const USB_Std_Device_Descriptor_t * const Device_Descriptor;
//     const USB_HID_Dynamic_Configuration_Descriptor_t * (* const Configuration_Descriptors)[];
// } USB_HID_Descriptors_Collection;


/* Can add Default Physical Descriptor Header here if needed */



/**
 * State Objects and State Handler function prototypes.
 * 
 */

/* Top-most State. Contains USB_Superstate and Error_State */
static Status USBHID_Device_Hsm_Top_State_Hndlr(USBHID_Device_Hsm * const me, const Event * const e);
static const State USBHID_Device_Hsm_Top_State = 
{
    (State *)0, /* Hsm Dispatcher uses NULL pointer to identify Top State has been reached. Do not change. */
    &USBHID_Device_Hsm_Top_State_Hndlr
};


static Status USBHID_Device_Hsm_Error_State_Hndlr(USBHID_Device_Hsm * const me, const Event * const e);
static const State USBHID_Device_Hsm_Error_State =
{
    (State *)&USBHID_Device_Hsm_Top_State,
    &USBHID_Device_Hsm_Error_State_Hndlr
};


/* Contains Default_State, Address_State, and Configured_State. USB 2.0 spec - Chapter 9 */
static Status USBHID_Device_Hsm_USB_Superstate_Hndlr(USBHID_Device_Hsm * const me, const Event * const e);
static const State USBHID_Device_Hsm_USB_Superstate =
{
    (State *)&USBHID_Device_Hsm_Top_State,
    &USBHID_Device_Hsm_USB_Superstate_Hndlr
};


static Status USBHID_Device_Hsm_Default_State_Hndlr(USBHID_Device_Hsm * const me, const Event * const e);
static const State USBHID_Device_Hsm_Default_State =
{
    (State *)&USBHID_Device_Hsm_USB_Superstate,
    &USBHID_Device_Hsm_Default_State_Hndlr
};


static Status USBHID_Device_Hsm_Address_State_Hndlr(USBHID_Device_Hsm * const me, const Event * const e);
static const State USBHID_Device_Hsm_Address_State =
{
    (State *)&USBHID_Device_Hsm_USB_Superstate,
    &USBHID_Device_Hsm_Address_State_Hndlr
};


static Status USBHID_Device_Hsm_Configured_State_Hndlr(USBHID_Device_Hsm * const me, const Event * const e);
static const State USBHID_Device_Hsm_Configured_State =
{
    (State *)&USBHID_Device_Hsm_USB_Superstate,
    &USBHID_Device_Hsm_Configured_State_Hndlr
};


/**
 * Control Transfers must be processed differently depending on the State you are in.
 * See USB 2.0 Spec Chapter 9.4 - Standard Device Requests
 */
static Status USBHID_Device_Hsm_Default_State_Process_Control_Transfer(USBHID_Device_Hsm * const me);
static Status USBHID_Device_Hsm_Address_State_Process_Control_Transfer(USBHID_Device_Hsm * const me);
static Status USBHID_Device_Hsm_Configured_State_Process_Control_Transfer(USBHID_Device_Hsm * const me);


/**
 * State Handler function definitions
 * 
 */

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
            me->Configuration = 0;
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
            me->Configuration = 0;
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
            me->Configuration = 0;
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
static Status USBHID_Device_Hsm_Address_State_Hndlr(USBHID_Device_Hsm * const me, const Event * const e)
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

/** TODO: Description
 * @brief Initialize a USBHID_Device Hsm Object with your custom Descriptor configuration.
 * 
 * @warning There are no checks to make sure bNumConfigurations, bNumInterfaces, bNumEndpoints, etc
 * are correct. Can result in stray pointer!
 * 
 * @note If no descriptors or an invalid descriptor configuration is provided, the default
 * descriptor configuration will be assigned to the object. These Descriptors and the Descriptor
 * Configuration is defined at the beginning of USBHIDDeviceHsm.c
 * 
 * @param me Pointer to USBHID_Device_Hsm type.
 * @param Std_Descriptors Device, Configuration, Interface, and Endpoint Descriptors to assign to this device.
 * A device can only have one Device Descriptor, but any number of Configuration, Interface, and Endpoint
 * Descriptors. The Constructor will parse through the supplied Descriptors.
 * @param HID_Descriptors HID, Report, and Physical Descriptors to assign to this device. A device can have any
 * number of HID, Report, and Physical Descriptors.
 * 
 */
void USBHID_Device_Hsm_Ctor(    USBHID_Device_Hsm * const me,
                                USB_Std_Descriptors_Collection * const Std_Descriptors,
                                USB_HID_Descriptor_Collection * const HID_Descriptors   )
{
    /* Device Descriptor Checks */
    // if (    (Device_Descriptor->bLength != sizeof(USB_Std_Device_Descriptor_t)) || \
    //         (Device_Descriptor->bcdUSB > USB version we support) || \
    //         (Device_Descriptor->bDeviceClass !=0) || \
    //         (Device_Descriptor->bSubClass != 0) || \
    //         (Device_Descriptor->bDeviceProtocol != 0) || \
    //         ((Device_Descriptor->bMaxPacketSize0 != 8) || (Device_Descriptor->bMaxPacketSize0 != 16) || (Device_Descriptor->bMaxPacketSize0 != 32) || (Device_Descriptor->bMaxPacketSize0 != 64)) || \
    //         (Device_Descriptor->bNumConfigurations != sizeof(*Configuration_Descriptor)) || \   /* sizeof on variable-length array so it is properly calculated at run-time */
    //          )
    // {
    //     #error "TODO: Make run-time error."
    //     return;
    // }

    /**
     * 
     * 0) CHECK IF Std_Descriptors and HID_Descriptors are NULL.
     * 
     * DEVICE DESCRIPTOR:
     *  1) Verify bLength = sizeof(USB_Std_Device_Descriptor_t)
     *  2) Verify bDescriptionType = DEVICE_DESCRIPTOR_TYPE
     *  3) Verify bcdUSB is the version we support
     *  4) Verify bDeviceClass = 0
     *  5) Verify bDeviceSubClass = 0
     *  6) Verify bDeviceProtocol = 0
     *  7) Verify bMaxPacketSize0 = CONTROL_ENDPOINT_SIZE (the endpoint 0 size the MCU supports)
     *  8) Verify bNumConfigurations = size of configuration descriptor array Std_Descriptors->(sizeof(Configuration_Descriptors) / sizeof(USB_Std_Configuration_Descriptor_t)
     * 
     * 
     * 
     */

    bool error = false;
    uint8_t bNumConfigurations = Std_Descriptors->Device_Descriptor->bNumConfigurations;

    if ( (Std_Descriptors == (USB_Std_Descriptors_Collection *)0) || (HID_Descriptors == (USB_HID_Descriptor_Collection *)0) )
    {
        error = true;
    }

    /**
     * Device Descriptor Check 
     */
    if (    (Std_Descriptors->Device_Descriptor->bLength != sizeof(USB_Std_Device_Descriptor_t)) || \
            (Std_Descriptors->Device_Descriptor->bDescriptionType != DEVICE_DESCRIPTOR_TYPE) || \
            (Std_Descriptors->Device_Descriptor->bcdUSB != (LE16_RUNTIME(USB_VERSION))) || \
            (Std_Descriptors->Device_Descriptor->bDeviceClass != 0x00) || \
            (Std_Descriptors->Device_Descriptor->bDeviceSubClass != 0x00) || \
            (Std_Descriptors->Device_Descriptor->bDeviceProtocol != 0x00) || \
            (Std_Descriptors->Device_Descriptor->bMaxPacketSize0 != CONTROL_ENDPOINT_SIZE) || \
            (Std_Descriptors->Device_Descriptor->bNumConfigurations == 0)
        )
    {
        error = true;
    }

    /**
     * Configuration Descriptor Checks
     */
    for (uint8_t i = 0, ; i < )

    /* Invalid configuration, assign default descriptors. */
    me->USBHID_Device_Hsm_Std_Descriptors = Std_Descriptors;
    me->USBHID_Device_Hsm_HID_Descriptors = HID_Descriptors;

}





// /**
//  * @brief Initial transition into the USB Hsm. This transitions the state 
//  * into the Pre-Operational State. Only called once when the State Machine
//  * first starts up.
//  * 
//  */
// static Status USBHID_Device_Hsm_Initial_State_Hndlr(USBHID_Device_Hsm * const me, const Event * const e);
// static Status USBHID_Device_Hsm_Initial_State_Hndlr(USBHID_Device_Hsm * const me, const Event * const e)
// {
//     (void)me;
//     (void)e;
//     return TRAN(USBHID_Device_Hsm_PreOperational_State);
// }






/**
 * @brief Calls the USBHID_Device_Hsm Constructor and runs the Initial State Handler 
 * function of the USB Hsm. This function transitions the USB Hsm state 
 * to the Pre-Operational State then runs the Entry Event of the 
 * Pre-Operational State Handler. This resets and initializes the USB hardware.
 * 
 * @note Meant to only be called once at startup since only one USBHID_Device_Hsm
 * object can be defined. If this is called again the function will 
 * simply return and no changes will be applied to the USB Hsm.
 * 
 */
void USBHID_Device_Hsm_Begin(void)
{
    if (USBHID_Device_Hsm_Me.hsm.state != (State *)0)
    {
        return;
    }
    else
    {
        Hsm_Ctor((Hsm *)&USBHID_Device_Hsm, &USBHID_Device_Hsm_Initial_State_Hndlr);
        Hsm_Begin((Hsm *)&USBHID_Device_Hsm, (Event *)0);
    }
}












static Status USBHID_Device_Hsm_Default_State_Process_Control_Transfer(USBHID_Device_Hsm * const me)
{
    State status;
    #error "TODO: Figure out Control Transfer request. Store in local variable 'Standard_Device_Request'."

    switch (Standard_Device_Request)
    {
        case GET_DESCRIPTOR:
            #error "TODO: Process this"
            status = HANDLED_STATUS;
            break;

        case SET_ADDRESS:
            #error "TODO: Process this"
            if (address > 0) 
            {
                me->Address = address;
                status = TRAN(USBHID_Device_Hsm_Address_State);
            }
            else
            {
                status = IGNORED_STATUS;
            }
            break;

        case SET_FEATURE:
            #error "TODO: Process SET_FEATURE(TEST_MODE) and SET_FEATURE(TEST_SELECTOR). Otherwise ignore"
            if (TEST_MODE || TEST_SELECTOR)
            {
                status = HANDLED_STATUS;
            }
            else
            {
                status = IGNORED_STATUS;
            }
            break;
        
        default: /* CLEAR_FEATURE, GET_CONFIGURATION, GET_INTERFACE, GET_STATUS, SET_CONFIGURATION, SET_DESCRIPTOR, SET_INTERFACE, and SYNCH_FRAME requests are ignored. */
            status = IGNORED_STATUS;
            break;
    }
    return status;
}


static Status USBHID_Device_Hsm_Address_State_Process_Control_Transfer(USBHID_Device_Hsm * const me)
{
    Status status = HANDLED_STATUS;
    #error "TODO: Figure out Control Transfer request. Store in local variable 'Standard_Device_Request'."

    switch (Standard_Device_Request)
    {
        case CLEAR_FEATURE:
            if (referring to endpoint 0)
            {
                #error "TODO: Process this."
            }
            else
            {
                #error "TODO: Respond to Host with a Request Error."
            }
            break;

        case GET_CONFIGURATION:
            #error "TODO: Return a value of 0 to the Host."
            break;

        case GET_DESCRIPTOR:
            #error "TODO: Process this."
            break;

        case GET_INTERFACE:
            #error "TODO: Respond to Host with Request Error."
            break;

        case GET_STATUS:
            if (referring to endpoint 0)
            {
                #error "TODO: Process this."
            }
            else
            {
                #error "TODO: Respond to Host with a Request Error."
            }
            break;

        case SET_ADDRESS:
            #error "TODO: Process this"
            if (address == 0) 
            {
                status = TRAN(USBHID_Device_Hsm_Default_State);
            }
            else
            {
                me->Address = address;
            }
            break;

        case SET_CONFIGURATION:
            #error "TODO: Process this"
            if (configuration == 0)
            {
                status = IGNORED_STATUS;
            }
            else if (configuration value matches value from a configuration descriptor in this device)
            {
                me->Configuration = configuration;
                status = TRAN(USBHID_Device_Hsm_Configured_State);
            }
            else
            {
                #error "TODO: Respond to Host with a Request Error."
            }
            break;

        case SET_DESCRIPTOR:
            #error "TODO: Process this"
            break;

        case SET_FEATURE:
            if (referring to endpoint 0)
            {
                #error "TODO: Process this."
            }
            else
            {
                #error "TODO: Respond to Host with a Request Error."
            }
            break;

        case SET_INTERFACE:
            #error "TODO: Respond to Host with a Request Error."
            break;

        case SYNCH_FRAME:
            #error "TODO: Respond to Host with a Request Error."
            break;

        default:
            status = IGNORED_STATUS;
            break;
    }
    return status;
}


static Status USBHID_Device_Hsm_Configured_State_Process_Control_Transfer(USBHID_Device_Hsm * const me)
{
    Status status = HANDLED_STATUS;

    #error "TODO: Figure out Control Transfer request. Store in local variable 'Standard_Device_Request'."
    switch (Standard_Device_Request)
    {
        case CLEAR_FEATURE:
            #error "TODO: Process this."
            break;

        case GET_CONFIGURATION:
            #error "TODO: Send me->Configuration."
            break;

        case GET_DESCRIPTOR:
            #error "TODO: Process this."
            break;

        case GET_INTERFACE:
            #error "TODO: Process this."
            break;

        case GET_STATUS:
            if (interface/endpoint specified exists)
            {
                #error "TODO: Process this."
            }
            else
            {
                #error "TODO: Send Request Error."
            }
            break;

        case SET_CONFIGURATION:
            if (configuration == 0)
            {
                status = TRAN(USBHID_Device_Hsm_Address_State);
            }
            else if (configuration value matches value from a configuration descriptor in this device)
            {
                me->Configuration = configuration;
            }
            else
            {
                #error "TODO: Respond to Host with a Request Error."
            }
            break;


        case SET_DESCRIPTOR:
            #error "TODO: Process this."
            break;

        case SET_FEATURE:
            #error "TODO: Process this."
            break;

        case SET_INTERFACE:
            #error "TODO: Process this."
            break;

        case SYNCH_FRAME:
            #error "TODO: Process this."
            break;

        default: /* SET_ADDRESS is ignored. */
            status = IGNORED_STATUS;
            break;
    }
    return status;
}

