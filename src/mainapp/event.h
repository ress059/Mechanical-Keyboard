/**
 * @file event.h
 * @author Dr. Miro Samek, Quantum Leaps LLC 
 * @brief Event Base Class for Finite State Machine and Hierarchical State Machine Classes
 * @date 2023-03-18
 * 
 */


#ifndef EVENT_H_
#define EVENT_H_

#include <stdint.h>

typedef uint16_t Signal;

enum ReservedSignals
{
    ENTRY_EVENT = 0,      /* Entry Event Signal when transitioning into a state. */
    EXIT_EVENT,           /* Exit Event Signal when transitioning out of a state. */
    /*********/
    USER_SIG              /* Beginning of user-definable Event Signals. */
};

typedef struct
{
    Signal sig;
    /* Private members can be added here in subclass that inherits Event Base Class. */
} Event;

#endif /* EVENT_H_ */
