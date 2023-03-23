/**
 * @file Fsm.c
 * @author Dr. Miro Samek, Quantum Leaps LLC 
 * @brief Finite State Machine and Event Base Class
 * @date 2023-03-18
 * 
 */

#include "Fsm.h"

static const Event entryEvent = {ENTRY_EVENT};
static const Event exitEvent = {EXIT_EVENT};

/**
 * @brief Fsm Base Class constructor.
 * 
 * @param me Pointer to Fsm object.
 * @param initial Function that executes when the Fsm is first initialized (Initial Transition).
 * Ensure this function calls the TRAN(target) macro to transition to the next state.
 * 
 */
void Fsm_Ctor(Fsm * const me, StateHandler initial)
{
    me->state = initial;
}


/**
 * @brief Executes Initial Transition function assign in Fsm_Ctor(). Then
 * executes the entry event of the next state transitioned into.
 * 
 * @param me Pointer to Fsm object.
 * @param e Event Signal dispatched to the Fsm when it is first initialized.
 * 
 */
void Fsm_Init(Fsm * const me, const Event * const e)
{
    if (me->state != (StateHandler)0) /* TODO: Replace with run-time error handler */
    {
        (*me->state)(me, e); /* Execute Initial Transition function assigned in Fsm_Ctor. */
        (*me->state)(me, &entryEvent); /* Execute entry event of the the next state transitioned into. */
    }
}


/**
 * @brief Runs the Fsm. If a state transition takes place, the dispatcher
 * automatically runs the Exit Event of the previous state and the Entry
 * Event of the state transitioned into.
 * 
 * @param me Pointer to Fsm object.
 * @param e Event Signal dispatched to the Fsm.
 * 
 */
void Fsm_Dispatch(Fsm * const me, const Event * const e)
{
    State status;
    StateHandler prev_state = me->state;

    if (me->state != (StateHandler)0) /* TODO: Replace with run-time error handler */
    {
        status = (*me->state)(me, e);

        if (status == TRAN_STATUS)
        {
            (*prev_state)(me, &exitEvent);
            (*me->state)(me, &entryEvent);
        }
    }
}
