/**
 * @file Endian.h
 * @author Ian Ress
 * @brief Determines endianness and appropriate byte swapping macros according to which MCU
 * is used. USB Specification requires certain fields to be in either Little or Big Endian 
 * format. We have to handle this differently according to our microcontroller's Endianness.
 * This file provides a portable way to do so across various AVR microcontrollers added to
 * this project in the future.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* TODO: Cleanup. Planning on defining Endianness in DeviceSpecific.h */

#ifndef ENDIAN_H
#define ENDIAN_H

#include <stdint.h>
#include "DeviceSpecific.h"


/**
 * @brief Swap the endianness of a 16-bit variable that is determined at compile-time. A macro is
 * needed because a function cannot swap the endianness of compile-time variable initializations.
 * Conversely, this macro cannot be used for run-time variables as the pre-processor expands 
 * the macro and afterwards it is up to the compiler on how to define 'x'. 'x' will be
 * unknown during compilation so this has the chance of returning a garbage value if it
 * is used for run-time variables. Use the static inline function variant for run-time endianness
 * swapping instead.
 * 
 * @param[in] x 16-bit compile-time variable to swap.
 * 
 * @return Swapped 16-bit variable
 * 
 */
#define SWAPENDIAN_COMPILETIME_16(x)            ((((x) & 0xFF00) >> 8U) | (((x) & 0x00FF) << 8U))


/**
 * @brief Swap the endianness of a 32-bit variable that is determined at compile-time. A macro is
 * needed because a function cannot swap the endianness of compile-time variable initializations.
 * Conversely, this macro cannot be used for run-time variables as the pre-processor expands 
 * the macro and afterwards it is up to the compiler on how to define 'x'. 'x' will be
 * unknown during compilation so this has the chance of returning a garbage value if it
 * is used for run-time variables. Use the static inline function variant for run-time endianness
 * swapping instead.
 * 
 * @param[in] x 32-bit compile-time variable to swap.
 * 
 * @return Swapped 32-bit variable
 * 
 */
#define SWAPENDIAN_COMPILETIME_32(x)            ((((x) & 0xFF000000) >> 24U) | (((x) & 0x00FF0000) >> 8U) | \
                                                (((x) & 0x0000FF00) << 8U)  | (((x) & 0x000000FF) << 24U))

/* Swap macros depending on MCU's Endianness */
#if defined(AVR_LITTLE_ENDIAN)
    /* Send 16-bit or 32-bit compile-time data to computer in Little Endian */
    #define LE16_TO_OS_COMPILETIME(x)               (x)
    #define LE32_TO_OS_COMPILETIME(x)               (x)

    /* Send 16-bit or 32-bit run-time data to computer in Little Endian */
    #define LE16_TO_OS_RUNTIME(x)                   (x)
    #define LE32_TO_OS_RUNTIME(x)                   (x)

    /* Receive 16-bit or 32-bit Little Endian data from computer. 
    Convert it to the MCUs Endianness. */
    #define LE16_FROM_OS_RUNTIME(x)                 (x)
    #define LE32_FROM_OS_RUNTIME(x)                 (x)

    /* Send 16-bit or 32-bit compile-time data to computer in Big Endian */
    #define BE16_TO_OS_COMPILETIME(x)               SWAPENDIAN_COMPILETIME_16(x)
    #define BE32_TO_OS_COMPILETIME(x)               SWAPENDIAN_COMPILETIME_32(x)

    /* Send 16-bit or 32-bit run-time data to computer in Big Endian */
    #define BE16_TO_OS_RUNTIME(x)                   SwapEndian_RunTime_16(x)
    #define BE32_TO_OS_RUNTIME(x)                   SwapEndian_RunTime_32(x)

    /* Receive 16-bit or 32-bit Big Endian data from computer. 
    Convert it to the MCUs Endianness. */
    #define BE16_FROM_OS_RUNTIME(x)                 SwapEndian_RunTime_16(x)
    #define BE32_FROM_OS_RUNTIME(x)                 SwapEndian_RunTime_32(x)

