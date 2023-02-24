/**
 * @file USBRegisters.h
 * @author Ian Ress
 * \brief Direct manipulation of the USB controller's registers. These registers will change depending
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


typedef enum
{
    ENDPOINT_DIR_OUT,
    ENDPOINT_DIR_IN
} endpoint_direction_t;


/* Only valid endpoint types for HID is Control and Interrupt*/
typedef enum
{
    ENDPOINT_CONTROL,
    // ENDPOINT_ISOCHRONOUS
    // ENDPOINT_BULK,
    ENDPOINT_INTERRUPT
} endpoint_type_t;

typedef enum
{
    ENDPOINT_SINGLE_BANK,
    ENDPOINT_DOUBLE_BANK
} endpoint_bank_t;

typedef enum
{
    ENDPOINT_BYTES_8,
    ENDPOINT_BYTES_16,
    ENDPOINT_BYTES_32,
    ENDPOINT_BYTES_64,
    ENDPOINT_BYTES_128,
    ENDPOINT_BYTES_256,
    ENDPOINT_BYTES_512
} endpoint_size_t;




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
// static inline void          USBReg_Enable_USB_Controller(void)                                      GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Void_Return);
// static inline void          USBReg_Reset_USB_Controller(void)                                       GCCATTRIBUTE_WEAK_ALIAS(USBReg_Void_Param_Void_Return);
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


// static inline void USBReg_Is_CPU_Clock_ExternalOsc();

/* USB Controller Enabling and Disabling */
static inline void USBReg_Enable_USB_Controller(void);
static inline void USBReg_Reset_USB_Controller(void);
static inline void USBReg_USB_Attach(void);
static inline void USBReg_USB_Detach(void);
static inline void USBReg_Unfreeze_Clock(void);
static inline void USBReg_Freeze_Clock(void);

/* USB Power */
static inline void USBReg_Enable_VBus(void);
static inline void USBReg_Disable_VBus(void);
static inline void USBReg_Enable_USBRegulator(void);
static inline void USBReg_Disable_USBRegulator(void);

/* USB Controller PLL and Clock Setup */
static inline void USBReg_Set_CPU_Clock_ExternalOsc(void);
static inline void USBReg_Set_CPU_Clock_InternalOsc(void);
static inline void USBReg_Enable_InternalOsc(void);
static inline void USBReg_Disable_InternalOsc(void);
static inline bool USBReg_Is_InternalOsc_Ready(void);
static inline void USBReg_Enable_ExternalOsc(void);
static inline void USBReg_Disable_ExternalOsc(void);
static inline bool USBReg_Is_ExternalOsc_Ready(void);
static inline void USBReg_PLL_Set_Prescalar(void);
static inline void USBReg_PLL_Select_ExternalOsc(void);
static inline void USBReg_PLL_Select_InternalOsc(void);
static inline void USBReg_PLL_Set_Postscalar(void);
static inline void USBReg_PLL_Enable(void);
static inline void USBReg_PLL_Disable(void);
static inline bool USBReg_Is_PLL_Ready(void);

/* USB Endpoint Selection */
static inline AVR_reg_t USBReg_Get_Current_Endpoint(void);
static inline void USBReg_Set_Current_Endpoint(AVR_reg_t var);

/* USB Endpoint Configuration */
static inline void USBReg_Set_Low_Speed(void);
static inline void USBReg_Set_Full_Speed(void);
static inline void USBReg_Enable_Endpoint(void);
static inline void USBReg_Disable_Endpoint(void);
static inline void USBReg_Allocate_Endpoint_Memory(void);
static inline void USBReg_Deallocate_Endpoint_Memory(void);
static inline void USBReg_Reset_Endpoint_Configuration(void);
static inline void USBReg_Set_Endpoint_Direction(endpoint_direction_t var);
static inline void USBReg_Set_Endpoint_Type(endpoint_type_t var);
static inline void USBReg_Set_Number_Of_Banks(endpoint_bank_t var);
static inline void USBReg_Set_Endpoint_Size(endpoint_size_t var);
static inline void USBReg_Disable_All_Endpoint_Interrupts(void);
static inline bool USBReg_Is_Endpoint_Configured(void);

