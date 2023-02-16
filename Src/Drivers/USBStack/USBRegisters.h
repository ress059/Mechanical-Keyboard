/** @file USBRegisters.h
*
* @brief Used whenever USB registers of target MCU need to be read or manipulated. AVR_reg_t is
* the word-size of the target microcontroller and will be defined at compile-time. This typedef
* is used because all of these functions will be called by the general USB stack that applies
* to all AVR targets.
*
* Author: Ian Ress
*
*/ 

#ifndef USBREGISTERS_H
#define USBREGISTERS_H

#include <stdbool.h>
#include <avr/io.h>
#include "avr_arch.h"


/**
 * @brief Enables the USB controller.
 * 
 * \note This MUST be called to start the USB controller.
 * 
 */
static inline void USBReg_EnableUSB(void);
static inline void USBReg_EnableUSB(void)
{
    USBCON |= (1 << USBE);
}


/**
 * @brief Resets the USB controller.
 * 
 */
static inline void USBReg_ResetUSB(void);
static inline void USBReg_ResetUSB(void)
{
    USBCON &= ~(1 << USBE);
}


/**
 * @brief Enables the VBUS pad connected to the USB controller.
 * 
 * \note This is not used to power up the USB controller. It is mainly used to detect
 * when a device is present by allowing you to read the VBUS voltage level.
 * 
 */
static inline void USBReg_Enable_VBus(void);
static inline void USBReg_Enable_VBus(void)
{
    USBCON |= (1 << OTGPADE);
}


/**
 * @brief Disables the VBUS pad connected to the USB controller.
 * 
 */
static inline void USBReg_Disable_VBus(void);
static inline void USBReg_Disable_VBus(void)
{
    USBCON &= ~(1 << OTGPADE);
}


/**
 * @brief Enables the USB controller's internal voltage regulator.
 * 
 * \note The internal voltage regulator should be enabled/disabled depending on the PCB
 * layout and whether the device will be bus powered or self powered.
 * 
 * If the device is bus powered the internal regulator must be enabled in all cases
 * to lower the voltage from 5V to 3.6V.
 * 
 * If the device is self powered the usage of the internal regulator depends on the MCU
 * logic level. If the MCU is 3.4V to 5.5V then the internal regular should be enabled.
 * 
 * 
 * Firmware MUST call this during USB initialization to power the USB controller.
 * See Section 21.3 Typical Application Development of ATMega32U4 datasheet.
 */
static inline void USBReg_Enable_USBRegulator(void);
static inline void USBReg_Enable_USBRegulator(void)
{
    UHWCON |= (1 << UVREGE);
}


/**
 * @brief Disables the USB controller's internal voltage regulator and powers off the
 * controller.
 * 
 */
static inline void USBReg_Disable_USBRegulator(void);
static inline void USBReg_Disable_USBRegulator(void)
{
    UHWCON &= ~(1 << UVREGE);
}


/**
 * @brief Unfreezes the USB clock. 
 * 
 * \note The FRZCLK bit will automatically be set by hardware after a reset. Firmware MUST
 * call this during USB initialization to start the controller's clock.
 * 
 */
static inline void USBReg_Unfreeze_Clock(void);
static inline void USBReg_Unfreeze_Clock(void)
{
    USBCON &= ~(1 << FRZCLK);
}


/**
 * @brief Disables the USB controller's clock. Usually used to reduce power-consumption.
 * 
 * \note The FRZCLK bit will automatically be set by hardware after a reset.
 * 
 */
static inline void USBReg_Freeze_Clock(void);
static inline void USBReg_Freeze_Clock(void)
{
    USBCON |= (1 << FRZCLK);
}


/**
 * @brief Read the Endpoint Number currently being accessed by the CPU.
 * 
 * @return AVR_reg_t: The Endpoint Number currently being accessed by the CPU.
 * 
 */
static inline AVR_reg_t USBReg_Get_Current_Endpoint(void);
static inline AVR_reg_t USBReg_Get_Current_Endpoint(void)
{
    return UENUM;
}


