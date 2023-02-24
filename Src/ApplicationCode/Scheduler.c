/**
 * @file Scheduler.c
 * @author Ian Ress
 * \brief Software implementation of scheduler. Uses 1ms systick interrupt to keep 
 * track of time. Currently uses a round-robin non-preemptive approach.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stddef.h>
#include <util/atomic.h>
#include "Scheduler.h"

static systick_wordsize_t g_ms_copy = 0;

static Task_t tasks[MAX_TASKS] =
{
    {NULL, 0, 0, 0},
    {NULL, 0, 0, 0},
    {NULL, 0, 0, 0},
    {NULL, 0, 0, 0},
    {NULL, 0, 0, 0},
};


/**
 * \brief Checks if the scheudler slot is occupied with a task.
 * 
 * \return The first index in the scheduler where a task is not assigned. Returns -1 
 * if no more tasks can be added to the scheduler 
 * 
 */
static int isempty(void);
static int isempty(void)
{
    for (uint8_t i = 0; i < (uint8_t)MAX_TASKS; i++)
    {
        if (tasks[i].handler == NULL)
        {
            return i;
        }
    }
    return -1;
}


/**
 * \brief Deletes the task in the scheduler slot.
 * 
 */
void delete_task(Task_t* task)
{
    task->handler = NULL;
    task->start = 0;
    task->now = 0;
    task->freq = 0;
}


/**
 * \brief Create a task object and adds it to an available scheduler slot.
 * 
 * \param taskhandler Callback to the task's function for the scheduler to execute. If the function requires
 * different arguments, the user should place it inside a wrapper function.
 * \param taskfreq How often the task should execute.
 * 
 * \return Constant pointer where the task object is stored in the scheduler if successful. Returns NULL if 
 * there is no room in the scheduler to add another task. It is up to the end user to check 
 * if a non-NULL object is returned and also to not dereference a NULL-returned object.
 * 
 */
Task_t* const create_task(void(*task)(void), systick_wordsize_t taskfreq)
{
    int idx = isempty();
    if (idx >= 0)
    {
        tasks[idx].handler = task;
        tasks[idx].freq = taskfreq;
        return &(tasks[idx]);
    }
    else
    {
        return NULL;
    }
}


/**
 * \brief Must be called periodically (e.g. within super loop). The scheduler uses a 1ms 
 * systick interrupt to keep track of time and determine which tasks are ready to execute.
 * The scheduler is non-preemptive.
 * 
 */
void begin_scheduler(void)
{
    for (uint8_t i = 0; i < (uint8_t)MAX_TASKS; i++)
    {
        if (tasks[i].handler != NULL)
        {
            if ( ((systick_wordsize_t)(tasks[i].now - tasks[i].start)) >= tasks[i].freq )
            {
                tasks[i].handler();

                ATOMIC_BLOCK(ATOMIC_FORCEON) /* Get most recent systick value after task handler executes. */
                {
                    g_ms_copy = g_ms;
                }
                tasks[i].start = g_ms_copy;
            }
            else
            {
                ATOMIC_BLOCK(ATOMIC_FORCEON)
                {
                    g_ms_copy = g_ms;
                }
                tasks[i].now = g_ms_copy;
            }
        }
    }
}


/**
 * \brief Clears all of the scheduler slots.
 * 
 */
void clear_scheduler(void)
{
    for (uint8_t i = 0; i < (uint8_t)MAX_TASKS; i++)
    {
        delete_task(&tasks[i]);
    }
}
