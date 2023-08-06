/**
 * @file kb_pin_def.h
 * @author Ian Ress
 * @brief Defines the available GPIO Pins on the ATMega16U4 and ATMega32U4 that the user can assign to a Keyboard 
 * Row/Column. See the description of bsp_pin_def.h for more details. Note that it is the user's reponsibility to 
 * ensure a GPIO pin defined here is not used on the Keyboard for an alternate function (SPI, ADC, etc). Only 
 * Programming Pins have guards around them to prevent them from being used.
 * @date 2023-06-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef KB_PIN_DEF_H_
#define KB_PIN_DEF_H_

#define ONLY_INCLUDE_BSP_PIN_DEF_H_IN_KB_PIN_DEF_H_

#include <bsp_pin_def.h>
#include <kb_programming_config.h>



/**
 * @brief Pin PB0 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PB0                              (BSP_PORT_B | BSP_PIN_0)


/**
 * @brief Pin PB1 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PB1     					        (BSP_PORT_B | BSP_PIN_1)


#if ((KB_ENABLE_PDI) == 0)
    /**
     * @brief Pin PB2 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column if PDI 
     * Programming is not used. GPIO Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract 
     * hardware-agnostic GPIO Port and Pin information from this definition. See the description in bsp_pin_def.h 
     * for more details.
     */
    #define KB_PIN_PB2     					        (BSP_PORT_B | BSP_PIN_2)


    /**
     * @brief Pin PB3 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column if PDI 
     * Programming is not used. GPIO Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract 
     * hardware-agnostic GPIO Port and Pin information from this definition. See the description in bsp_pin_def.h 
     * for more details.
     */
    #define KB_PIN_PB3     					        (BSP_PORT_B | BSP_PIN_3)
#endif


/**
 * @brief Pin PB4 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PB4     					        (BSP_PORT_B | BSP_PIN_4)


/**
 * @brief Pin PB5 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PB5     					        (BSP_PORT_B | BSP_PIN_5)


/**
 * @brief Pin PB6 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PB6     					        (BSP_PORT_B | BSP_PIN_6)


/**
 * @brief Pin PB7 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PB7     					        (BSP_PORT_B | BSP_PIN_7)


/**
 * @brief Pin PC6 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PC6     					        (BSP_PORT_C | BSP_PIN_6)


/**
 * @brief Pin PC7 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PC7     					        (BSP_PORT_C | BSP_PIN_7)


/**
 * @brief Pin PD0 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PD0     					        (BSP_PORT_D | BSP_PIN_0)


/**
 * @brief Pin PD1 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PD1     					        (BSP_PORT_D | BSP_PIN_1)


/**
 * @brief Pin PD2 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PD2     					        (BSP_PORT_D | BSP_PIN_2)


/**
 * @brief Pin PD3 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PD3     					        (BSP_PORT_D | BSP_PIN_3)


/**
 * @brief Pin PD4 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PD4     					        (BSP_PORT_D | BSP_PIN_4)


/**
 * @brief Pin PD5 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PD5     					        (BSP_PORT_D | BSP_PIN_5)


/**
 * @brief Pin PD6 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PD6     					        (BSP_PORT_D | BSP_PIN_6)


/**
 * @brief Pin PD7 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PD7     					        (BSP_PORT_D | BSP_PIN_7)


/**
 * @brief Pin PE2 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PE2     					        (BSP_PORT_E | BSP_PIN_2)


/**
 * @brief Pin PE6 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PE6     					        (BSP_PORT_E | BSP_PIN_6)


/**
 * @brief Pin PF0 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PF0     					        (BSP_PORT_F | BSP_PIN_0)


/**
 * @brief Pin PF1 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column. GPIO 
 * Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract hardware-agnostic GPIO Port 
 * and Pin information from this definition. See the description in bsp_pin_def.h for more details.
 */
#define KB_PIN_PF1     					        (BSP_PORT_F | BSP_PIN_1)


