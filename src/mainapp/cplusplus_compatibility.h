/**
 * @file cplusplus_compatibility.h
 * @author Ian Ress
 * @brief For backwards compatibility between C and C++ compilers.
 * @date 2023-04-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#if defined(__cplusplus)
    #define SCOPE_RESOLUTION(a, b)                  (a)::(b)
#else
    #define SCOPE_RESOLUTION(a, b)                  (b)
#endif
