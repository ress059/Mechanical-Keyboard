/**
 * @file USB.c
 * @author Ian Ress
 * @brief TODO: Description
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* TODO: Major cleanup and work */
#include <avr/interrupt.h>
#include <avr/io.h>
#include "AVRArch.h"
#include "USB.h"


/**
 * @brief Initializes the hardware registers of the USB peripheral.
 * 
 */
void USBHardwareInit(void)
{
     /* ATMega32U4 specific. Will generalize once have a baseline down.

     Step 1) Power on USB pads regulator
     * - Make sure USBE bit is set (enables the controller)
     * - Make sure OTGPADE is set (allow VBUS to go into regulator)
     * - Make sure FRZCLK bit is not set.
     * - Make sure DETACH bit is not set.
     * - Make sure SUSPI bit is not set.
     * - Make sure OTGPADE bit is set to actually power up the controller (enables voltage regulator)
      */
     
USBReg_Enable_USBRegulator();
USBReg_Unfreeze_Clock(); /* Clear FRZCLK bit */

     /* Step 2) Setup PLL frequency
        *- LSM bit determines if D+ or D- pullup is enabled (low speed or high speed device)


*/
     /* 

     * 
     * Step 2) Setup any USB interrupts you want.
     * Step 3) 
     */
}




















/**
 * @brief USB Endpoint ISR.
 * 
 */
ISR(USB_COM_vect)
{
    

}

/**
 * @brief TODO: Reads the UEINTx register  the type of packet 
 * 
 */
static inline uint8_t USB_Get_Endpoint_Flag(void);
static inline uint8_t USB_Get_Endpoint_Flag(void)
{
    return UEINTX;
}


/**
 * @brief Initializes USB peripheral. TODO: Perhaps break out into separate MCU-specific driver??
 * 
 */
static void USB_Hardware_Init(void);
static void USB_Hardware_Init(void)
{
    /* 0) Configure Endpoint0 on device */

    /* 1) Allocate memory in DPRAM for each endpoint.
            Will probably be 64 bytes for Endpoint 0 and 256 bytes for Endpoint 1. See Section 21.9 of ATMega32U4 */
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
 * @brief TODO: Control Endpoint
 * 
 */
static void USB_Control_Endpoint(void);
static void USB_Control_Endpoint(void)
{
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




