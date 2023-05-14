/**
 * @file USB.c
 * @author Ian Ress
 * @brief TODO: Description
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#define ONLY_INCLUDE_USBREGISTERS_H_IN_USB_C_

/* TODO: Major cleanup and work */
#include <stdbool.h>
#include <util/atomic.h>
#include "USB.h"
#include "USBConfig.h"
#include "USBEventHandler.h"
#include "USBRegisters.h"


/**
 * @brief When initializing the USB controller, a clock source must be selected
 * and enabled. This defines the maximum number of times to check if the clock
 * is successfully enabled before throwing a user-defined error event.
 * 
 */
#define MAX_CLOCK_ENABLE_POLLS                  20

/**
 * @brief After the PLL is enabled you must wait for the PLL to lock before
 * proceeding. This defines the maximum number of times to check if the
 * PLL is locked before throwing a user-defined error event.
 * 
 */
#define MAX_PLL_LOCK_POLLS                      20

/**
 * @brief When the device boots up, it waits for the host to send a
 * a reset signal. This defines the maximum number of times to check
 * if the host sent a reset signal on the bus before throwing a
 * user-defined error.
 * 
 * @note The way the USB stack is structured, everytime the bus boots
 * up, it will first detach the USB Controller from the bus and reset
 * the controller. This should cause the host to send a bus reset signal.
 * 
 */
#define MAX_HOST_RESET_POLLS                    100

/**
 * @brief TODO:
 * 
 */
#define MAX_ENUMERATION_POLLS                   100


/**
 * @brief Connects the VBUS pad to the USB controller and enables the 
 * controller's internal regulator, depending how the user configures
 * settings in USBConfig.h and which target MCU is used.
 * 
 */
static void USB_Power_On(void);
static void USB_Power_On(void)
{
    #if defined(USB_USE_VBUS_DETECTION)
        USBReg_Enable_VBus();
    #else
        USBReg_Disable_VBus();
    #endif
    USBReg_Enable_USBRegulator(); /* Blank function if USB Controller doesn't have regulator. */
}


/**
 * @brief Sets the PLL to use the oscillator chosen in @p USBConfig.h
 * 
 * @warning This also sets the CPU clock to the selected oscillator, and disables the other.
 * For example if PLL is configured to use the Internal Oscillator, the CPU uses the Internal
 * Oscillator and the External Oscillator is disabled.
 * 
 * @return true if successful. False if the selected clock source is not successfully enabled
 * after a user-defined amount of polls, @p MAX_CLOCK_ENABLE_POLLS 
 * 
 */
static bool USB_Set_PLL_Clock(void);
static bool USB_Set_PLL_Clock(void)
{
    bool success = true;

    //USBReg_PLL_Disable(); /* Disable PLL. May just put in startup instead */
    #if defined(USB_USE_INTERNAL_OSCILLATOR)
        USBReg_Enable_InternalOsc();
        for (uint8_t polls = 0; ( (polls < (MAX_CLOCK_ENABLE_POLLS)) && (!USBReg_Is_InternalOsc_Ready()) ); polls++)
    #else
        USBReg_Enable_ExternalOsc();
        for (uint8_t polls = 0; ( (polls < (MAX_CLOCK_ENABLE_POLLS)) && (!USBReg_Is_ExternalOsc_Ready()) ); polls++)
    #endif
        {
            if (polls == (MAX_CLOCK_ENABLE_POLLS - 1))
            {
                success = false;
            }
        }

    #if defined(USB_USE_INTERNAL_OSCILLATOR)
        USBReg_Set_CPU_Clock_InternalOsc();
        USBReg_Disable_ExternalOsc();
        USBReg_PLL_Select_InternalOsc();
    #else
        USBReg_Set_CPU_Clock_ExternalOsc();
        USBReg_Disable_InternalOsc();
        USBReg_PLL_Select_ExternalOsc();
    #endif

    return success;
}


/**
 * @brief Configures the PLL and CPU clock. Also enables the PLL. 
 * 
 * @note Both the PLL and CPU will use the same clock source.
 * 
 * @return true if successful. False if the PLL does not lock after a 
 * user-defined amount of polls, @p MAX_PLL_LOCK_POLLS
 * 
 */
static bool USB_Set_PLL_Prescalars_And_Enable(void);
static bool USB_Set_PLL_Prescalars_And_Enable(void)
{
    bool success = true;

    USBReg_PLL_Set_Prescalar();
    USBReg_PLL_Set_Postscalar();
    USBReg_PLL_Enable();

    for (uint8_t polls = 0; ( (polls < (MAX_PLL_LOCK_POLLS)) && (!USBReg_Is_PLL_Ready()) ); polls++)
    {
        if (polls == (MAX_PLL_LOCK_POLLS - 1))
        {
            success = false;
        }
    }

    return success;
}


