/**
 * @file TargetSpecific.h
 * @author Ian Ress
 * @brief USB capabilities, instruction sets, registers, etc will depend on the hardware target
 * being compiled on. This file is used to determine hardware-dependent parameters at compile-time. 
 * The goal is to contain all hardware-specific code within this file and within the MCU-specific 
 * drivers. So if a new device is ever added, only this file and the MCU's basic hardware peripheral 
 * drivers need to be changed. The common USB stack and application code should not have to be altered.
 * 
 * The user must pass the target device name into the -mmcu flag. For example for an ATMega32U4:
 * -mmcu=atmega32u4.
 * @date 2023-04-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef DEVICESPECIFIC_H
#define DEVICESPECIFIC_H

#include <stdint.h>

#if (defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__))
    /**
     * @brief CPU wordsize.
     * 
     */
    typedef uint8_t CPU_RegSize_t;


    /**
     * @brief Target MCU is Little Endian. Leave as a preprocessor define.
     * Do not set this to a value. 
     * 
     * @warning Either CPU_LITTLE_ENDIAN or CPU_BIG_ENDIAN must be defined.
     * If both or none are defined, a compilation error will occur.
     * 
     */
    #define CPU_LITTLE_ENDIAN
    

    /**
     * @brief ATMega16U4 and ATMega32U4 microcontrollers. Targets that are
     * in the same Series are grouped together so they can potentially 
     * share the same code. Leave as a preprocessor define. Do not set this 
     * to a value.
     * 
     * @note Usually the list of microcontrollers within the same Series 
     * will be at the beginning of the datasheet. As a general rule of thumb
     * the main differences between these devices will be the physical 
     * footprint and FLASH/RAM size. However the programmer should be aware
     * of any differences in peripherals, instruction sets, memory map, etc.
     * Also note that any differences in the Memory Mapped I/O will already 
     * be handled in <avr/io.h>
     * 
     */
    #define ATMEGAXXU4_SERIES


    /**
     * @brief Number of General Purpose I/O pins available for use.
     * 
     * @warning A compilation error will occur if this is 0 or less.
     * 
     */
    #define NUMBER_OF_IO_PINS                           26


    /**
     * @brief Most recent USB spec the target MCU's USB Controller supports.
     * This is in BCD format 0xMMnn where MM is the major version and nn is 
     * the minor version. So 0x0200 corresponds to v2.0
     * 
     * @warning A compilation error will occur if this is less than 0x0100 (v1.0)
     * 
     * @attention This is a raw value that has not been typecasted so it
     * can also be used in preprocessor checks in CompileChecks.h.
     * 
     */
    #define CPU_SUPPORTED_USB_VERSION                   0x0200


    /**
     * @brief Number of endpoint addresses INCLUDING Endpoint 0.
     * 
     * @warning A compilation error will occur if this is less than 2.
     * We need at least one Control Endpoint and one Endpoint for data
     * transfer to/from the Host.
     * 
     * @note Each endpoint includes an IN and OUT endpoint. E.g. If 
     * NUMBER_OF_USB_ENDPOINTS is 2, there are 2 IN endpoint banks 
     * and 2 OUT endpoint banks.
     * 
     */
    #define NUMBER_OF_USB_ENDPOINTS                     7


    /**
     * @brief Maximum size, in bytes, that the Endpoint 0 bank can be 
     * programmed to.
     * 
     * @warning A compilation error will occur if this is 0 or less.
     * 
     */
    #define ENDPOINT0_MAX_FIFO_SIZE                     64


    /**
     * @brief Some MCU's have a dedicated peripheral or register that checks
     * the status of the VBUS signal. Note that this is not a GPIO pin.
     * This register/peripheral can be polled to detect when the device is 
     * plugged into the bus. Set to 1 if the target has this feature.
     * Otherwise set to 0.
     * 
     * @warning A compilation error will occur if this is not set to 0 or 1.
     * 
     */
    #define HAS_VBUS_PERIPHERAL                         1


    /**
     * @brief The MCU can be configured as a USB Low Speed Device. Set to 1 
     * if the target supports this feature. Set to 0 if this is unsupported.
     * 
     * @warning A compilation error will occur if this is not set to 0 or 1.
     * 
     * @warning Either CAN_BE_USB_LOW_SPEED_DEVICE, CAN_BE_USB_FULL_SPEED_DEVICE,
     * and/or CAN_BE_USB_HI_SPEED_DEVICE must be set to 1. A compilation error 
     * will occur if none of these are set to 1.
     * 
     */
    #define CAN_BE_USB_LOW_SPEED_DEVICE                 1


    /**
     * @brief The MCU can be configured as a USB Full Speed Device. Set to 1 
     * if the target supports this feature. Set to 0 if this is unsupported.
     * 
     * @warning A compilation error will occur if this is not set to 0 or 1.
     * 
     * @warning Either CAN_BE_USB_LOW_SPEED_DEVICE, CAN_BE_USB_FULL_SPEED_DEVICE,
     * and/or CAN_BE_USB_HI_SPEED_DEVICE must be set to 1. A compilation error 
     * will occur if none of these are set to 1.
     * 
     */
    #define CAN_BE_USB_FULL_SPEED_DEVICE                1


    /**
     * @brief The MCU can be configured as a USB Hi-Speed Device. Set to 1 
     * if the target supports this feature. Set to 0 if this is unsupported.
     * 
     * @warning A compilation error will occur if this is not set to 0 or 1.
     * 
     * @warning Either CAN_BE_USB_LOW_SPEED_DEVICE, CAN_BE_USB_FULL_SPEED_DEVICE,
     * and/or CAN_BE_USB_HI_SPEED_DEVICE must be set to 1. A compilation error 
     * will occur if none of these are set to 1.
     * 
     */
    #define CAN_BE_USB_HI_SPEED_DEVICE                  0


    /**
     * @brief The MCU's USB Controller can be driven using an internal clock. 
     * An external crystal is not needed. Set to 1 if the target supports this 
     * feature. Set to 0 if this is unsupported.
     * 
     * @warning A compilation error will occur if this is not set to 0 or 1.
     * 
     */
    #define CAN_USE_USB_INTERNAL_OSCILLATOR                  1

