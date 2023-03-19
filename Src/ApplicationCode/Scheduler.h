/**
 * @file Scheduler.h
 * @author Ian Ress
 * @brief Software implementation of scheduler. Uses 1ms systick interrupt to keep 
 * track of time. Currently uses a round-robin non-preemptive approach.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <stdbool.h>
#include "SysTick.h"

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

Task_t* const Create_Task(void(*task)(void), systick_wordsize_t taskfreq);
void Delete_Task(Task_t* task);
void Begin_Scheduler(void);
void Clear_Scheduler(void);

#endif /* SCHEDULER_H */