/**
 * @brief Enables the USB controller's clock and sets the proper speed.
 * 
 */
static void USB_Configure_USB_Speed(void);
static void USB_Configure_USB_Speed(void)
{
    #if defined(USB_LOW_SPEED_DEVICE)
        USBReg_Set_Low_Speed();
    #elif defined(USB_FULL_SPEED_DEVICE)
        USBReg_Set_Full_Speed();
    #else
        "Currently only support Low and Full Speed."
    #endif
}


/**
 * @brief Sets up the Control Endpoint with a single bank.
 * The endpoint's size is user-definable by changing
 * the value of @p USB_CONTROL_ENDPOINT_SIZE
 * 
 * @return true if endpoint configuration was successful. 
 * False otherwise
 * 
 */
static bool USB_Configure_Control_Endpoint(void);
static bool USB_Configure_Control_Endpoint(void)
{
    USBReg_Set_Current_Endpoint(0);
    USBReg_Disable_Endpoint();
    USBReg_Deallocate_Endpoint_Memory();
    USBReg_Enable_Endpoint();
    USBReg_Reset_Endpoint_Configuration();
    /* TODO: Can we do multiple writes like this to UECFG0X and UECFG1X registers? */
    USBReg_Set_Endpoint_Direction(ENDPOINT_DIR_OUT);
    USBReg_Set_Endpoint_Type(ENDPOINT_CONTROL);
    USBReg_Set_Number_Of_Banks(ENDPOINT_SINGLE_BANK);
    USBReg_Set_Endpoint_Size(USB_CONTROL_ENDPOINT_SIZE); /* Valid size is checked at compile-time in CompileChecks.h */
    USBReg_Allocate_Endpoint_Memory();
    USBReg_Disable_All_Endpoint_Interrupts();

    return (USBReg_Is_Endpoint_Configured());
}


/**
 * @brief Sets up the HID Endpoint as an Interrupt IN Endpoint
 * with a single bank. The endpoint's size is user-definable 
 * by changing the value of @p HID_ENDPOINT_SIZE
 * 
 * @note This function sets up the HID Endpoint as
 * Endpoint 1. Adjust @p USBReg_Set_Current_Endpoint()
 * call to change this if desired.
 * 
 * @note Only an Interrupt IN endpoint is configured as the
 * USB HID spec does not require an Interrupt OUT endpoint.
 * As a result, HID output reports generated by the host
 * are transmitted to the control endpoint. You must program
 * the Interrupt OUT endpoint configuration and define an
 * additional endpoint descriptor if desired.
 * 
 * @return true if endpoint configuration was successful. 
 * False otherwise
 * 
 */
static bool USB_Configure_HID_Endpoint(void);
static bool USB_Configure_HID_Endpoint(void)
{   
    USBReg_Set_Current_Endpoint(HID_ENDPOINT_NUMBER);
    USBReg_Disable_Endpoint();
    USBReg_Deallocate_Endpoint_Memory();
    USBReg_Enable_Endpoint();
    USBReg_Reset_Endpoint_Configuration();
    /* TODO: Can we do multiple writes like this to UECFG0X and UECFG1X registers? */
    USBReg_Set_Endpoint_Direction(ENDPOINT_DIR_IN);
    USBReg_Set_Endpoint_Type(ENDPOINT_INTERRUPT);
    USBReg_Set_Number_Of_Banks(ENDPOINT_SINGLE_BANK);
    USBReg_Set_Endpoint_Size(HID_ENDPOINT_SIZE); /* Valid size is checked at compile-time in CompileChecks.h */
    USBReg_Allocate_Endpoint_Memory();
    USBReg_Disable_All_Endpoint_Interrupts();

    return (USBReg_Is_Endpoint_Configured());
}


/**
 * @brief TODO: 
 * 
 */
static void USB_Power_Off(void);
static void USB_Power_Off(void)
{
    USBReg_Disable_All_USB_Interrupts();
    USBReg_Clear_All_Endpoints();
    USBReg_Detach_USB_Controller();
    USBReg_Disable_USB_Controller();
    USBReg_PLL_Disable();
    USBReg_Disable_USBRegulator();
}


/**
 * @brief Initializes the hardware registers of the USB peripheral. If an error
 * occurs, a user-defined error handler will execute. These events have the prefix
 * @p USB_EVENT_ERROR
 * See the specific USB_EVENT_ERROR function of interest for more in-depth .
 * comments pertaining to it.
 * 
 */
