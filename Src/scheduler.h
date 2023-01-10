/** @file scheduler.h
*
* @brief Software implementation of scheduler. Uses 1ms systick interrupt to keep track of time.
* 
* Author: Ian Ress
* 
*/

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <stdbool.h>

#include "systick.h"

/**
 * @brief The maximum number of tasks the scheduler is allowed to run.
 * 
 */
#define MAX_TASKS                               5 

typedef struct {
    void (*handler)(void);      /* Task handler function. */
    systick_wordsize_t start;   /* Timestamp of when task last executed. */
    systick_wordsize_t now;     /* The current timestamp. */
    systick_wordsize_t freq;    /* Frequency task should execute at in ms. Example: freq = 5 executes the task every 5ms. */
} Task_t;

Task_t* const create_task(void(*task)(void), systick_wordsize_t taskfreq);
void delete_task(Task_t* task);
void begin_scheduler(void);
void clear_scheduler(void);

#endif /* SCHEDULER_H */
