/**
 * @file Hsm.h
 * @author Dr. Miro Samek, Quantum Leaps LLC 
 * @brief Hierarchical State Machine and Event Base Class
 * @date 2023-03-20
 * 
 */

#ifndef HSM_H
#define HSM_H

#if defined(FSM_H)
    #error "Do not include both Fsm.h and Hsm.h. Your object must either be a Hierarchical State Machine or Finite State Machine. It cannot be both."
#endif

#include <stdint.h>

#define NULL                ((void*) 0)

/* Event Base Class */
enum ReservedSignals
{
    ENTRY_EVENT = 0,        /* Entry Event Signal when transitioning into a state. */
    EXIT_EVENT,             /* Exit Event Signal when transitioning out of a state. */
    /*********/
    USER_SIG                /* Beginning of user-definable Event Signals. */
};

typedef uint16_t Signal;

typedef struct
{
    Signal sig;
    /* Private members can be added here in subclass that inherits Event Base Class. */
} Event;

/* Hsm Base Class */
typedef struct Hsm Hsm;     /* Must forward declare for StateHandler typedef. */

typedef enum
{
    HSM_DISPATCH_STATUS,    /*  Used for Hsm_Dispatch() */
    TRAN_STATUS,            /*  Event dispatched to the HSM resulted in a State Transition */
    HANDLED_STATUS,         /*  Event handler executed */
    IGNORED_STATUS,         /*  Event dispatched to HSM was ignored. */
    INIT_STATUS,
    SUPER_STATUS            /*  Transitioned to a superstate. If an event dispatched to the HSM doesn't exist in the current state,
                                the state hierarchy is traversed up until the event is located or the Top State is reached. 
                                If the event does not exist in the Top State, it is ignored. */
} Status;

typedef Status (*StateHandler)(Hsm * const me, const Event * const e);

typedef struct 
{
    State * superstate;     /*  This is a pointer to the State above the current state. For example
                                if State A11 is nested inside State A1, the State struct of A11 would define
                                a pointer to State A1 for the superstate. NULL if no superstate. */

    StateHandler hndlr;     /*  Current state's Event Handler function */
} State;

struct Hsm
{
    State * state;
    /* Private members can be added here in subclass that inherits Hsm Base Class. */
};

/* Hsm Methods */
#define TRAN(target_)   (((Hsm *)me)->state = (State *)(&target_), TRAN_STATUS)
#define SUPER(super_)   (((Hsm *)me)->state = (State *)(&super_), SUPER_STATUS)
void State_Ctor(State * const me, State * const superstate, StateHandler * const hndlr);
void Hsm_Ctor(Hsm * const me, StateHandler initial);
void Hsm_Begin(Hsm * const me, const Event * const e);
void Hsm_Dispatch(Hsm * const me, const Event * const e);

#endif /* HSM_H */