/* USB Endpoint Run-Time */
static inline bool USBReg_Is_Setup_TokenPacket_Received(void);
static inline void USBReg_Clear_Setup_TokenPacket(void);
static inline bool USBReg_Is_Out_DataPacket_Received(void);
static inline void USBReg_Clear_Out_DataPacket(void);
static inline bool USBReg_Can_Receive_In_DataPacket(void);
static inline void USBReg_Send_In_DataPacket(void);
static inline bool USBReg_Can_ReadWrite_Bank(void);


/* TODO: MUST SET CLKS BIT TO SELECT WHICH CLOCK TO USE */
#if defined(AVR_DEVICE_FAMILY1)
    /**
     * \brief Enables the USB controller.
     * 
     * \note This MUST be called to start the USB controller.
     * 
     */
    static inline void USBReg_Enable_USB_Controller(void)
    {
        USBCON |= (1 << USBE);
    }


    /**
     * \brief Resets the USB controller.
     * 
     */
    static inline void USBReg_Reset_USB_Controller(void)
    {
        USBCON &= ~(1 << USBE);
    }


    /**
     * \brief Connects the D+/D- pullups to VBUS, thus attaching
     * the USB controller to the bus.
     * 
     * \note This MUST be called to start the USB controller.
     * 
     */
    static inline void USBReg_USB_Attach(void)
    {
        UDCON &= ~(1 << DETACH);
    }


    /**
     * \brief Disconnects VBUS from the D+/D- pullups, thus
     * resetting the USB controller.
     * 
     */
    static inline void USBReg_USB_Detach(void)
    {
        UDCON |= (1 << DETACH);
    }


    /**
     * \brief Unfreezes the USB clock. 
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
     * \brief Disables the USB controller's clock. Usually used to reduce power-consumption.
     * 
     * \note The FRZCLK bit will automatically be set by hardware after a reset.
     * 
     */
    static inline void USBReg_Freeze_Clock(void)
    {
        USBCON |= (1 << FRZCLK);
    }


    /**
     * \brief Enables the VBUS pad connected to the USB controller.
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
     * \brief Disables the VBUS pad connected to the USB controller.
     * 
     */
    static inline void USBReg_Disable_VBus(void)
    {
        USBCON &= ~(1 << OTGPADE);
    }


    /**
     * \brief Enables the USB controller's internal voltage regulator.
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
     * \brief Disables the USB controller's internal voltage regulator and powers off the
     * controller.
     * 
     */
    static inline void USBReg_Disable_USBRegulator(void)
    {
        UHWCON &= ~(1 << UVREGE);
    }


    /**
     * \brief Sets the External Oscillator as the CPU clock.
     * 
     * \warning Before calling this function, you must first enable the
     * External Oscillator then ensure it is operating properly. This can
     * be done by calling \p USBReg_Enable_ExternalOsc() then polling
     * \p USBReg_Is_ExternalOsc_Ready() until it returns true.
     * 
     */
    static inline void USBReg_Set_CPU_Clock_ExternalOsc(void)
    {
        CLKSEL0 |= (1 << CLKS);
    }


    /**
     * \brief Sets the Internal Oscillator as the CPU clock.
     * 
     * \warning Before calling this function, you must first enable the
     * External Oscillator then ensure it is operating properly. This can
     * be done by calling \p USBReg_Enable_InternalOsc() then polling
     * \p USBReg_Is_InternalOsc_Ready() until it returns true.
     * 
     */
    static inline void USBReg_Set_CPU_Clock_InternalOsc(void)
    {
        CLKSEL0 &= ~(1 << CLKS);
    }


    /**
     * \brief Enables the Internal RC Oscillator.
     * 
     * \warning By default, AVR_DEVICE_FAMILY1 devices calibrate the internal 
     * RC oscillator to 8MHz on reset. This value is not changed because an
     * 8MHz input must be fed into the PLL for the USB controller. Do not
     * set the OSCCAL register to change this calibration value.
     * 
     */
    static inline void USBReg_Enable_InternalOsc(void)
    {
        CLKSEL0 |= (1 << RCE);
    }


    /**
     * \brief Disables the Internal RC Oscillator.
     * 
     */
    static inline void USBReg_Disable_InternalOsc(void)
    {
        CLKSEL0 &= ~(1 << RCE);
    }


    /**
     * \brief Polls Clock status register to see if the Internal RC Oscillator
     * is running.
     * 
     * \return true if the Internal RC Oscillator is running. False otherwise.
     * 
     * \note For this to return true you must first enable the Internal RC
     * Oscillator by calling USBReg_Enable_InternalOsc().
     * 
     */
    static inline bool USBReg_Is_InternalOsc_Ready(void)
    {
        return ((CLKSTA & (1 << RCON)) ? true : false);
    }


    /**
     * \brief Enables the External Oscillator.
     * 
     * \warning AVR_DEVICE_FAMILY1 devices support a maximum clock frequency
     * of 16MHz. This is under the assumption the device is powered with 5V
     * (from VBUS for keyboard). If the device is powered with a lower voltage,
     * this maximum frequency will be even lower. See ATMega32U4 datasheet,
     * Section 29-4, Table 29-1.
     * 
     */
    static inline void USBReg_Enable_ExternalOsc(void)
    {
        CLKSEL0 |= (1 << EXTE);   
    }


    /**
     * \brief Disables the External Oscillator.
     * 
     */
    static inline void USBReg_Disable_ExternalOsc(void)
    {
        CLKSEL0 &= ~(1 << EXTE);
    }


    /**
     * \brief Polls Clock status register to see if the External Oscillator
     * is running.
     * 
     * \return true if the External Oscillator is running. False otherwise.
     * 
     * \note For this to return true you must first enable the External
     * Oscillator by calling USBReg_Enable_ExternalOsc().
     * 
     */
    static inline bool USBReg_Is_ExternalOsc_Ready(void)
    {
        return ((CLKSTA & (1 << EXTON)) ? true : false);
    }


    /**
     * \brief Sets the PLL prescalar so the input clock to the PLL is
     * 8MHz. 
     * 
     * \note Based on user configurations in USBConfig.h, this function
     * will determine at compile-time what to set the PLL prescalar to.
     * 
     */
    static inline void USBReg_PLL_Set_Prescalar(void)
    {
        #if (defined(USB_USE_EXTERNAL_OSCILLATOR) && (USB_EXTERNAL_CLOCK_FREQUENCY == 16000000))
            PLLFRQ |= (1 << PINDIV);
        #else /* Using Internal Oscillator or 8MHz External Oscillator.*/
            PLLFRQ &= ~(1 << PINDIV);
        #endif
    }


    /**
     * \brief Selects the External Oscillator to go into the PLL.
     * 
     * \warning If this is selected, the user must ensure that the External
     * Oscillator is prescaled down to 8MHz BEFORE calling this function.
     * This must be done by using the PLL prescalar and NOT the system 
     * clock prescalar by calling the USBReg_PLL_Set_Prescalar() function.
     * 
     */
    static inline void USBReg_PLL_Select_ExternalOsc(void)
    {
        PLLFRQ &= ~(1 << PINMUX);
    }


    /**
     * \brief Selects the Internal RC Oscillator to go into the PLL.
     * 
     */
    static inline void USBReg_PLL_Select_InternalOsc(void)
    {
        PLLFRQ |= (1 << PINMUX);
    }


    /**
     * \brief Sets the PLL Postscalar to output a 48MHz clock into the USB
     * controller.
     * 
     * \warning This assumes the input clock to the PLL is correctly prescaled
     * to 8MHz.
     * 
     */
    static inline void USBReg_PLL_Set_Postscalar(void)
    {
        PLLFRQ |= (1 << PDIV2);
    }


    /**
     * \brief Enables the PLL.
     * 
     */
    static inline void USBReg_PLL_Enable(void)
    {
        PLLSCR |= (1 << PLLE);
    }


    /**
     * \brief Disables the PLL.
     * 
     */
    static inline void USBReg_PLL_Disable(void)
    {
        PLLSCR &= ~(1 << PLLE);
    }


    /**
     * \brief Checks if PLL is locked to the reference clock, and ready for operation.
     * After the PLL is enabled, it takes about several ms for the PLL to lock.
     * 
     * \return true If the PLL is ready, false otherwise.
     * 
     * \warning Before doing any task that depends on the PLL, you should first
     * verify that the PLL is locked.
     *
     */
    static inline bool USBReg_Is_PLL_Ready(void)
    {
        return ((PLLSCR & (1 << PLOCK)) ? true : false);
    }


    /**
     * \brief Read the Endpoint Number currently being accessed by the CPU.
     * 
     * \return AVR_reg_t: The Endpoint Number currently being accessed by the CPU.
     * 
     */
    static inline AVR_reg_t USBReg_Get_Current_Endpoint(void)
    {
        return UENUM;
    }


    /**
     * \brief Set the Endpoint Number that will be accessed by the CPU.
     * 
     * \param var Endpoint Number to set, starting at 0.
     * 
     * \warning \p AVR_DEVICE_FAMILY1 devices have 7 endpoints, so \p var 
     * must be less than 7.
     *
     */
    static inline void USBReg_Set_Current_Endpoint(AVR_reg_t var)
    {
        if (var < 0b111)
        {
            UENUM = var;
        }  
    }


    /**
     * \brief Connects the USB Controller's internal pullup resistor to the D- line.
     * 
     */
    static inline void USBReg_Set_Low_Speed(void)
    {
        UDCON |= (1 << LSM);
    }


    /**
     * \brief Connects the USB Controller's internal pullup resistor to the D+ line.
     * 
     */
    static inline void USBReg_Set_Full_Speed(void)
    {
        UDCON &= ~(1 << LSM);
    }


    /**
     * \brief Activates the endpoint. This must be called to use the endpoint.  
     * 
     * \note Ensure the endpoint number of interest is selected prior to calling this.
     * 
     */
    static inline void USBReg_Enable_Endpoint(void)
    {
        UECONX |= (1 << EPEN);
    }


    /**
     * \brief Disables the endpoint.
     * 
     * \note Ensure the endpoint number of interest is selected prior to calling this.
     * 
     * \note Disabling the endpoint does not clear it's memory bank from DPRAM. You must
     * call USBReg_Deallocate_Endpoint_Memory() to free up memory in the DPRAM.
     * 
     */
    static inline void USBReg_Disable_Endpoint(void)
    {
        UECONX &= ~(1 << EPEN);
    }


    /**
     * \brief Allocates the selected endpoint's memory bank into DPRAM.
     * 
     * \warning See Section 21.9 Memory Management of ATMega32U4 datasheet.
     * Memory in DPRAM containing other endpoint banks may be corrupted 
     * depending on which endpoint is deallocated.
     * 
     * \note You must specify the endpoint bank's size before allocating
     * memory.
     * 
     * \note Ensure the endpoint number of interest is selected prior to calling this.
     * 
     */
    static inline void USBReg_Allocate_Endpoint_Memory(void)
    {
        UECFG1X |= (1 << ALLOC);
    }


    /**
     * \brief Removes the selected endpoint's memory bank from DPRAM.
     * 
     * \warning See Section 21.9 Memory Management of ATMega32U4 datasheet.
     * Memory in DPRAM containing other endpoint banks may be corrupted 
     * depending on which endpoint is deallocated.
     * 
     * \note Ensure the endpoint number of interest is selected prior to calling this.
     * 
     */
    static inline void USBReg_Deallocate_Endpoint_Memory(void)
    {
        UECFG1X &= ~(1 << ALLOC);
    }


    /**
     * \brief Clears all of the endpoint's configuration settings and restores
     * them to the default values.
     * 
     * \note Ensure the endpoint number of interest is selected prior to calling this.
     * 
     */
    static inline void USBReg_Reset_Endpoint_Configuration(void)
    {
        UECFG0X = 0;
        UECFG1X = 0;
    }


    /**
     * \brief Call to configure either the IN or OUT bank of the selected
     * endpoint.
     * 
     * \param var Either ENDPOINT_DIR_IN or ENDPOINT_DIR_OUT.
     * 
     * \note Ensure the endpoint number of interest is selected prior to calling this.
     * 
     * \note This must also be called before configuring the endpoint type (Control, Bulk,
     * Interrupt, etc.)
     * 
     */
    static inline void USBReg_Set_Endpoint_Direction(endpoint_direction_t var)
    {
        UECFG0X &= ~(1 << EPDIR);
        if (var == ENDPOINT_DIR_IN)
        {
            UECFG0X |= (1 << EPDIR);
        }
    }


    /**
     * \brief Set the endpoint type.
     * 
     * \param var Either ENDPOINT_CONTROL, ENDPOINT_ISOCHRONOUS,
     * ENDPOINT_BULK, or ENDPOINT_INTERRUPT.
     * 
     * \note Ensure the endpoint number of interest is selected prior to calling this.
     * 
     */
    static inline void USBReg_Set_Endpoint_Type(endpoint_type_t var)
    {
        UECFG0X &= ~(0b11 << EPTYPE0);
        if (var == ENDPOINT_INTERRUPT)
        {
            UECFG0X |= (0b11 << EPTYPE0);
        }
    }


    /**
     * \brief Set the endpoint to either a single or double bank.
     * 
     * \param var Input 0 for a single bank or 1 for a double-banked endpoint.
     * 
     * \note Ensure the endpoint number of interest is selected prior to calling this.
     * 
     */
    static inline void USBReg_Set_Number_Of_Banks(endpoint_bank_t var)
    {
        UECFG1X &= ~(0b11 << EPBK0);
        UECFG1X |= ((0b11 & var) << EPBK0);
    }


    /**
     * \brief Sets the endpoint bank's size.
     * 
     * \param var Can be ENDPOINT_BYTES_8 to ENDPOINT_BYTES_512.
     * 
     * \note Ensure the endpoint number of interest is selected prior to calling this.
     * 
     */
    static inline void USBReg_Set_Endpoint_Size(endpoint_size_t var)
    {
        UECFG1X &= ~(0b111 << EPSIZE0);
        switch (var)
        {
            case ENDPOINT_BYTES_8:
                break;

            case ENDPOINT_BYTES_16:
                UECFG1X |= (0b001 << EPSIZE0);
                break;

            case ENDPOINT_BYTES_32:
                UECFG1X |= (0b010 << EPSIZE0);
                break;

            case ENDPOINT_BYTES_64:
                UECFG1X |= (0b110 << EPSIZE0);
                break;

            case ENDPOINT_BYTES_128:
                UECFG1X |= (0b100 << EPSIZE0);
                break;

            case ENDPOINT_BYTES_256:
                UECFG1X |= (0b101 << EPSIZE0);
                break;

            case ENDPOINT_BYTES_512:
                UECFG1X |= (0b111 << EPSIZE0);
                break;

            default:
                break;
        }
    }


    /**
     * \brief Disables all of the endpoint's interrupt flags.
     * 
     * \note Ensure the endpoint number of interest is selected prior to calling this.
     * 
     */
    static inline void USBReg_Disable_All_Endpoint_Interrupts(void)
    {
        UEIENX = 0;
    }


    /**
     * \brief Determines if the endpoint's size and banks are configured
     * correctly. This is compared against the target MCU's max FIFO size and
     * possible bank configurations. 
     * 
     * \return true if properly configured. False otherwise
     * 
     * \note This only checks for the endpoint's size and bank configuration.
     * This will return true even if memory allocation of the endpoint's
     * bank caused memory corruption in the DPRAM.
     *
     */
    static inline bool USBReg_Is_Endpoint_Configured(void)
    {
        return ((UESTA0X & (1 << CFGOK)) ? true : false);
    }



    /**
     * \brief Reads if a valid SETUP token packet was sent to the device.
     * 
     * \return Boolean: true if there's a valid SETUP token packet in the device's currently
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
     * \brief Clears the SETUP packet received flag for the currently selected endpoint. 
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
     * \brief Reads if a valid OUT data packet was sent to the device.
     * 
     * \return Boolean: true if there's a valid OUT data packet in the device's currently
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
     * \brief Clears the OUT data packet received flag for the currently selected endpoint. 
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
     * \brief Reads if the selected endpoint bank is ready to accept a new IN data packet.
     * 
     * \return Boolean: true if the device is ready to receive an IN data packet from the host.
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
    //  * \brief 
    //  * 
    //  */
    // static inline void USBReg_Send_In_DataPacket(void)
    // {
    // 	UEINTX &= ~(1 << TXINI);
    // }


    /**
     * \brief Reads whether the selected endpoint's bank can be written to or read from.
     * 
     * \return Boolean:
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