static void USB_Hardware_Init(void);
static void USB_Hardware_Init(void)
{
    USB_Power_On();

    if (!USB_Set_PLL_Clock())
    {
        USB_EVENT_ERROR_Clock_Enable_Failure();
    }

    if (!USB_Set_PLL_Prescalars_And_Enable())
    {
        USB_EVENT_ERROR_PLL_Lock_Failure();
    }

    USBReg_Unfreeze_Clock();
    USB_Configure_USB_Speed();

    if ( (!USB_Configure_Control_Endpoint()) || (!USB_Configure_HID_Endpoint()) )
    {
        USB_EVENT_ERROR_Endpoint_Setup_Failure();
    }
}


/**
 * @brief Enables the USB controller. Before attaching the controller
 * to the bus, the end of reset interrupt is enabled. This interrupt
 * is categorized under a general USB interrupt and executes whenever
 * the host requests a device reset (new device plugged into the bus,
 * there's an error, etc.) This interrupt MUST be enabled as it is
 * the driving force behind the USB_Device_State state machine.
 * 
 */
static void USB_Controller_Begin(void);
static void USB_Controller_Begin(void)
{
    USBReg_Enable_USB_Controller();
    USBReg_Enable_USB_Interrupt(USB_END_OF_RESET_INTERRUPT);
    USBReg_Attach_USB_Controller();
}


/**
 * @brief TODO: 
 * 
 */
static void USB_Process_Control_Transfer(void);
static void USB_Process_Control_Transfer(void)
{
    /* Read endpoint bank */


    /*          CONTROL WRITE - READING DATA FROM HOST
    
        1) CONTROL TRANSFER - SETUP STAGE
            NOTE: clearing RXSPTI, RXOUTI, and TXINI clears the endpoint buffer.

            - RXSPTI bit in UEINTx register is set by hardware when host sends a SETUP token packet.
            - Firmware reads DATA packet in endpoint buffer then clears RXSPTI bit in UEINTx register.
            - Hardware sends back ACK to host.
        

        2) CONTROL TRANSFER - DATA OUT STAGE (read data from host)
            - RXOUTI bit in UEINTx register is set by hardware when host sends an OUT token packet.
            - Firmware reads DATA packet in endpoint buffer then clears RXOUTI bit in UEINTx register.
            - Hardware sends back ACK to host. 
            - Cycle repeats until all data is read. NAKINI bit in UEINTx register is set when host has sent all data.

        3) CONTROL TRANSFER - STATUS STAGE
            - Ensure NAKINI bit in UEINTx register is set. This means SETUP stage has started and all data has been read.
            - Clear NAKINI bit.
            - Clear TXINI bit in UEINTx register. This sends a Zero Length DATA packet to host.
         */



            /*          CONTROL READ - WRITING DATA TO HOST
    
        1) CONTROL TRANSFER - SETUP STAGE
            - Same as CONTROL TRANSFER - READING DATA FROM HOST

        2) CONTROL TRANSFER - DATA IN STAGE (write data to host)
            - Put data into endpoint buffer (Endpoint0 IN).
            - Ensure TXINI bit is set. (ready to accept IN Token packet)
            - Clear TXINI bit in UEINTx register. (Sends data, ready to accept new data)
            - Repeat until all data is sent..

        3) CONTROL TRANSFER - STATUS STAGE
            - Hardware will set NAKOUTI bit in UEINTx register when STATUS STAGE happens.
            - Clear NAKOUTI bit and clear RXOUTI bit in UEINTx register to send ACK back to host.

            - Ensure NAKINI bit in UEINTx register is set. This means SETUP stage has started and all data has been read.
            - Clear TXINI bit in UEINTx register. This sends a Zero Length DATA packet
         */
}


/* Disable global interrupts before this init call and reenable after this init call. */
// void USB_Init(void)
{
    USB_Power_Off();
    USB_Hardware_Init();
    USB_Controller_Begin();
}


/**
 * @brief Updates the USB Controller's state machine.
 * 
 */
static void USB_Poll(void);
static void USB_Poll(void)
{
    /* Reset is highest priority */
    if (USBReg_Is_Bus_Reset())
    {
        USBReg_Clear_Bus_Reset_Flag();
        USB_Device_State = USB_DEVICE_STATE_HOST_RESET;
    }

    else if ((USBReg_Is_Setup_TokenPacket_Received()) && (USB_Device_State != USB_DEVICE_STATE_HOST_RESET))
    {
        USB_Device_State = USB_DEVICE_STATE_ENUMERATION;
    }
}