#elif (defined(__AVR_ATmega8U2__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega32U2__))
    /**
     * @brief CPU wordsize.
     * 
     */
    typedef uint8_t CPU_RegSize_t;


    /**
     * @brief Target MCU is Little Endian. Leave as a preprocessor define.
     * Do not set this to a value. 
     * 
     * @warning Either CPU_LITTLE_ENDIAN or CPU_BIG_ENDIAN must be defined.
     * If both or none are defined, a compilation error will occur.
     * 
     */
    #define CPU_LITTLE_ENDIAN


    /**
     * @brief ATMega8U2, ATMega16U2, and ATMega32U2 microcontrollers. Targets 
     * that are in the same Series are grouped together so they can potentially 
     * share the same code. Leave as a preprocessor define. Do not set this 
     * to a value.
     * 
     * @note Usually the list of microcontrollers within the same Series 
     * will be at the beginning of the datasheet. As a general rule of thumb
     * the main differences between these devices will be the physical 
     * footprint and FLASH/RAM size. However the programmer should be aware
     * of any differences in peripherals, instruction sets, memory map, etc.
     * Also note that any differences in the Memory Mapped I/O will already 
     * be handled in <avr/io.h>
     * 
     */
    #define ATMEGAXXU2_SERIES


    /**
     * @brief Number of General Purpose I/O pins available for use.
     * 
     * @warning A compilation error will occur if this is 0 or less.
     * 
     */
    #define NUMBER_OF_IO_PINS                           22


    /**
     * @brief Most recent USB spec the target MCU's USB Controller supports.
     * This is in BCD format 0xMMnn where MM is the major version and nn is 
     * the minor version. So 0x0200 corresponds to v2.0
     * 
     * @warning A compilation error will occur if this is less than 0x0100 (v1.0)
     * 
     * @attention This is a raw value that has not been typecasted so it
     * can also be used in preprocessor checks in CompileChecks.h.
     * 
     */
    #define CPU_SUPPORTED_USB_VERSION                   0x0200


    /**
     * @brief Number of endpoint addresses INCLUDING Endpoint 0.
     * 
     * @warning A compilation error will occur if this is less than 2.
     * We need at least one Control Endpoint and one Endpoint for data
     * transfer to/from the Host.
     * 
     * @note Each endpoint includes an IN and OUT endpoint. E.g. If 
     * NUMBER_OF_USB_ENDPOINTS is 2, there are 2 IN endpoint banks 
     * and 2 OUT endpoint banks.
     * 
     */
    #define NUMBER_OF_USB_ENDPOINTS                     5


    /**
     * @brief Maximum size, in bytes, that the Endpoint 0 bank can be 
     * programmed to.
     * 
     * @warning A compilation error will occur if this is 0 or less.
     * 
     */
    #define ENDPOINT0_MAX_FIFO_SIZE                     64


    /**
     * @brief Some MCU's have a dedicated peripheral or register that checks
     * the status of the VBUS signal. Note that this is not a GPIO pin.
     * This register/peripheral can be polled to detect when the device is 
     * plugged into the bus. Set to 1 if the target has this feature.
     * Otherwise set to 0.
     * 
     * @warning A compilation error will occur if this is not set to 0 or 1.
     * 
     */
    #define HAS_VBUS_PERIPHERAL                         0


    /**
     * @brief The MCU can be configured as a USB Low Speed Device. Set to 1 
     * if the target supports this feature. Set to 0 if this is unsupported.
     * 
     * @warning A compilation error will occur if this is not set to 0 or 1.
     * 
     * @warning Either CAN_BE_USB_LOW_SPEED_DEVICE, CAN_BE_USB_FULL_SPEED_DEVICE,
     * and/or CAN_BE_USB_HI_SPEED_DEVICE must be set to 1. A compilation error 
     * will occur if none of these are set to 1.
     * 
     */
    #define CAN_BE_USB_LOW_SPEED_DEVICE                 0


    /**
     * @brief The MCU can be configured as a USB Full Speed Device. Set to 1 
     * if the target supports this feature. Set to 0 if this is unsupported.
     * 
     * @warning A compilation error will occur if this is not set to 0 or 1.
     * 
     * @warning Either CAN_BE_USB_LOW_SPEED_DEVICE, CAN_BE_USB_FULL_SPEED_DEVICE,
     * and/or CAN_BE_USB_HI_SPEED_DEVICE must be set to 1. A compilation error 
     * will occur if none of these are set to 1.
     * 
     */
    #define CAN_BE_USB_FULL_SPEED_DEVICE                1


    /**
     * @brief The MCU can be configured as a USB Hi-Speed Device. Set to 1 
     * if the target supports this feature. Set to 0 if this is unsupported.
     * 
     * @warning A compilation error will occur if this is not set to 0 or 1.
     * 
     * @warning Either CAN_BE_USB_LOW_SPEED_DEVICE, CAN_BE_USB_FULL_SPEED_DEVICE,
     * and/or CAN_BE_USB_HI_SPEED_DEVICE must be set to 1. A compilation error 
     * will occur if none of these are set to 1.
     * 
     */
    #define CAN_BE_USB_HI_SPEED_DEVICE                  0


    /**
     * @brief The MCU's USB Controller can be driven using an internal clock. 
     * An external crystal is not needed. Set to 1 if the target supports this 
     * feature. Set to 0 if this is unsupported.
     * 
     * @warning A compilation error will occur if this is not set to 0 or 1.
     * 
     */
    #define CAN_USE_USB_INTERNAL_OSCILLATOR                  0

