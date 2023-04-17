/**
 * @file Endian.h
 * @author Ian Ress
 * @brief Determines appropriate byte swapping macros based on the target microcontroller's
 * Endianness. The Endianness for each supported target/future targets are defined in 
 * DeviceSpecific.h. USB is Little Endian so swapping macros will change based on if the
 * microcontroller is Little or Big Endian.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ENDIAN_H
#define ENDIAN_H

#include <stdint.h>
#include "DeviceSpecific.h"

/**
 * @brief Do not use this directly in the application code. This is meant to be used for the
 * Endianness swapping macros defined at the end of Endian.h
 * 
 */
#define SWAPENDIAN_COMPILETIME_16(x)            ((((x) & 0xFF00) >> 8U) | (((x) & 0x00FF) << 8U))

/**
 * @brief Do not use this directly in the application code. This is meant to be used for the
 * Endianness swapping macros defined at the end of Endian.h
 * 
 */
#define SWAPENDIAN_COMPILETIME_32(x)            ((((x) & 0xFF000000) >> 24U) | (((x) & 0x00FF0000) >> 8U) | \
                                                (((x) & 0x0000FF00) << 8U)  | (((x) & 0x000000FF) << 24U))


/**
 * @brief Do not use this directly in the application code. This is meant to be used for the
 * Endianness swapping macros defined at the end of Endian.h
 * 
 */
static inline uint16_t SwapEndian_RunTime_16(const uint16_t Word);
static inline uint16_t SwapEndian_RunTime_16(const uint16_t Word)
{
    uint16_t Copy = Word;
    uint8_t * ptr = (uint8_t *)&Copy;
    uint8_t temp = *ptr;

    *ptr = *(ptr + 1);
    *(ptr + 1) = temp;

    return Copy;
}


/**
 * @brief Do not use this directly in the application code. This is meant to be used for the
 * Endianness swapping macros defined at the end of Endian.h
 * 
 */
static inline uint32_t SwapEndian_RunTime_32(const uint32_t Word);
static inline uint32_t SwapEndian_RunTime_32(const uint32_t Word)
{
    uint32_t Copy = Word;
    uint8_t * ptr = (uint8_t *)&Copy;
    uint8_t temp = *ptr;

    *ptr = *(ptr + 3);
    *(ptr + 3) = temp;
    temp = *(ptr + 1);
    *(ptr + 1) = *(ptr + 2);
    *(ptr + 2) = temp;

    return Copy;
}


/**
 * Use these macros within the application code.
 */
#if defined(AVR_LITTLE_ENDIAN)
    /**
     * @brief Swaps the endianness of a 16-bit variable that is determined at compile-time. A macro is
     * needed because a function cannot swap the endianness of compile-time variable initializations.
     * In this case, our target MCU is Little Endian. Therefore the input value will already be 
     * stored as Little Endian and this macro will do nothing. However this MUST be left within 
     * the application code so the same software is compatiable with both Little and Big Endian targets.
     * 
     * @warning Do not use this for values determined at run-time. The pre-processor expands 
     * the macro and afterwards it is up to the compiler on how to define 'x', which can lead
     * to undesirable behavior. For example, passing a function call into x.
     * Use @p LE16_RUNTIME(x) for run-time endianness swapping.
     * 
     * @param x 16-bit compile-time variable to swap.
     * 
     */
    #define LE16_COMPILETIME(x)                     (x)

    /**
     * @brief Swaps the endianness of a 32-bit variable that is determined at compile-time. A macro is
     * needed because a function cannot swap the endianness of compile-time variable initializations.
     * In this case, our target MCU is Little Endian. Therefore the input value will already be 
     * stored as Little Endian and this macro will do nothing. However this MUST be left within 
     * the application code so the same software is compatiable with both Little and Big Endian targets.
     * 
     * @warning Do not use this for values determined at run-time. The pre-processor expands 
     * the macro and afterwards it is up to the compiler on how to define 'x', which can lead
     * to undesirable behavior. For example, passing a function call into x.
     * Use @p LE16_RUNTIME(x) for run-time endianness swapping.
     * 
     * @param x 32-bit compile-time variable to swap.
     * 
     */
    #define LE32_COMPILETIME(x)                     (x)

    /**
     * @brief Swaps the endianness of a 16-bit variable that is determined at run-time.
     * In this case, our target MCU is Little Endian. Therefore the input value will already be 
     * stored as Little Endian and this macro will do nothing. However this MUST be left within 
     * the application code so the same software is compatiable with both Little and Big Endian targets.
     * 
     * @param x 16-bit run-time variable to swap.
     * 
     */
    #define LE16_RUNTIME(x)                         (x)

    /**
     * @brief Swaps the endianness of a 32-bit variable that is determined at run-time. 
     * In this case, our target MCU is Little Endian. Therefore the input value will already be 
     * stored as Little Endian and this macro will do nothing. However this MUST be left within 
     * the application code so the same software is compatiable with both Little and Big Endian targets.
     * 
     * @param x 32-bit run-time variable to swap.
     * 
     */
    #define LE32_RUNTIME(x)                         (x)

