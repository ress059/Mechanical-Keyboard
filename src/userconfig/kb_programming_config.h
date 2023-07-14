/**
 * @file kb_programming_config.h
 * @author Ian Ress
 * @brief The user can define how their Keyboard is able to be programmed here. Common programming
 * interfaces are JTAG, SWD (for ARM), or PDI (Atmel). Setting a programming option to 0 disables it and
 * allows the programming pins to be used as GPIOs that can be assigned to a Keyboard Row/Column.
 * Setting a programming option to 1 enables it and disables the ability for the relevant pins to
 * be assigned to a Keyboard Row/Column. The user must assign all options to either 0 or 1.
 * @date 2023-06-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef KB_PROGRAMMING_CONFIG_H_
#define KB_PROGRAMMING_CONFIG_H_


/**
 * @brief Allows the Keyboard to be programmed and debugged over JTAG. Set to 0 to disable
 * this option or 1 to enable this option.
 * 
 * @attention The JTAG pins cannot be assigned to a Keyboard Row/Column if this parameter is
 * enabled since these pins can no longer be GPIOs. A compilation error will occur if JTAG
 * is enabled but one of the pins is assigned to a Keyboard Row/Column within kb_config.h.
 * 
 * @warning A compilation error will occur if this is not set to 0 or 1.
 * 
 */
#define KB_ENABLE_JTAG                          1


/**
 * @brief Allows the Keyboard to be programmed and debugged over SWD. Set to 0 to disable
 * this option or 1 to enable this option. This only applies to ARM targets. If a non-ARM
 * target is used, this definition will be ignored.
 * 
 * @attention The SWD pins cannot be assigned to a Keyboard Row/Column if this parameter is
 * enabled since these pins can no longer be GPIOs. A compilation error will occur if SWD
 * is enabled but one of the pins is assigned to a Keyboard Row/Column within kb_config.h.
 * 
 * @warning A compilation error will occur if this is not set to 0 or 1.
 * 
 */
#define KB_ENABLE_SWD                           0


/**
 * @brief Allows the Keyboard to be programmed and debugged over PDI. Set to 0 to disable
 * this option or 1 to enable this option. This only applies to Atmel targets. If a non-Atmel
 * target is used, this definition will be ignored.
 * 
 * @attention The PDI pins cannot be assigned to a Keyboard Row/Column if this parameter is
 * enabled since these pins can no longer be GPIOs. A compilation error will occur if PDI
 * is enabled but one of the pins is assigned to a Keyboard Row/Column within kb_config.h.
 * 
 * @warning A compilation error will occur if this is not set to 0 or 1.
 * 
 */
#define KB_ENABLE_PDI                           0


#error "TODO: ADD THESE TO COMPILECHECKS.H"


#endif /* KB_PROGRAMMING_CONFIG_H_ */
