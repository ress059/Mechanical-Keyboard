/**
 * @file Hsm.h
 * @author Template from Dr. Miro Samek, Quantum Leaps LLC. Adjustments for specific
 * application made by Ian Ress.
 * @brief Hierarchical State Machine Base Class
 * @date 2023-03-20
 * 
 */

#ifndef HSM_H
#define HSM_H

#include <stdint.h>
#include "Event.h"

/* Hsm Base Class */
typedef struct Hsm Hsm;     /* Must forward declare for StateHandler typedef. */

typedef enum
{
    HSM_TRAN_STATUS,            /*  Event dispatched to the Hsm resulted in a State Transition. The Entry and Exit Event
                                    of the state that handled the event will also execute. */
    HSM_INTERNAL_TRAN_STATUS,   /*  Event dispatched to the Hsm resulted in a State Transition. However the Entry and
                                    Exit Events of the state that handled the event may not execute. See description in
                                    HSM_INTERNAL_TRAN(target_) macro for more details. */
    HSM_HANDLED_STATUS,         /*  Event handler executed. */
    HSM_IGNORED_STATUS,         /*  Event dispatched to Hsm was ignored. */
    HSM_SUPER_STATUS            /*  Transitioned to a superstate. If an event dispatched to the Hsm doesn't exist in the current state,
                                    the state hierarchy is traversed up until the event is located or the Top State is reached. 
                                    If the event does not exist in the Top State, it is ignored. */
} HsmStatus;

typedef HsmStatus (*HsmStateHandler)(Hsm * const me, const Event * const e);
typedef HsmStatus (*HsmInitStateHandler)(Hsm * const me);

typedef struct 
{
    HsmState * superstate;      /*  This is a pointer to the State above the current state. For example
                                    if State A11 is nested inside State A1, the State struct of A11 would define
                                    a pointer to State A1 for the superstate. NULL if no superstate. */

    HsmStateHandler hndlr;      /*  Current state's handler function. This is the function that will execute
                                    when events are dispatched to the Hsm. */
} HsmState;

struct Hsm
{
    HsmState top;              /*  Top-most State. It's superstate will be (HsmState *)0 */
    HsmState * state;          /*  The Current State the Hsm is in. */
    /* Private members can be added here in subclass that inherits Hsm Base Class. */
};



/* Hsm Methods */

/**
 * @brief Used in user-defined Hsm State Handler functions. Call when a State to State Transition 
 * or a State Reset occurs. Transitions from the current state you were in to the State @p target_
 * The Hsm Dispatcher will determine the proper State Traversal and Entry/Exit Event sequence to execute.
 * 
 * @return HSM_TRAN_STATUS. This is used by the Hsm Dispatcher.
 * 
 */
#define HSM_TRAN(target_)                   (((Hsm *)me)->state = (HsmState *)(&target_), HSM_TRAN_STATUS)


/**
 * @brief Used in user-defined Hsm State Handler functions. Call when an Internal State Transition (Nested
 * State Transition) to state @p target_ occurs. The Hsm Dispatcher will determine the proper State 
 * Traversal and Entry/Exit Event sequence to execute.
 * 
 * @note Below is an example of what the Dispatcher would do if an Internal State Transition occurs:
 * In the following example, the State that calls this macro is referred to as @p S
 * If @p target_ takes you to a Substate of @p S, then the Entry and Exit Events of @p S will NOT execute.
 * If @p target_ takes you to a Superstate of @p S, the the Exit Event of @p S will execute.
 * 
 * @return HSM_INTERNAL_TRAN_STATUS. This is used by the Hsm Dispatcher.
 * 
 */
#define HSM_INTERNAL_TRAN(target_)          (((Hsm *)me)->state = (HsmState *)(&target_), HSM_INTERNAL_TRAN_STATUS)


/**
 * @brief Used in user-defined Hsm State Handler functions. Call when a transition to the current
 * State's Superstate @p super_ occurs. Usually used when a Dispatched Event doesn't exist in the 
 * current state. The Hsm State hierarchy is traversed up until the Event is found or it is 
 * ignored in the Top State.
 * 
 * @return HSM_SUPER_STATUS. This is used by the Hsm Dispatcher.
 * 
 */
#define HSM_SUPER(super_)                   (((Hsm *)me)->state = (HsmState *)(&super_), HSM_SUPER_STATUS)


void HsmState_Ctor(HsmState * const me, const HsmState * const superstate, const HsmStateHandler hndlr);
void Hsm_Ctor(Hsm * const me, const HsmStateHandler tophndlr);
bool Hsm_Begin(Hsm * const me, const HsmStateHandler inithndlr);
void Hsm_Dispatch(Hsm * const me, const Event * const e);

#endif /* HSM_H */
