/** @file assert.h
*
* @brief Used to throw compile and real-time errors. This is implemented via the naked attribute
* because we do not want to waste time saving program context. If this function triggers, a significant
* error has occured so we want to disable all interrupts and have program execution stop as soon
* as possible. Author: Ian Ress
*
*/

#ifndef ASSERT_H
#define ASSERT_H

void HARD_FAULT(void) __attribute__((naked));

#endif /* ASSERT_H */