#if ((KB_ENABLE_JTAG) == 0)
    /**
     * @brief Pin PF4 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column if 
     * JTAG is not used. GPIO Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract 
     * hardware-agnostic GPIO Port and Pin information from this definition. See the description in 
     * bsp_pin_def.h for more details.
     */
    #define KB_PIN_PF4     					        (BSP_PORT_F | BSP_PIN_4)


    /**
     * @brief Pin PF5 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column if 
     * JTAG is not used. GPIO Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract 
     * hardware-agnostic GPIO Port and Pin information from this definition. See the description in 
     * bsp_pin_def.h for more details.
     */
    #define KB_PIN_PF5     					        (BSP_PORT_F | BSP_PIN_5)


    /**
     * @brief Pin PF6 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column if 
     * JTAG is not used. GPIO Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract 
     * hardware-agnostic GPIO Port and Pin information from this definition. See the description in 
     * bsp_pin_def.h for more details.
     */
    #define KB_PIN_PF6     					        (BSP_PORT_F | BSP_PIN_6)


    /**
     * @brief Pin PF7 on ATMega16U4 and ATMega32U4 which can be assigned to a Keyboard Row/Column if 
     * JTAG is not used. GPIO Drivers can use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract 
     * hardware-agnostic GPIO Port and Pin information from this definition. See the description in 
     * bsp_pin_def.h for more details.
     */
    #define KB_PIN_PF7     					        (BSP_PORT_F | BSP_PIN_7)
#endif



/*--------------------------------------------------------------------------------------------------------------------------*/
/*------------ AT THE END OF KB_PIN_DEF.H UNDEFINE UNUSED BSP_PORT_x AND BSP_PIN_xx VALUES FOUND IN BSP_PIN_DEF.H ----------*/
/*--- ENSURES UNUSED DEFINITIONS ARE NOT USED IN THE APPLICATION. UNFORTUNATELY THE USED BSP DEFINITIONS HAVE TO REMAIN. ---*/
/*------------------------ IT IS THE PROGRAMMER'S RESPONSIBILITY TO NOT USE THESE IN THE APPLICATION. ----------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/

#warning "TODO: Is there a way to hide the used BSP_PIN_xx and BSP_PORT_x from the Application as well without \
writing BSP_PIN_PA0 ((0U << 8) | 0U), BSP_PIN_PA1 ((0U << 8) | 1),... definitions in bsp_pin_def.h? Hard-writing \
definitions like above would work but would require like 900 defines... and you would have to undef all unused ones."
// #undef BSP_PIN_0
// #undef BSP_PIN_1
// #undef BSP_PIN_2
// #undef BSP_PIN_3
// #undef BSP_PIN_4
// #undef BSP_PIN_5
// #undef BSP_PIN_6
// #undef BSP_PIN_7
#undef BSP_PIN_8
#undef BSP_PIN_9
#undef BSP_PIN_10
#undef BSP_PIN_11
#undef BSP_PIN_12
#undef BSP_PIN_13
#undef BSP_PIN_14
#undef BSP_PIN_15
#undef BSP_PIN_16
#undef BSP_PIN_17
#undef BSP_PIN_18
#undef BSP_PIN_19
#undef BSP_PIN_20
#undef BSP_PIN_21
#undef BSP_PIN_22
#undef BSP_PIN_23
#undef BSP_PIN_24
#undef BSP_PIN_25
#undef BSP_PIN_26
#undef BSP_PIN_27
#undef BSP_PIN_28
#undef BSP_PIN_29
#undef BSP_PIN_30
#undef BSP_PIN_31
#undef BSP_PIN_32

#undef BSP_PORT_A
// #undef BSP_PORT_B
// #undef BSP_PORT_C
// #undef BSP_PORT_D
// #undef BSP_PORT_E
// #undef BSP_PORT_F
#undef BSP_PORT_G
#undef BSP_PORT_H
#undef BSP_PORT_I
#undef BSP_PORT_J
#undef BSP_PORT_K
#undef BSP_PORT_L
#undef BSP_PORT_M
#undef BSP_PORT_N
#undef BSP_PORT_O
#undef BSP_PORT_P
#undef BSP_PORT_Q
#undef BSP_PORT_R
#undef BSP_PORT_S
#undef BSP_PORT_T
#undef BSP_PORT_U
#undef BSP_PORT_V
#undef BSP_PORT_W
#undef BSP_PORT_X
#undef BSP_PORT_Y
#undef BSP_PORT_Z

/* Prevent bsp_pin_def.h from being able to be directly included after including kb_pin_def.h */
#undef ONLY_INCLUDE_BSP_PIN_DEF_H_IN_KB_PIN_DEF_H_ 

#endif /* BSP_PIN_DEF_H_ */
