/**
 * @file CompileChecks.c
 * @author Ian Ress
 * @brief Solely used for compile-time checks. CompilerChecks.h/.c is meant to be compiled in 
 * its own translation unit, never being included in any other source/header file.
 * @date 2023-02-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Attributes.h"
#include "CompileChecks.h"


/**
 * @brief Used to check if AVR_reg_t typedef is defined. This typedef is the target CPU's
 * word-size.
 * 
 */
#define AVR_REG_T_CHECK                     (void)sizeof(char[(2*(sizeof(AVR_reg_t))) - 1])


/**
 * @brief Solely used to check that AVR_reg_t typedef is defined and greater than 0. If AVR_reg_t is not defined there will be
 * a compile-time error. If AVR_reg_t is equal to 0, the AVR_REG_T_CHECK macro expands to (void)sizeof(char[-1]) which
 * will also get a compile-time error. Otherwise, the check passes.
 * 
 */
static void AVR_Reg_Check(void) GCCATTRIBUTE_UNUSED;
static void AVR_Reg_Check(void)
{
    AVR_REG_T_CHECK;
}
