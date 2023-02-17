/**
 * @file USBRegisters.h
 * @author Ian Ress
 * @brief Direct manipulation of the USB controller's registers. These registers will change depending
 * on the target device, so all device-specific code relating to this is contained within this file.
 * The capabilities of the USB controller will also be different depending on the target. For example, some
 * controllers may not have an internal regulator. A master list of all inlined register manipulations
 * is first declared with the weak attribute and provided with an empty definition. If the target device does
 * not use a certain capability, it will replace the inlined function call with nothing. Otherwise, 
 * the empty definition will be overwritten and inlined accordingly. This way we don't have to alter 
 * the Common USB Stack's code when using these function calls. Should only be included in USB.c
 * to limit code size.
 * @date 2023-02-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef USBREGISTERS_H
#define USBREGISTERS_H

#include <avr/io.h>
#include <stdbool.h>
#include "Attributes.h"
#include "DeviceSpecific.h"
#include "USBConfig.h"

/* Alias targets. */
// static inline void USBReg_Void_Param_Void_Return(void);
// static inline void USBReg_Void_Param_Void_Return(void) {}

// static inline bool USBReg_Void_Param_Bool_Return(void);
// static inline bool USBReg_Void_Param_Bool_Return(void)
// {
//     /* TODO: Return value? */
// }

// static inline void USBReg_AVRRegt_Param_Void_Return(AVR_reg_t var);
// static inline void USBReg_AVRRegt_Param_Void_Return(AVR_reg_t var) {}

// static inline AVR_reg_t USBReg_Void_Param_AVRRegt_Return(void);
// static inline AVR_reg_t USBReg_Void_Param_AVRRegt_Return(void)
// {
//     /* TODO: Return value? */
// }

// static inline AVR_reg_t USBReg_AVRRegt_Param_AVRRegt_Return(AVR_reg_t var);
// static inline AVR_reg_t USBReg_AVRRegt_Param_AVRRegt_Return(AVR_reg_t var)
// {
//     /* TODO: Return value? */
// }


/* List of all supported register manipulations */
/* TODO: Setting up so all of these functions must be defined for each AVR device family for debugging. Afterwards figure out which ones
can have a weak alias attribute and which ones must be required for all AVR devices. */
// static inline void          Set_System_Clock_Freq(uint8_t freqMHz);
// static inline void          Use_InternalRC_System_Clock(void)                           GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Void_Return);
// static inline void          Use_ExternalOsc_System_Clock(void)                          GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Void_Return);
// static inline bool          Is_ExternalOsc_Enabled(void)                                GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Bool_Return);
// static inline void          USBReg_EnableUSB(void)                                      GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Void_Return);
// static inline void          USBReg_ResetUSB(void)                                       GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Void_Return);
// static inline void          USBReg_Enable_VBus(void)                                    GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Void_Return);
// static inline void          USBReg_Disable_VBus(void)                                   GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Void_Return);
// static inline void          USBReg_Enable_USBRegulator(void)                            GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Void_Return);
// static inline void          USBReg_Disable_USBRegulator(void)                           GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Void_Return);
// static inline void          USBReg_Unfreeze_Clock(void)                                 GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Void_Return);
// static inline void          USBReg_Freeze_Clock(void)                                   GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Void_Return);
// static inline AVR_reg_t     USBReg_Get_Current_Endpoint(void)                           GCCATTRIBUTE_WEAK_ALIAS(USBReg_AVRRegt_Param_AVRRegt_Return);
// static inline void          USBReg_Set_Current_Endpoint(AVR_reg_t var)                  GCCATTRIBUTE_WEAK_ALIAS(USBReg_AVRRegt_Param_Void_Return);
// static inline bool          USBReg_Is_Setup_TokenPacket_Received(void)                  GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Bool_Return);
// static inline void          USBReg_Clear_Setup_TokenPacket(void)                        GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Void_Return);
// static inline bool          USBReg_Is_Out_DataPacket_Received(void)                     GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Bool_Return);
// static inline void          USBReg_Clear_Out_DataPacket(void)                           GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Void_Return);
// static inline bool          USBReg_Can_Receive_In_DataPacket(void)                      GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Bool_Return);
// static inline void          USBReg_Send_In_DataPacket(void)                             GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Void_Return);
// static inline bool          USBReg_Can_ReadWrite_Bank(void)                             GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Bool_Return);


