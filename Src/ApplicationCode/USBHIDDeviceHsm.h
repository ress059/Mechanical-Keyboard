/**
 * @file USBHIDDeviceHsm.h
 * @author Ian Ress
 * @brief Hierarchical State Machine for the USB Handler. Inherits the Hsm Base Class.
 * Only one USBHsm can be created.
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef USBHIDDEVICEHSM_H
#define USBHIDDEVICEHSM_H

#include "Hsm.h"
#include "USBStdDescriptors.h"


/* USB HID Device Hsm Base Class */
// typedef struct
// {
//     struct USBHID_Device_Hsm_Device_Descriptor
//     {
//         const USB_Std_Device_Descriptor_t * const Device_Descriptor;
//     };

//     struct USBHID_Device_Hsm_Configuration_Descriptor
//     {
//         struct USBHID_Device_Hsm_Device_Descriptor * const Device;
//         const USB_Std_Configuration_Descriptor_t * const Configuration_Descriptor;
//     } arr[];

// } USBHID_Device_Hsm_Descriptors;



typedef struct
{
    Hsm hsm; /* Inherit Hsm Base Class */

    /* Private Members */
    struct
    {
        const USB_Std_Device_Descriptor_t * const Device_Descriptor;
        
        const struct Configuration_Descriptor_t
        {
            /* Each Configuration Descriptor belongs to this Device (an instance of USBHID_Device_Hsm). */
            const USB_Std_Configuration_Descriptor_t * const Configuration_Descriptor;
        } Configuration_Descriptors[];

        const struct Interface_Descriptor_t
        {
            const struct Configuration_Descriptor_t * const Configuration;  /* Configuration each Interface Descriptor belongs to. */
            const USB_Std_Interface_Descriptor_t * const Interface_Descriptor;
        } Interface_Descriptors[];
        
   
        
    } Descriptors;


   

    enum
    {
        USBHID_DEVICE_ATTACHED_STATE,
        USBHID_DEVICE_POWERED_STATE,
        USBHID_DEVICE_DEFAULT_STATE,
        USBHID_DEVICE_ADDRESS_STATE,
        USBHID_DEVICE_CONFIGURED_STATE,
        USBHID_DEVICE_SUSPENDED_STATE,
        USBHID_DEVICE_DISABLED_STATE    /* Not defined in USB Spec. Signifies the USB HID Device Hsm instance is disabled - either because it is starting up or a major error has occured. */
    } Device_State; /* Visible USB Device States. Chapter 9 of USB 2.0 Spec. */

    /* TODO: Add HID Descriptor */

    uint8_t Address;                /* The address the Host sets the USB Device to. This is updated when a SET_ADDRESS request is received. Otherwise the default Address of 0 is used. */
    uint8_t Configuration_Index;    /* The Configuration Descriptor the Device uses. This is updated when a SET_CONFIGURATION request is received. Otherwise it is 0. */

} USBHID_Device_Hsm;


/* USB HID Device Hsm Event Class */
typedef struct
{
    Event event; /* Inherit Event Base Class */

    /* Private Members */
    uint8_t HIDReport[8];
} USBHID_Device_Hsm_Event;


/* Event Signals specific to USBHsm */
enum USBHID_Device_Hsm_Event_Sigs
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


void USBHID_Device_Hsm_Ctor(    USBHID_Device_Hsm * const me, 
                                const USB_Std_Device_Descriptor_t * const Device_Descriptor, 
                                const USB_Std_Configuration_Descriptor_t * (*const Configuration_Descriptor)[],
                                const USB_Std_Interface_Descriptor_t * (*const Interface_Descriptor)[],
                                const USB_Std_Endpoint_Descriptor_t * (*const Endpoint_Descriptor)[]    );
void USBHID_Device_Hsm_Begin(void);
void USBHID_Device_Hsm_Dispatch(const USBHID_Device_Hsm_Event * const e);

#endif /* USBHIDDEVICEHSM_H */