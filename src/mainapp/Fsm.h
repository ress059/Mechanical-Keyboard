/**
 * @file Fsm.h
 * @author Dr. Miro Samek, Quantum Leaps LLC 
 * @brief Finite State Machine and Event Base Class
 * @date 2023-03-18
 * 
 */


#ifndef FSM_H
#define FSM_H

#include <stdint.h>
#include "Event.h"

typedef struct Fsm Fsm; /* Must forward declare for FsmStateHandler typedef. */

typedef enum
{
    FSM_TRAN_STATUS,
    FSM_HANDLED_STATUS,
    FSM_IGNORED_STATUS,
    FSM_INIT_STATUS,
} FsmStatus;

typedef FsmStatus (*FsmStateHandler)(Fsm * const me, const Event * const e);

struct Fsm
{
    FsmStateHandler state;
    /* Private members can be added here in subclass that inherits Fsm Base Class. */
};


/* Fsm Methods */

/**
 * @brief Used in Fsm State Handler functions. State to State Transition or used to reset a State. 
 * Transition from the current state you were in to the State @p target_
 * 
 * @return FSM_TRAN_STATUS. This is used by the Fsm Dispatcher.
 * 
 */
#define FSM_TRAN(target_)   (((Fsm *)me)->state = (FsmStateHandler)(target_), FSM_TRAN_STATUS)

void Fsm_Ctor(Fsm * const me, FsmStateHandler initial);
void Fsm_Init(Fsm * const me, const Event * const e);
void Fsm_Dispatch(Fsm * const me, const Event * const e);

#endif /* FSM_H */