void USB_ControlEP_Task(void)
{
    static uint16_t Polls = 0;

    USBReg_Set_Current_Endpoint(0);
    USBReg_Set_Endpoint_Direction(ENDPOINT_DIR_OUT);
    
    /* TODO: Try to make a macro that only disables the general usb interrupt and endpoint interrupts 
    as I still want systick interrupt to be running. */
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        USB_Device_State_t USB_Device_State_Copy, USB_Device_State_Prev = USB_Device_State;
    }

    switch (USB_Device_State_Copy)
    {
        case USB_DEVICE_STATE_STARTUP:
            if ((Polls++) > MAX_HOST_RESET_POLLS)
            {
                USB_EVENT_ERROR_Host_Reset_Not_Received();
            }
            break;

        case USB_DEVICE_STATE_HOST_RESET:
            if ( (!USB_Configure_Control_Endpoint()) || (!USB_Configure_HID_Endpoint()) )
            {
                USB_EVENT_ERROR_Endpoint_Setup_Failure();
            }

            Polls = 0;
            USB_Device_State_Copy = USB_DEVICE_STATE_CONFIGURED;
            break;

        case USB_DEVICE_STATE_CONFIGURED:
            /* TODO: */
            if (token packet received)
            {
                process control transfer
                if (token packet is address setup)
                {
                    Polls = 0;
                    USB_Device_State_Copy = USB_DEVICE_STATE_ADDRESS_SETUP;
                }
                
            }
            else if ((Polls++) > MAX_ENUMERATION_POLLS)
            {
                USB_EVENT_ERROR_Enumeration_Failure();
            }

            break;
        
        case USB_DEVICE_STATE_ADDRESS_SETUP:
            /* TODO: Go through address setup Once done: */
            USB_Device_State_Copy = USB_DEVICE_STATE_ENUMERATION;
        
        case USB_DEVICE_STATE_ENUMERATION:
            /* TODO: Go through enumeration. Once done: */
            USB_Device_State_Copy = USB_DEVICE_STATE_OPERATIONAL;

        case USB_DEVICE_STATE_OPERATIONAL:
            break;

        default:
            USB_EVENT_ERROR_USB_State_Machine_Corrupted();
            break;
    }

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        /* If an interrupt that changes USB_Device_State fires in the middle of executing 
        this state machine, we would miss this change of state by overwriting USB_Device_State. 
        Prevent this from happening. */
        if (USB_Device_State == USB_Device_State_Prev)
        {
            USB_Device_State = USB_Device_State_Copy;
        }    
    }
}


    if (USBReg_Is_Bus_Reset())
    {
        USBReg_Clear_Bus_Reset_Flag();
        if ( (!USB_Configure_Control_Endpoint()) || (!USB_Configure_HID_Endpoint()) )
        {
            USB_EVENT_ERROR_Endpoint_Setup_Failure();
        }
    }

    /* Enumeration*/


    if (USBReg_Is_Setup_TokenPacket_Received())
    {
        USB_Process_Control_Transfer();
    }
}



void USB_HID_Task(void)
{
    USBReg_Set_Current_Endpoint(1);
    USBReg_Set_Endpoint_Direction(ENDPOINT_DIR_OUT);

}







/**
 * @brief TODO: Reads the endpoint buffer
 * 
 */
static void USB_Endpoint_Read(void);
static void USB_Endpoint_Read(void)
{
    /* OUT Endpoint notification (receiving data from host): */
    /* 0) Hardware sets the FIFOCON and RXOUTI bits in the UEINTx register */
    /* NOTE: Optional interrupt can be enabled (RXOUTE bit). */
    /* 1) Whether interrupt is enabled or not, read data in buffer bank then clear RXOUTI bit. */
    /* 2) Clear FIFOCON bit in the following instruction (CAN'T clear FIFOCON and RXOUTI at same time). 
        If there's more data in the bank, clearing FIFOCON will cause hardware to switch to the next
        bank automatically and set FIFOCON/RXOUTI bits accordingly depending on type of data after. */

    /* RWAL bit in UEINTx register is set to 1 if firmware can read data in bank. Hardware automatically
    clears this bit if the bank's empty. */

    if (UEINTx)

    (1 << RWAL) | (1 << FIFOCON) | (1 << RXOUTI)


    /* SETUP Endpoint notification: */
    /* 0) Hardware sets the FIFOCON and RXSPTI bits in the UEINTx register */

    /* IN Endpoint (sending data to host): */
    /* 0) Hardware sets the FIFOCON and TXIN bits in the UEINTx register when the endpoint buffer 
        is free. */


    /*  0)   Hardware sets the RXOUTI bit in the UEINTx register when there's data placed 
    in the endpoint buffer. Can optionally enable an endpoint interrupt to trigger when this happens.

        1)   RXSPTI bit */

}





/**
 * @brief TODO:
 * 
 */
// void USB_Init(void)
// {
//     /*  Call USB_Hardware_Init()
//         1) Host sends SETUP token packet and DATA0 packet (containing 8byte Device Descriptor request)
//         2) Process SETUP token packet, place address value in UADD while keeping ADDEN cleared.
//         3) RXSPTI bit in UIENTx register 

//         4)? Send IN command of 0 bytes (Zero length data packet)
//         5) Set ADDEN bit*/

//     /* Endpoint0 is selected by default on reset. */
//     UECFG0x
// }




