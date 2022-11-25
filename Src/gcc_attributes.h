/** @file gcc_attributes.h
*
* @brief GNU and AVR-specific attributes are used throughout driver code and some application code.
* This wrapper file is used to generate a compiler error if an AVR GCC compiler is not used. This 
* ensures attributes used throughout the code are not ignored, and behave as expected. 
*
* Author: Ian Ress
*
*/ 

#ifndef GCC_ATTRIBUTES_H
#define GCC_ATTRIBUTES_H

/* Check for GCC V3.1 and up. Check if compiling for AVR target */
#if defined(__AVR__) && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR >= 1)))
    /**
     * @brief Removes any preamble or postamble from the function. When used, the function will not have 
     * any register or stack saving code. This should be used with caution, and when used the programmer
     * is responsible for maintaining stack and register integrity.
     * 
     */
    #define GCCATTRIBUTE_NAKED                  __attribute__ ((naked))

    /**
     * @brief Places the function in one of the initialization sections, which execute before the main function
     * of the application. Refer to the avr-libc manual for more information on the initialization sections.
     *
     * @param[in] SectionIndex  Initialization section number where the function should be placed.
     * 
     */
    #define GCCATTRIBUTE_SECTION(SectionIndex)  __attribute__ ((section (".init" #SectionIndex )))

    /**
     * @brief This attribute, attached to a function, means that code must be emitted for the function even 
     * if it appears that the function is not referenced.
     * 
     */
    #define GCCATTRIBUTE_USED                   __attribute__((used))

    /**
     * @brief Marks a variable or struct element for packing into the smallest space available, omitting any
     * alignment bytes usually added between fields to optimize field accesses. 
     * NOTE: Users should be aware of what the packed attribute does on machines that are greater than 8-bits, 
     * particularly the misalignment of words. In general dereferencing pointers to packed struct members should
     * be avoided on machines that are greater than 8-bits. Behavior would depend on the compiler
     * and CPU.
     * 
     */
    #define GCCATTRIBUTE_PACKED                 __attribute__ ((packed))
#endif

#endif /* GCC_ATTRIBUTES_H */