#else /* Big Endian. CompileChecks.h will check if Endianness is defined properly in DeviceSpecific.h so we don't need an error guard here. */

    /**
     * @brief Swaps the endianness of a 16-bit variable that is determined at compile-time. A macro is
     * needed because a function cannot swap the endianness of compile-time variable initializations.
     * In this case, our target MCU is Big Endian. Therefore the input value's byte order will be 
     * swapped so 'x' is stored as Little Endian. This macro MUST be left within the application 
     * code so the same software is compatiable with both Little and Big Endian targets.
     * 
     * @warning Do not use this for values determined at run-time. The pre-processor expands 
     * the macro and afterwards it is up to the compiler on how to define 'x', which can lead
     * to undesirable behavior. For example, passing a function call into x.
     * Use @p LE16_RUNTIME(x) for run-time endianness swapping.
     * 
     * @param x 16-bit compile-time variable to swap.
     * 
     */
    #define LE16_COMPILETIME(x)                     SWAPENDIAN_COMPILETIME_16(x)

    /**
     * @brief Swaps the endianness of a 32-bit variable that is determined at compile-time. A macro is
     * needed because a function cannot swap the endianness of compile-time variable initializations.
     * In this case, our target MCU is Big Endian. Therefore the input value's byte order will be 
     * swapped so 'x' is stored as Little Endian. This macro MUST be left within the application 
     * code so the same software is compatiable with both Little and Big Endian targets.
     * 
     * @warning Do not use this for values determined at run-time. The pre-processor expands 
     * the macro and afterwards it is up to the compiler on how to define 'x', which can lead
     * to undesirable behavior. For example, passing a function call into x.
     * Use @p LE16_RUNTIME(x) for run-time endianness swapping.
     * 
     * @param x 32-bit compile-time variable to swap.
     * 
     */
    #define LE32_COMPILETIME(x)                     SWAPENDIAN_COMPILETIME_32(x)

    /**
     * @brief Swaps the endianness of a 16-bit variable that is determined at run-time.
     * In this case, our target MCU is Big Endian. Therefore a copy of 'x' in Little Endian
     * format (byte ordering swapped) will be returned. This macro MUST be left within the application 
     * code so the same software is compatiable with both Little and Big Endian targets.
     * 
     * @warning This will return a copy of 'x' with swapped Endianness instead of swapping the
     * Endianness of 'x' directly. E.g. x = LE16_RUNTIME(x); should be called instead of 
     * LE16_RUNTIME(x);
     * 
     * @param x 16-bit run-time variable to swap.
     * 
     */
    #define LE16_RUNTIME(x)                         SwapEndian_RunTime_16(X)

    /**
     * @brief Swaps the endianness of a 32-bit variable that is determined at run-time.
     * In this case, our target MCU is Big Endian. Therefore a copy of 'x' in Little Endian
     * format (byte ordering swapped) will be returned. This macro MUST be left within the application 
     * code so the same software is compatiable with both Little and Big Endian targets.
     * 
     * @warning This will return a copy of 'x' with swapped Endianness instead of swapping the
     * Endianness of 'x' directly. E.g. x = LE32_RUNTIME(x); should be called instead of 
     * LE32_RUNTIME(x);
     * 
     * @param x 32-bit run-time variable to swap.
     * 
     */
    #define LE32_RUNTIME(x)                         SwapEndian_RunTime_32(x)
#endif

#endif /* ENDIAN_H */
