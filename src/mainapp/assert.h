/**
 * @file assert.h
 * @author Ian Ress
 * @brief For error checking.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ASSERT_H
#define ASSERT_H

/**
 * @brief Produces a compilation error if @p condition is false.
 * 
 */
#define COMPILE_ASSERT(condition)       (void)sizeof(char[(condition) ? 1 : -1])

#endif /* ASSERT_H */
