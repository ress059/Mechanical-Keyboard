/**
 * @file kb_pin_def.h
 * @author Ian Ress
 * @brief All possible Ports, Pin Numbers, and Pin Configurations that apply to all microcontrollers. These definitions are 
 * ORed together to create Keyboard Pins that the user can assign to a Keyboard Row/Column in kb_config.h. These definitions will
 * follow the naming convention BSP_PIN_Pxyyy_INPUT_HIZ, BSP_PIN_Pxyyy_INPUT_PULLUP, BSP_PIN_Pxyyy_INPUT_PULLDOWN, BSP_PIN_Pxyyy_OUTPUT_PUSHPULL, 
 * or BSP_PIN_Pxyyy_OUTPUT_OPENDRAIN where x represents the Port Letter and yyy represents the Pin Number. For example:
 * 
 *          #define BSP_PIN_PA3_INPUT_HIZ               (KB_PORT_A | KB_PIN_3 | KB_INPUT_HIZ)
 * 
 * The result is a Keyboard pin that is represented as a uint16_t Bitmap, where the Least Significant Byte is the Pin Number, the FIRST FIVE 
 * BITS of the Most Significant Byte is the Port Assignment, and the LAST THREE BITS of the Most Significant Byte is the Pin Configuration 
 * (Input HiZ, Input Pullup, Input Pulldown, Output Pushpull, or Output Open-drain). I.e:
 * 
 *        0b 000      00000 | 00000000
 *            |         |        |
 *            |         |        |
 *           Pin      Port   Pin Number
 *          Config          
 *   
 * 
 * These are separately defined for each microcontroller in bsp_pin_def.h since the available pins and configurations depend entirely 
 * on the microcontroller itself. For example for ATMega32U4, BSP_PIN_PB2_INPUT_PULLUP would be (KB_PORT_B | KB_PIN_2 | KB_INPUT_INTERNAL_PULLUP) 
 * but nothing would be defined for BSP_PIN_PB2_INPUT_PULLDOWN since that microcontroller does not support input pulldown
 * configurations. In a similar fashion BSP_PIN_PM3_INPUT_PULLUP wouldn't be defined since PM3 doesn't exist on an ATMega32U4.
 * 
 * This method is used because:
 * 1) A compilation error will occur if the user assigns a pin in kb_config.h that does not exist on their target MCU, or uses a pin configuration 
 * that is not supported by their target MCU. The assigned BSP_PIN_Pxyyy_TYPE pin would be undefined.
 * 
 * 2) This gives the user maximum flexibility to configure every Row/Column pin however they desire.
 * 
 * 3) This allows a GPIO driver for any microcontroller to be easily created. The Bitmap representation provides a standard that any microcontroller 
 * can follow to extract Port, Pin, and configuration information. The BSP_PIN_Pxyyy_TYPE definition would be an input into a GPIO Driver function
 * that would control the Keyboard Row/Column.
 * 
 * @date 2023-06-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef KB_PIN_DEF_H_
#define KB_PIN_DEF_H_

#include <stdint.h>


/*----------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------ MACROS. USE IN GPIO DRIVERS. ----------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/

/**
 * @brief The keyboard pin the user assigns to each Keyboard Row/Column in kb_config.h Currently this is
 * represented as a uint16_t Bitmap but the type is defined here in case this must be changed in the future. 
 * See the File Description above for more details.
 * 
 */
typedef uint16_t KB_PINSIZE_T;

/**
 * @brief Extract the GPIO Pin Number that was assigned to a Keyboard Row/Column in kb_config.h. The user will assign BSP_PIN_Pxyyy_TYPE
 * definition to their Keyboard Row/Column. Valid options are BSP_PIN_Pxyyy_INPUT_HIZ, BSP_PIN_Pxyyy_INPUT_PULLUP, BSP_PIN_Pxyyy_INPUT_PULLDOWN, 
 * BSP_PIN_Pxyyy_OUTPUT_PUSHPULL, or BSP_PIN_Pxyyy_OUTPUT_OPENDRAIN. This is a uint16_t bitmap, with the Least Significant Byte reprsenting 
 * the Pin Number. This will be a decimal value with 0 representing Pin 0, 1 representing Pin 1, 2 representing Pin 2,... and 255 representing 
 * Pin 255.
 * 
 * @attention This is the Pin Number associated with the GPIO port, NOT the Pin Number of the microcontroller's footprint. 
 * 
 * @param BSP_PIN_Pxyyy_TYPE The Pin definition the user assigned to a Keyboard Row/Column in kb_config.h.
 * 
 */
#define KB_GET_PIN(BSP_PIN_Pxyyy_TYPE)                          ((BSP_PIN_Pxyyy_TYPE) & 0x00FFU)


/**
 * @brief Extract the GPIO Port that was assigned to a Keyboard Row/Column in kb_config.h. The user will assign BSP_PIN_Pxyyy_TYPE
 * definition to their Keyboard Row/Column. Valid options are BSP_PIN_Pxyyy_INPUT_HIZ, BSP_PIN_Pxyyy_INPUT_PULLUP, BSP_PIN_Pxyyy_INPUT_PULLDOWN, 
 * BSP_PIN_Pxyyy_OUTPUT_PUSHPULL, or BSP_PIN_Pxyyy_OUTPUT_OPENDRAIN. This is a uint16_t bitmap, with the first FIVE BITS of the Most Significant 
 * Byte representing the Port Information. This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 
 * 25 representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses. The
 * Ports are represented as decimal values starting at 0 in order to make this process easier.
 * 
 * @param BSP_PIN_Pxyyy_TYPE The Pin definition the user assigned to a Keyboard Row/Column in kb_config.h.
 * 
 */
