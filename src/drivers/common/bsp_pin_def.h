/**
 * @file bsp_pin_def.h
 * @author Ian Ress
 * @brief Helper definitions that each Microcontroller's Board Support Package (kb_pin_def.h) uses to create Keyboard 
 * GPIO Pins that the user can assign to a Keyboard Row/Column. These definitions are represented as a bitmap.
 * 
 *        0b 000        00000             00000000
 *            |           |                   |
 *            |           |                   |
 *        Reserved    BSP_PORT_x          BSP_PIN_xx
 *                   (GPIO Port)      (GPIO Pin Number)
 * 
 * 
 * BSP_PORT_x = All possible GPIO Ports. Supports PortA through PortZ. This value starts at 0 with each increasing 
 * value representing the next Port. I.e. 0 = PORTA, 1 = PORTB, 2 = PORTC,... 25 = PORTZ.
 * 
 * BSP_PIN_xx = GPIO Pin Numbers. This is the pin number assigned to the GPIO Port NOT the footprint pin number. 
 * I.e. BSP_PIN_2 could apply to PA2, PB2, PC2, etc. NOT Footprint Pin #2. Currently supports pin numbers up 
 * to 32 but this has the capacity to support support up to 255 pin numbers if needed.
 * 
 * Each microcontroller's Board Support Package ORs together these definitions to create a Keyboard Pin of type
 * KB_PINSIZE_T. These are separately defined for each microcontroller in their kb_pin_def.h files since the 
 * available GPIO pins are hardware dependent. A pseudocode example of a microcontroller's kb_pin_def.h file 
 * would be:
 * 
 * 
 * ```
 * #define ONLY_INCLUDE_BSP_PIN_DEF_H_IN_KB_PIN_DEF_H_ // Ensure bsp_pin_def.h is only visible in kb_pin_def.h
 * 
 * #include <bsp_pin_def.h>
 * 
 * // Define all GPIO pins the target microcontroller supports
 * #define KB_PIN_PA3                  (BSP_PORT_A | BSP_PIN_3)     // Target Microcontroller has PA3 pin
 * #define KB_PIN_PB5                  (BSP_PORT_B | BSP_PIN_5)     // Target Microcontroller has PB5 pin
 * .....
 * // Undefine unused BSP_PORT_x and BSP_PIN_xx macros so they can't be used in the Application.
 * // Unfortunately the used BSP_PORT_x and BSP_PIN_xx will have to remain visible to the Application.
 * // It is the programmer's responsibility to ensure these are not used in the Application.
 * #undef BSP_PORT_C
 * #undef BSP_PORT_D
 * ...
 * #undef BSP_PIN_0
 * #undef BSP_PIN_1
 * ...
 * // Ensure Application cannot directly include bsp_pin_def.h after including kb_pin_def.h
 * #undef ONLY_INCLUDE_BSP_PIN_DEF_H_IN_KB_PIN_DEF_H_
 * ```
 * 
 * 
 * The Application then uses these KB_PIN_Pxx definitions. This method is used because:
 * 
 * 1) A compilation error will occur if the user assigns a GPIO to their Keyboard Row/Column that is not supported
 * on their target MCU. For example, GPIO PK3 does not exist on an ATMega32U4 microcontroller. When a user assigns
 * KB_PIN_PK3 to their Keyboard and compiles for an ATMega32U4, KB_PIN_PK3 will not be defined - thus causing a
 * compilation error.
 * 
 * 2) This allows a GPIO driver for any microcontroller to be easily created. The Bitmap representation provides a 
 * standard that any microcontroller can follow to extract hardware-agnostic Port and Pin information. GPIO Driver 
 * functions would take in a KB_PINSIZE_T type, use the BSP_GET_PORT() and BSP_GET_PIN() macros to extract Port 
 * and Pin information, and use this to perform writes to the appropriate GPIO Registers.
 * 
 * @version 0.1
 * @date 2023-08-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#if defined(ONLY_INCLUDE_BSP_PIN_DEF_H_IN_KB_PIN_DEF_H_)

    #ifndef BSP_PIN_DEF_H_
    #define BSP_PIN_DEF_H_

    #include <stdint.h>



    /*--------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------------ MACROS. USE IN GPIO DRIVERS. --------------------------------------------*/
    /*--------------------------------------------------------------------------------------------------------------------------*/

    /**
     * @brief The Keyboard Pin Type used in the Application. Currently this is represented as a uint16_t bitmap - see the
     * description of bsp_pin_def.h for more details. This type is defined here in case this must be expanded in the future.
     */
    typedef uint16_t KB_PINSIZE_T;


    /**
     * @brief Extract the GPIO Pin Number from a KB_PIN_Pxx definition. For example BSP_GET_PIN(KB_PIN_PA5) returns 5,
     * BSP_GET_PIN(KB_PIN_PK23) returns 23, BSP_GET_PIN(KB_PIN_PB12) returns 12, etc.
     * 
     * @attention This is the Pin Number associated with the GPIO port, NOT the Pin Number of the microcontroller's 
     * footprint. I.e. If this macro returns 5 this could be PA5, PB5, PC5,... NOT Footprint Pin #5.
     * 
     * @param KB_PIN_Pxx The Keyboard Pin. This is a bitmap of type KB_PINSIZE_T - see the description of bsp_pin_def.h
     * for more details on how this is represented.
     */
    #define BSP_GET_PIN(KB_PIN_Pxx)                                 ((KB_PIN_Pxx) & 0x00FFU)


    /**
     * @brief Extract the GPIO Port from a KB_PIN_Pxx definition. The returned value starts at 0 with each 
     * increasing value representing the next Port. I.e. 0 = PORTA, 1 = PORTB, 2 = PORTC,... 25 = PORTZ. 
     * For example BSP_GET_PORT(KB_PIN_PA5) returns 0, BSP_GET_PORT(KB_PIN_PB21) returns 1, BSP_GET_PORT(KB_PIN_PC5) 
     * returns 2, etc.
     * 
     * @param KB_PIN_Pxx The Keyboard Pin. This is a bitmap of type KB_PINSIZE_T - see the description of bsp_pin_def.h
     * for more details on how this is represented.
     */
    #define BSP_GET_PORT(KB_PIN_Pxx)                                (((KB_PIN_Pxx) & 0x1F00) >> 8U)



    /*--------------------------------------------------------------------------------------------------------------------------*/
    /*------------------ ALL SUPPORTED MICROCONTROLLER PIN DEFINITIONS. THESE ARE THE PIN NUMBERS FOR EACH GPIO PORT -----------*/
    /*--------------------------------------- NOT THE FOOTPRINT PIN NUMBER. USE IN GPIO DRIVERS --------------------------------*/
    /*------------------------- 8 BITS ARE RESERVED FOR THIS SO WE CAN SUPPORT UP TO 255 PINS IN THE FUTURE --------------------*/
    /*--------------------------------------------------------------------------------------------------------------------------*/

    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_0                                               (0U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_1                                               (1U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_2                                               (2U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_3                                               (3U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_4                                               (4U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_5                                               (5U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_6                                               (6U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_7                                               (7U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_8                                               (8U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_9                                               (9U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_10                                              (10U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_11                                              (11U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_12                                              (12U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_13                                              (13U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_14                                              (14U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_15                                              (15U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_16                                              (16U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_17                                              (17U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_18                                              (18U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_19                                              (19U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_20                                              (20U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_21                                              (21U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_22                                              (22U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_23                                              (23U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_24                                              (24U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_25                                              (25U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_26                                              (26U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_27                                              (27U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_28                                              (28U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_29                                              (29U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_30                                              (30U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_31                                              (31U)


    /**
     * @brief ORed with BSP_PORT_x to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. 
     * The result is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This portion is 
     * the Pin Number associated with the GPIO Port. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PIN_32                                              (32U)



    /*--------------------------------------------------------------------------------------------------------------------------*/
    /*----------------------------  ALL POSSIBLE MICROCONTROLLER PORT DEFINITIONS. USE IN GPIO DRIVERS. ------------------------*/
    /*--------------------------------------------------------------------------------------------------------------------------*/

    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_A                                              (0U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_B                                              (1U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_C                                              (2U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_D                                              (3U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_E                                              (4U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_F                                              (5U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_G                                              (6U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_H                                              (7U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_I                                              (8U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_J                                              (9U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_K                                              (10U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_L                                              (11U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_M                                              (12U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_N                                              (13U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_O                                              (14U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_P                                              (15U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_Q                                              (16U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_R                                              (17U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_S                                              (18U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_T                                              (19U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_U                                              (20U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_V                                              (21U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_W                                              (22U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_X                                              (23U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_Y                                              (24U << 8)


    /**
     * @brief ORed with BSP_PIN_xx to create a GPIO Pin Definition that can be assigned to a Keyboard Row/Column. The result 
     * is a bitmap containing the hardware-agnostic GPIO Port and Pin information. This contains the GPIO Port which starts 
     * at 0. Each increasing value represents the next Port. I.e. 0 = PORTA, 1 = PORTB,... 25 = PORTZ. It is the GPIO Driver's 
     * responsibility to map this to the correct Register Addresses. See bsp_pin_def.h description for more details.
     * 
     * @attention Only use this in kb_pin_def.h within each MCU Board Support Package. Do not use in the Application.
     */
    #define BSP_PORT_Z                                              (25U << 8)



    /*--------------------------------------------------------------------------------------------------------------------------*/
    /*----------------------------------- LAST 3 MOST SIGNIFICANT BITS ARE RESERVED FOR FUTURE USE -----------------------------*/
    /*--------------------------------------------------------------------------------------------------------------------------*/
                                                                
    #endif /* BSP_PIN_DEF_H_ */

#else
    #error "Only include this file in each Microcontroller's kb_pin_def.h file."
#endif /* ONLY_INCLUDE_BSP_PIN_DEF_H_IN_KB_PIN_DEF_H_ */
