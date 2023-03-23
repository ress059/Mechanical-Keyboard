/**
 * @file Fsm.h
 * @author Dr. Miro Samek, Quantum Leaps LLC 
 * @brief Finite State Machine and Event Base Class
 * @date 2023-03-18
 * 
 */


#ifndef FSM_H
#define FSM_H

#if defined(HSM_H)
    #error "Do not include both Fsm.h and Hsm.h. Your object must either be a Hierarchical State Machine or Finite State Machine. It cannot be both."
#endif

#include <stdint.h>

typedef struct Fsm Fsm; /* Must forward declare for StateHandler typedef. */
typedef uint16_t Signal;

enum ReservedSignals
{
    ENTRY_EVENT,          /* Entry Event Signal when transitioning into a state. */
    EXIT_EVENT,           /* Exit Event Signal when transitioning out of a state. */
    /*********/
    USER_SIG              /* Beginning of user-definable Event Signals. */
};

/* Event Base Class */
typedef struct
{
    Signal sig;
    /* Private members can be added here in subclass that inherits Event Base Class. */
} Event;

typedef enum
{
    TRAN_STATUS,
    HANDLED_STATUS,
    IGNORED_STATUS,
    INIT_STATUS,
} State;

typedef State (*StateHandler)(Fsm * const me, const Event * const e);

/* Fsm Base Class */
struct Fsm
{
    StateHandler state;
    /* Private members can be added here in subclass that inherits Fsm Base Class. */
};

/* Fsm Methods */
#define TRAN(target_)   (((Fsm *)me)->state = (StateHandler)(target_), TRAN_STATUS)
void Fsm_Ctor(Fsm * const me, StateHandler initial);
void Fsm_Init(Fsm * const me, const Event * const e);
void Fsm_Dispatch(Fsm * const me, const Event * const e);

#endif /* FSM_H */