static inline void Enable_InternalOsc(void);
static inline void Disable_InternalOsc(void);
static inline bool Is_InternalOsc_Ready(void);
static inline void Enable_ExternalOsc(void);
static inline void Disable_ExternalOsc(void);
static inline bool Is_ExternalOsc_Ready(void);
static inline void PLL_Set_Prescalar(void);
static inline void PLL_Select_ExternalOsc(void);
static inline void PLL_Select_InternalOsc(void);
static inline void PLL_Set_Postscalar(void);
static inline void PLL_Enable(void);
static inline void PLL_Disable(void);
static inline bool Is_PLL_Ready(void);
static inline void USBReg_EnableUSB(void);
static inline void USBReg_ResetUSB(void);
static inline void USBReg_Enable_VBus(void);
static inline void USBReg_Disable_VBus(void);
static inline void USBReg_Enable_USBRegulator(void);
static inline void USBReg_Disable_USBRegulator(void);
static inline void USBReg_Unfreeze_Clock(void);
static inline void USBReg_Freeze_Clock(void);
static inline AVR_reg_t USBReg_Get_Current_Endpoint(void);
static inline void USBReg_Set_Current_Endpoint(AVR_reg_t var);
static inline bool USBReg_Is_Setup_TokenPacket_Received(void);
static inline void USBReg_Clear_Setup_TokenPacket(void);
static inline bool USBReg_Is_Out_DataPacket_Received(void);
static inline void USBReg_Clear_Out_DataPacket(void);
static inline bool USBReg_Can_Receive_In_DataPacket(void);
static inline void USBReg_Send_In_DataPacket(void);
static inline bool USBReg_Can_ReadWrite_Bank(void);


