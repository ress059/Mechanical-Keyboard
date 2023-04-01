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
    HSM_DISPATCH_STATUS,    /*  Used to start executing Event handlers in Hsm_Dispatch() function. */
    TRAN_STATUS,            /*  Event dispatched to the HSM resulted in a State Transition. The Entry and Exit Event
                                of the state that handled the event will also execute. */
    INTERNAL_TRAN_STATUS,   /*  Event dispatched to the HSM resulted in a State Transition. However the Entry and
                                Exit Events of the state that handled the event will not execute. */
    HANDLED_STATUS,         /*  Event handler executed. */
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

/**
 * @brief Used in State Handler functions. State to State Transition or used to reset a State. 
 * Transition from the current state you were in to the State @p target_
 * 
 */
#define TRAN(target_)                   (((Hsm *)me)->state = (State *)(&target_), TRAN_STATUS)


/**
 * @brief Used in State Handler functions. Internal State Transition to state @p target_
 * The State that calls this macro is referred to as @p S
 * If @p target_ takes you to a Substate of @p S, then the Entry and Exit Events of @p S will NOT execute.
 * If @p target_ takes you to a Superstate of @p S, the the Exit Event of @p S will execute.
 * 
 */
#define INTERNAL_TRAN(target_)          (((Hsm *)me)->state = (State *)(&target_), INTERNAL_TRAN_STATUS)


/**
 * @brief Used in State Handler functions. Transition to a Superstate @p super_ 
 * Usually used when an event doesn't exist in the current state. 
 * 
 */
#define SUPER(super_)                   (((Hsm *)me)->state = (State *)(&super_), SUPER_STATUS)


void State_Ctor(State * const me, State * const superstate, StateHandler * const hndlr);
void Hsm_Ctor(Hsm * const me, StateHandler initial);
void Hsm_Begin(Hsm * const me, const Event * const e);
void Hsm_Dispatch(Hsm * const me, const Event * const e);

#endif /* HSM_H */