/**
 * @brief Set the Endpoint Number that will be accessed by the CPU.
 * 
 * @param EndpointNum Endpoint Number to set.
 *
 */
static inline void USBReg_Set_Current_Endpoint(AVR_Reg_t EndpointNum);
static inline void USBReg_Set_Current_Endpoint(AVR_Reg_t EndpointNum)
{
    return UENUM = EndpointNum;
}


/**
 * @brief Reads if a valid SETUP token packet was sent to the device. NOTE: Ensure the
 * endpoint number of interest is selected prior to calling this.
 * 
 * @return Boolean: true if there's a valid SETUP token packet in the device's currently
 * selected endpoint buffer. False otherwise.
 *
 */
static inline bool USBReg_Is_Setup_TokenPacket_Received(void);
static inline bool USBReg_Is_Setup_TokenPacket_Received(void)
{
    return ((UEINTX & (1 << RXSTPI)) ? true : false);
}


/**
 * @brief Clears the SETUP packet received flag for the currently selected endpoint. 
 * 
 * \note Ensure you read the contents of the Endpoint bank. Clearing this flag discards 
 * the SETUP token packet currently stored in the selected endpoint's bank.
 * 
 */
static inline void USBReg_Clear_Setup_TokenPacket(void);
static inline void USBReg_Clear_Setup_TokenPacket(void)
{
    UEINTX &= ~(1 << RXSTPI);
}


/**
 * @brief Reads if a valid OUT data packet was sent to the device.
 * 
 * @return Boolean: true if there's a valid OUT data packet in the device's currently
 * selected endpoint buffer. False otherwise.
 * 
 * \note Ensure the endpoint number of interest is selected prior to calling this.
 *
 */
static inline bool USBReg_Is_Out_DataPacket_Received(void);
static inline bool USBReg_Is_Out_DataPacket_Received(void)
{
    return ((UEINTX & (1 << RXOUTI)) ? true : false);
}


/**
 * @brief Clears the OUT data packet received flag for the currently selected endpoint. 
 * 
 * \note Ensure you read the contents of the Endpoint bank. Clearing this flag discards the OUT data packet
 * currently stored in the selected endpoint's bank.
 * 
 */
static inline void USBReg_Clear_Out_DataPacket(void);
static inline void USBReg_Clear_Out_DataPacket(void)
{
    UEINTX &= ~(1 << RXOUTI);
    UEINTX &= ~(1 << FIFOCON); /* RXOUTI must always be cleared before FIFOCON. Pg. 275 ATMega32U4 */
}


/**
 * @brief Reads if the selected endpoint bank is ready to accept a new IN data packet.
 * 
 * @return Boolean: true if the device is ready to receive an IN data packet from the host.
 * False otherwise.
 * 
 * \note Ensure the endpoint number of interest is selected prior to calling this.
 *
 */
static inline bool USBReg_Can_Receive_In_DataPacket(void);
static inline bool USBReg_Can_Receive_In_DataPacket(void)
{
	return ((UEINTX & (1 << TXINI)) ? true : false);
}

/* TODO: */
// /**
//  * @brief 
//  * 
//  */
// static inline void USBReg_Send_In_DataPacket(void);
// static inline void USBReg_Send_In_DataPacket(void)
// {
// 	UEINTX &= ~(1 << TXINI);
// }


/**
 * @brief Reads whether the selected endpoint's bank can be written to or read from.
 * 
 * @return Boolean:
 * For an IN endpoint (sending data to host): Returns true if the current bank 
 * is not full i.e. the firmware can push data into the FIFO. False otherwise.
 * 
 * For an OUT endpoint (receiving data from host): Returns true if the current
 * bank is not empty, i.e. the firmware can read data from the FIFO. False otherwise.
 * 
 * \note Ensure the endpoint number of interest is selected prior to calling this.
 * Do not call if you are using a Control Endpoint (Endpoint 0).
 *  
 */
static inline bool USBReg_Can_ReadWrite_Bank(void);
static inline bool USBReg_Can_ReadWrite_Bank(void)
{
	return ((UEINTX & (1 << RWAL)) ? true : false);
}


#endif /* USBREGISTERS_H */