#if defined(AVR_DEVICE_FAMILY1)
/* Comes with prescalar of 8 programmed in fuse bits. */
    /**
     * @brief Enables the Internal RC Oscillator.
     * 
     * \warning By default, AVR_DEVICE_FAMILY1 devices calibrate the internal 
     * RC oscillator to 8MHz on reset. This value is not changed because an
     * 8MHz input must be fed into the PLL for the USB controller. Do not
     * set the OSCCAL register to change this calibration value.
     * 
     */
    static inline void Enable_InternalOsc(void)
    {
        CLKSEL0 |= (1 << RCE);
    }


    /**
     * @brief Disables the Internal RC Oscillator.
     * 
     */
    static inline void Disable_InternalOsc(void)
    {
        CLKSEL0 &= ~(1 << RCE);
    }


    /**
     * @brief Polls Clock status register to see if the Internal RC Oscillator
     * is running.
     * 
     * @return true if the Internal RC Oscillator is running. False otherwise.
     * 
     * \note For this to return true you must first enable the Internal RC
     * Oscillator by calling Enable_InternalOsc().
     * 
     */
    static inline bool Is_InternalOsc_Ready(void)
    {
        return ((CLKSTA & (1 << RCON)) ? true : false);
    }


    /**
     * @brief Enables the External Oscillator.
     * 
     * \warning AVR_DEVICE_FAMILY1 devices support a maximum clock frequency
     * of 16MHz. This is under the assumption the device is powered with 5V
     * (from VBUS for keyboard). If the device is powered with a lower voltage,
     * this maximum frequency will be even lower. See ATMega32U4 datasheet,
     * Section 29-4, Table 29-1.
     * 
     */
    static inline void Enable_ExternalOsc(void)
    {
        CLKSEL0 |= (1 << EXTE);   
    }


    /**
     * @brief Disables the External Oscillator.
     * 
     */
    static inline void Disable_ExternalOsc(void)
    {
        CLKSEL0 &= ~(1 << EXTE);
    }


    /**
     * @brief Polls Clock status register to see if the External Oscillator
     * is running.
     * 
     * @return true if the External Oscillator is running. False otherwise.
     * 
     * \note For this to return true you must first enable the External
     * Oscillator by calling Enable_ExternalOsc().
     * 
     */
    static inline bool Is_ExternalOsc_Ready(void)
    {
        return ((CLKSTA & (1 << EXTON)) ? true : false);
    }


    /**
     * @brief Sets the PLL prescalar so the input clock to the PLL is
     * 8MHz. 
     * 
     * \note Based on user configurations in USBConfig.h, this function
     * will determine at compile-time what to set the PLL prescalar to.
     * 
     */
    static inline void PLL_Set_Prescalar(void)
    {
        #if (defined(USB_USE_EXTERNAL_OSCILLATOR) && (USB_EXTERNAL_CLOCK_FREQUENCY == 16000000))
            PLLFRQ |= (1 << PINDIV);
        #else /* Using Internal Oscillator or 8MHz External Oscillator.*/
            PLLFRQ &= ~(1 << PINDIV);
        #endif
    }


    /**
     * @brief Selects the External Oscillator to go into the PLL.
     * 
     * \warning If this is selected, the user must ensure that the External
     * Oscillator is prescaled down to 8MHz BEFORE calling this function.
     * This must be done by using the PLL prescalar and NOT the system 
     * clock prescalar by calling the PLL_Set_Prescalar() function.
     * 
     */
    static inline void PLL_Select_ExternalOsc(void)
    {
        PLLFRQ &= ~(1 << PINMUX);
    }


    /**
     * @brief Selects the Internal RC Oscillator to go into the PLL.
     * 
     */
    static inline void PLL_Select_InternalOsc(void)
    {
        PLLFRQ |= (1 << PINMUX);
    }


    /**
     * @brief Sets the PLL Postscalar to output a 48MHz clock into the USB
     * controller.
     * 
     * \warning This assumes the input clock to the PLL is correctly prescaled
     * to 8MHz.
     * 
     */
    static inline void PLL_Set_Postscalar(void)
    {
        PLLFRQ |= (1 << PDIV2);
    }


    /**
     * @brief Enables the PLL.
     * 
     */
    static inline void PLL_Enable(void)
    {
        PLLSCR |= (1 << PLLE);
    }


    /**
     * @brief Disables the PLL.
     * 
     */
    static inline void PLL_Disable(void)
    {
        PLLSCR &= ~(1 << PLLE);
    }


    /**
     * @brief Checks if PLL is locked to the reference clock, and ready for operation.
     * After the PLL is enabled, it takes about several ms for the PLL to lock.
     * 
     * @return true If the PLL is ready, false otherwise.
     * 
     * \warning Before doing any task that depends on the PLL, you should first
     * verify that the PLL is locked.
     *
     */
    static inline bool Is_PLL_Ready(void)
    {
        return ((PLLSCR & (1 << PLOCK)) ? true : false);
    }


    /**
     * @brief Enables the USB controller.
     * 
     * \note This MUST be called to start the USB controller.
     * 
     */
    static inline void USBReg_EnableUSB(void)
    {
        USBCON |= (1 << USBE);
    }


    /**
     * @brief Resets the USB controller.
     * 
     */
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
    static inline void USBReg_Enable_VBus(void)
    {
        USBCON |= (1 << OTGPADE);
    }


    /**
     * @brief Disables the VBUS pad connected to the USB controller.
     * 
     */
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
     * logic level and if an external voltage regulator is used to power the MCU.
     * 
     */
    static inline void USBReg_Enable_USBRegulator(void)
    {
        UHWCON |= (1 << UVREGE);
    }


    /**
     * @brief Disables the USB controller's internal voltage regulator and powers off the
     * controller.
     * 
     */
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
    static inline AVR_reg_t USBReg_Get_Current_Endpoint(void)
    {
        return UENUM;
    }


    /**
     * @brief Set the Endpoint Number that will be accessed by the CPU.
     * 
     * @param var Endpoint Number to set.
     *
     */
    static inline void USBReg_Set_Current_Endpoint(AVR_reg_t var)
    {
        return UENUM = var;
    }


    /**
     * @brief Reads if a valid SETUP token packet was sent to the device.
     * 
     * @return Boolean: true if there's a valid SETUP token packet in the device's currently
     * selected endpoint buffer. False otherwise.
     * 
     * \note Ensure the endpoint number of interest is selected prior to calling this.
     *
     */
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
    static inline bool USBReg_Can_Receive_In_DataPacket(void)
    {
        return ((UEINTX & (1 << TXINI)) ? true : false);
    }

    /* TODO: */
    // /**
    //  * @brief 
    //  * 
    //  */
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
    static inline bool USBReg_Can_ReadWrite_Bank(void)
    {
        return ((UEINTX & (1 << RWAL)) ? true : false);
    }

#elif defined(AVR_DEVICE_FAMILY3)
    #error "TODO"
#else
    #error "Current target MCU is not currently supported for USB at this time."
#endif


#endif /* USBREGISTERS_H */