#elif defined(AVR_BIG_ENDIAN)
    /* Send 16-bit or 32-bit compile-time data to computer in Little Endian */
    #define LE16_TO_OS_COMPILETIME(x)               SWAPENDIAN_COMPILETIME_16(x)
    #define LE32_TO_OS_COMPILETIME(x)               SWAPENDIAN_COMPILETIME_32(x)

    /* Send 16-bit or 32-bit run-time data to computer in Little Endian */
    #define LE16_TO_OS_RUNTIME(x)                   SwapEndian_RunTime_16(x)
    #define LE32_TO_OS_RUNTIME(x)                   SwapEndian_RunTime_32(x)

    /* Receive 16-bit or 32-bit Little Endian data from computer. 
    Convert it to the MCUs Endianness. */
    #define LE16_FROM_OS_RUNTIME(x)                 SwapEndian_RunTime_16(x)
    #define LE32_FROM_OS_RUNTIME(x)                 SwapEndian_RunTime_32(x)

    /* Send 16-bit or 32-bit compile-time data to computer in Big Endian */
    #define BE16_TO_OS_COMPILETIME(x)               (x)
    #define BE32_TO_OS_COMPILETIME(x)               (x)

    /* Send 16-bit or 32-bit run-time data to computer in Big Endian */
    #define BE16_TO_OS_RUNTIME(x)                   (x)
    #define BE32_TO_OS_RUNTIME(x)                   (x)

    /* Receive 16-bit or 32-bit Big Endian data from computer. 
    Convert it to the MCUs Endianness. */
    #define BE16_FROM_OS_RUNTIME(x)                 (x)
    #define BE32_FROM_OS_RUNTIME(x)                 (x)
#endif


/* TODO: Cleanup, use union instead. */
/**
 * @brief Swap the endianness of a 16-bit variable that is determined during run-time.
 * A copy of the function's argument is explicitly made within the body. If the 
 * compiler decides to inline the function it will have the same scope as the caller and
 * we don't want to accidently overwrite the function's argument unless we explicitly write
 * code to do so. Therefore making a copy like this in an inline function means we get 
 * the potential optimization benefits of no function call overhead while also having 
 * the ability to preserve the original variable's value.
 * 
 * @param[in] Word uint16_t variable to swap.
 * 
 * @return Copy of input variable with swapped endianness.
 * 
 */
static inline uint16_t SwapEndian_RunTime_16(const uint16_t Word);
static inline uint16_t SwapEndian_RunTime_16(const uint16_t Word)
{
    uint16_t SwappedWordCopy = Word;
    uint8_t *ptr = (uint8_t*) &SwappedWordCopy;
    uint8_t temp = *ptr;

    *ptr = *(ptr + 1);
    *(ptr + 1) = temp;

    return SwappedWordCopy;
}

/* TODO: Cleanup, use union instead. */
/**
 * @brief Swap the endianness of a 32-bit variable that is determined during run-time.
 * A copy of the function's argument is explicitly made within the body. If the 
 * compiler decides to inline the function it will have the same scope as the caller and
 * we don't want to accidently overwrite the function's argument unless we explicitly write
 * code to do so. Therefore making a copy like this in an inline function means we get 
 * the potential optimization benefits of no function call overhead while also having 
 * the ability to preserve the original variable's value.
 * 
 * @param[in] Word uint32_t variable to swap.
 * 
 * @return Copy of input variable with swapped endianness.
 * 
 */
static inline uint32_t SwapEndian_RunTime_32(const uint32_t Word);
static inline uint32_t SwapEndian_RunTime_32(const uint32_t Word)
{
    uint32_t SwappedWordCopy = Word;
    uint8_t *ptr = (uint8_t*) &SwappedWordCopy;
    uint8_t temp = *ptr;

    *ptr = *(ptr + 3);
    *(ptr + 3) = temp;
    temp = *(ptr + 1);
    *(ptr + 1) = *(ptr + 2);
    *(ptr + 2) = temp;

    return SwappedWordCopy;
}

#endif /* ENDIAN_H */