#define KB_GET_PORT(BSP_PIN_Pxyyy_TYPE)                         (((BSP_PIN_Pxyyy_TYPE) & 0x1F00) >> 8U)


/**
 * @brief Extract the Pin Configuration that was assigned to the Keyboard Row/Column in kb_config.h. The user will assign BSP_PIN_Pxyyy_TYPE
 * definition to their Keyboard Row/Column. Valid options are BSP_PIN_Pxyyy_INPUT_HIZ, BSP_PIN_Pxyyy_INPUT_PULLUP, BSP_PIN_Pxyyy_INPUT_PULLDOWN, 
 * BSP_PIN_Pxyyy_OUTPUT_PUSHPULL, or BSP_PIN_Pxyyy_OUTPUT_OPENDRAIN. This is a uint16_t bitmap, with the last THREE BITS of the Most Significant
 * Byte representing the Pin Configuration information. This is a decimal value, with 0 representing Input HiZ, 1 representing Input Pullup,
 * 2 representing Input Pulldown, 3 representing Output Push-pull, and 4 representing Output Open-drain.
 * 
 * @param BSP_PIN_Pxyyy_TYPE The Pin definition the user assigned to a Keyboard Row/Column in kb_config.h.
 * 
 */
#define KB_GET_PIN_TYPE(BSP_PIN_Pxyyy_TYPE)                     ((BSP_PIN_Pxyyy_TYPE) & 0xE000)



/*----------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/
/*----------------------- ALL POSSIBLE MICROCONTROLLER PIN DEFINITIONS. USE IN GPIO DRIVERS. ---------------------*/
/*----------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/

/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_0                                                0U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_1                                                1U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_2                                                2U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_3                                                3U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_4                                                4U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_5                                                5U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_6                                                6U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_7                                                7U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_8                                                8U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_9                                                9U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_10                                               10U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_11                                               11U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_12                                               12U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_13                                               13U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_14                                               14U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_15                                               15U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_16                                               16U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_17                                               17U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_18                                               18U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_19                                               19U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_20                                               20U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_21                                               21U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_22                                               22U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_23                                               23U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_24                                               24U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_25                                               25U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_26                                               26U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_27                                               27U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_28                                               28U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_29                                               29U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_30                                               30U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_31                                               31U


/**
 * @brief ORed with KB_PORT_x to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column. 
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is the Pin Number assigned to the Port, NOT the Pin Number of the microcontroller's footprint.
 * 
 */
#define KB_PIN_32                                               32U



/*----------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/
/*----------------------- ALL POSSIBLE MICROCONTROLLER PORT DEFINITIONS. USE IN GPIO DRIVERS. --------------------*/
/*----------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/

/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_A                                               (0U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_B                                               (1U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_C                                               (2U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_D                                               (3U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_E                                               (4U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_F                                               (5U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_G                                               (6U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_H                                               (7U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_I                                               (8U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_J                                               (9U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_K                                               (10U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_L                                               (11U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_M                                               (12U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_N                                               (13U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_O                                               (14U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_P                                               (15U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_Q                                               (16U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_R                                               (17U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_S                                               (18U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_T                                               (19U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_U                                               (20U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_V                                               (21U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_W                                               (22U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_X                                               (23U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_Y                                               (24U << 8)


/**
 * @brief ORed with KB_PIN_xx to create the full Port-Pin definition that the user assigns to a Keyboard Row/Column.
 * These definitions are created in each microcontroller's GPIO driver header file since the available pins depend
 * on the microcontroller itself. For example for ATMega32U4, KB_PIN_PB2 would be (KB_PORT_B | KB_PIN_2) but nothing
 * would be defined for KB_PIN_PM3 since that pin does not exist. This ensures a compilation error will occur if
 * the user assigns a pin in kb_config.h that does not exist on their target MCU.
 * 
 * @attention Do NOT assign this as a Keyboard Row/Column in kb_config.h. Use the BSP_PIN_Pxx definitions instead.
 * 
 * @note This is a decimal value with 0 representing PORTA, 1 representing PORTB, 2 representing PORTC, ... and 25 
 * representing PORTZ. The GPIO driver is responsible for mapping these values to the relevant Memory Mapped I/O addresses.
 * 
 */
#define KB_PORT_Z                                               (25U << 8)



/*----------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/
/*--------------------- ALL POSSIBLE MICROCONTROLLER PIN CONFIGURATIONS. USE IN GPIO DRIVERS. --------------------*/
/*----------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/


#define KB_INPUT_HIZ                                        (0U << 13)

#define KB_INPUT_INTERNAL_PULLUP                            (1U << 13)

#define KB_INPUT_EXTERNAL_PULLUP                            (2U << 13)

#define KB_PIN_INPUT_INTERNAL_PULLDOWN                          (3U << 13)

#define KB_PIN_INPUT_EXTERNAL_PULLDOWN                          (4U << 13)

#define KB_PIN_OUTPUT_PUSHPULL                                  (5U << 13)

#define KB_PIN_OUTPUT_OPENDRAIN                                 (6U << 13)


#endif /* KB_BSP_H_ */
