/**
 * @file Hsm.c
 * @author Dr. Miro Samek, Quantum Leaps LLC 
 * @brief Hierarchical State Machine and Event Base Class
 * @date 2023-03-20
 * 
 */

#include <stdbool.h>
#include "Hsm.h"

static const Event entryEvent = {ENTRY_EVENT};
static const Event exitEvent = {EXIT_EVENT};


/**
 * @brief Initializes a substate within the Hsm. 
 * 
 * @param me Pointer to the state you want to initialize.
 * @param superstate Pointer to the superstate of your current state. For example
 * if State A11 is nested inside State A1, the superstate passed in A11's constructor
 * would point to State A1. State_Ctor(&State_A11, &State_A1, &State_A11 handler);
 * @param hndlr The State's Event Handler function. Whenever you are in this current state
 * this event handler function will process events dispatched to the Hsm. Each state
 * can be assigned an individual handler function. This is because event processing
 * will be unique depending on whcih state you are currently in.
 * 
 */
void State_Ctor(State * const me, State * const superstate, StateHandler * const hndlr)
{
    me->superstate = superstate;
    me->hndlr = hndlr;
}


/**
 * @brief Hsm Base Class constructor.
 * 
 * @param me Pointer to Hsm object.
 * @param initial Function that executes when the Hsm is first initialized (Initial Transition).
 * Ensure this function calls the TRAN(target) macro to transition to the next state.
 * 
 */
void Hsm_Ctor(Hsm * const me, StateHandler initial)
{
    me->state = initial;
}


/**
 * @brief Executes Initial Transition function assigned in Hsm_Ctor(). Then
 * executes the entry event of the next state transitioned into.
 * 
 * @warning Must be called after Hsm_Ctor()
 * 
 * @param me Pointer to Hsm object.
 * @param e Event Signal dispatched to the Hsm when it is first initialized.
 * 
 */
void Hsm_Begin(Hsm * const me, const Event * const e)
{
    if (me->state->hndlr != (StateHandler)0) /* TODO: Replace with run-time error handler */
    {
        (void)(*me->state->hndlr)(me, e); /* Execute Initial Transition function assigned in Hsm_Ctor. */
        (void)(*me->state->hndlr)(me, &entryEvent); /* Execute entry event of the the next state transitioned into. */
    }
}


/**
 * @brief Runs the Hsm. If a state transition takes place, the dispatcher
 * determines the entry and exit paths and executes the Entry and Exit
 * Events of the appropriate states.
 * 
 * @warning Do not execute this in both the main application code and within an ISR.
 * If you need to use ISRs to dispatch events to the Hsm, add the event to a queue
 * and dispatch events in the main application.
 * 
 * @param me Pointer to Hsm object.
 * @param e Event Signal dispatched to the Hsm.
 * 
 */
void Hsm_Dispatch(Hsm * const me, const Event * const e)
{
    #define MAX_STATE_EXIT_NESTS        3           /* TODO: Throw run-time error if max nested states is exceeded. Otherwise you'll have a stray pointer!! */
    #define MAX_STATE_ENTRY_NESTS       3           /* TODO: Throw run-time error if max nested states is exceeded. Otherwise you'll have a stray pointer!! */

    State * StartState = me->state;
    State * HandledState;
    Status status = HSM_DISPATCH_STATUS;

    /* Execute dispatched event in current state's Event Handler. Exits when event is handled. */
    while ( (status == SUPER_STATUS || status == HSM_DISPATCH_STATUS) )
    {
        HandledState = me->state;  /* Will hold the State that handled the event once this exits */
        status = (*me->state->hndlr)(me, e);
    }

    /* Did the dispatched event cause a State Transition? */
    if (status == TRAN_STATUS)
    {
        /* Was it a self-transition? */
        if (StartState == HandledState) 
        {
            (void)(*me->state->hndlr)(me, &exitEvent);
            (void)(*me->state->hndlr)(me, &entryEvent);
        }

        else
        {
            /* Declared here to try to reduce Stack allocation since this is only needed if a State Transition occurs. */
            State * entryPath[MAX_STATE_ENTRY_NESTS+1] = {NULL};
            State ** entryTrace = &entryPath[0];

            State * exitPath[MAX_STATE_EXIT_NESTS+1] = {NULL};
            State ** exitTrace = &exitPath[0];

            /**
             * Source State = state we just transitioned out of. Similar to the node of a tree.
             * Target State = state we just transitioned into. Similar to the node of a tree.
             * Top State = similar to the root of a tree
             * LCA = Least Common Ancestor. Lowest level state shared between two states.
             * 
             * We must find the LCA between the Source and Target State. This process is accomplished 
             * in a similar fashion to finding the LCA of a tree. However the path from the root 
             * to each node is not defined at compile-time to save memory. This path is determined
             * at run-time for the necessary states only if a transition occurs.
             * 
             * We start with the Source State (node) and trace up the State Hierarchy until we reach 
             * the Top State (root). This path is recorded in exitTrace. The same process is 
             * repeated for the Target State, with the path being recorded in entryTrace. 
             * 
             * We then traverse back down exitPath and entryPath. (From root to node).
             * After traversing down each level, we check if the current state in entryPath 
             * and exitPath are the same. If they are different we know that the LCA is the 
             * state one level above.
             * 
             * With this information, we now know the proper Exit and Entry paths to take
             * for the State Transition.
             * 
             */
            *exitTrace = TempState;
            *entryTrace = me->state;

            /* Trace up to the Top State */
            while ( ((*exitTrace)->superstate != NULL) && ((*entryTrace)->superstate != NULL) )
            {
                if ((*exitTrace)->superstate)
                {
                    *(exitTrace+1) = (*exitTrace)->superstate;
                    exitTrace++;
                }
                if ((*entryTrace)->superstate)
                {
                    *(entryTrace+1) = (*entryTrace)->superstate;
                    entryTrace++;
                }
            }

            /* Find LCA */
            while ( ((*exitTrace) == (*entryTrace)) )
            {
                bool exitTraversed = ((*exitTrace) != exitPath[0]) ? true : false;
                bool entryTraversed = ((*entryTrace) != entryPath[0]) ? true : false;

                if ( (exitTraversed == true) && (entryTraversed == true) )
                {
                    break;
                }
                else
                {
                    if (!exitTraversed)
                    {
                        exitTrace--;
                    }
                    if (!entryTraversed)
                    {
                        entryTrace--;
                    }
                }          
            }

            /* At this point we know our Entry and Exit paths. Traverse down each path then execute the Entry and Exit events for each state. */
            for ( (TempState = *exitTrace, *exitTrace = &entryPath[0]); (*exitTrace != TempState); (exitTrace++) )
            {
                (void)(*exitTrace)->hndlr(me, &exitEvent);
            }
            (void)(*exitTrace)->hndlr(me, &exitEvent);


            for (; *entryTrace != me->state; entryTrace--)
            {
                (void)(*entryTrace)->hndlr(me, &entryEvent);
            }
            (void)(*entryTrace)->hndlr(me, &entryEvent);
        }        
    }
}