#elif (defined(__AVR_ATxmega64B3__) || defined(__AVR_ATxmega128B3__))
    /**
     * @brief CPU wordsize. These microcontrollers use a combination of 8 and 
     * 16bit architecture (not sure why...) however wordsize is set to 8-bits 
     * since all Memory Mapped I/O peripherals are 8-bit registers.
     * 
     */
    typedef uint8_t CPU_RegSize_t;


    /**
     * @brief Target MCU is Little Endian. Leave as a preprocessor define.
     * Do not set this to a value. 
     * 
     * @warning Either CPU_LITTLE_ENDIAN or CPU_BIG_ENDIAN must be defined.
     * If both or none are defined, a compilation error will occur.
     * 
     */
    #define CPU_LITTLE_ENDIAN


    /**
     * @brief ATxMega128B3 and ATxMega64B3 microcontrollers. Targets 
     * that are in the same Series are grouped together so they can potentially 
     * share the same code. Leave as a preprocessor define. Do not set this 
     * to a value.
     * 
     * @note Usually the list of microcontrollers within the same Series 
     * will be at the beginning of the datasheet. As a general rule of thumb
     * the main differences between these devices will be the physical 
     * footprint and FLASH/RAM size. However the programmer should be aware
     * of any differences in peripherals, instruction sets, memory map, etc.
     * Also note that any differences in the Memory Mapped I/O will already 
     * be handled in <avr/io.h>
     * 
     */
    #define ATXMEGAXXB3_SERIES


    /**
     * @brief Number of General Purpose I/O pins available for use.
     * 
     * @warning A compilation error will occur if this is 0 or less.
     * 
     */
    #define NUMBER_OF_IO_PINS                           36


    /**
     * @brief Most recent USB spec the target MCU's USB Controller supports.
     * This is in BCD format 0xMMnn where MM is the major version and nn is 
     * the minor version. So 0x0200 corresponds to v2.0
     * 
     * @warning A compilation error will occur if this is less than 0x0100 (v1.0)
     * 
     * @attention This is a raw value that has not been typecasted so it
     * can also be used in preprocessor checks in CompileChecks.h.
     * 
     */
    #define CPU_SUPPORTED_USB_VERSION                   0x0200
    

    /**
     * @brief Number of endpoint addresses INCLUDING Endpoint 0.
     * 
     * @warning A compilation error will occur if this is less than 2.
     * We need at least one Control Endpoint and one Endpoint for data
     * transfer to/from the Host.
     * 
     * @note Each endpoint includes an IN and OUT endpoint. E.g. If 
     * NUMBER_OF_USB_ENDPOINTS is 2, there are 2 IN endpoint banks 
     * and 2 OUT endpoint banks.
     * 
     */
    #define NUMBER_OF_USB_ENDPOINTS                     16


    /**
     * @brief Maximum size, in bytes, that the Endpoint 0 bank can be 
     * programmed to.
     * 
     * @warning A compilation error will occur if this is 0 or less.
     * 
     */
    #define ENDPOINT0_MAX_FIFO_SIZE                     1023


    /**
     * @brief Some MCU's have a dedicated peripheral or register that checks
     * the status of the VBUS signal. Note that this is not a GPIO pin.
     * This register/peripheral can be polled to detect when the device is 
     * plugged into the bus. Set to 1 if the target has this feature.
     * Otherwise set to 0.
     * 
     * @warning A compilation error will occur if this is not set to 0 or 1.
     * 
     */
    #define HAS_VBUS_PERIPHERAL                         0


    /**
     * @brief The MCU can be configured as a USB Low Speed Device. Set to 1 
     * if the target supports this feature. Set to 0 if this is unsupported.
     * 
     * @warning A compilation error will occur if this is not set to 0 or 1.
     * 
     * @warning Either CAN_BE_USB_LOW_SPEED_DEVICE, CAN_BE_USB_FULL_SPEED_DEVICE,
     * and/or CAN_BE_USB_HI_SPEED_DEVICE must be set to 1. A compilation error 
     * will occur if none of these are set to 1.
     * 
     */
    #define CAN_BE_USB_LOW_SPEED_DEVICE                 1


    /**
     * @brief The MCU can be configured as a USB Full Speed Device. Set to 1 
     * if the target supports this feature. Set to 0 if this is unsupported.
     * 
     * @warning A compilation error will occur if this is not set to 0 or 1.
     * 
     * @warning Either CAN_BE_USB_LOW_SPEED_DEVICE, CAN_BE_USB_FULL_SPEED_DEVICE,
     * and/or CAN_BE_USB_HI_SPEED_DEVICE must be set to 1. A compilation error 
     * will occur if none of these are set to 1.
     * 
     */
    #define CAN_BE_USB_FULL_SPEED_DEVICE                1


    /**
     * @brief The MCU can be configured as a USB Hi-Speed Device. Set to 1 
     * if the target supports this feature. Set to 0 if this is unsupported.
     * 
     * @warning A compilation error will occur if this is not set to 0 or 1.
     * 
     * @warning Either CAN_BE_USB_LOW_SPEED_DEVICE, CAN_BE_USB_FULL_SPEED_DEVICE,
     * and/or CAN_BE_USB_HI_SPEED_DEVICE must be set to 1. A compilation error 
     * will occur if none of these are set to 1.
     * 
     */
    #define CAN_BE_USB_HI_SPEED_DEVICE                  0


    /**
     * @brief The MCU's USB Controller can be driven using an internal clock. 
     * An external crystal is not needed. Set to 1 if the target supports this 
     * feature. Set to 0 if this is unsupported.
     * 
     * @warning A compilation error will occur if this is not set to 0 or 1.
     * 
     */
    #define CAN_USE_USB_INTERNAL_OSCILLATOR                  1

#else
    #error "Selected MCU is currently unsupported or -mmcu flag was not set."
#endif

#endif /* DEVICESPECIFIC_H */
