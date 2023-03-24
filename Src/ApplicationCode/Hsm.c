/**
 * @file Hsm.c
 * @author Dr. Miro Samek, Quantum Leaps LLC 
 * @brief Hierarchical State Machine and Event Base Class
 * @date 2023-03-20
 * 
 */

 /*TODO: STOPPED HERE FOR THE NIGHT - PICK UP 3/20*/
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



// /**
//  * @brief Hsm Base Class constructor.
//  * 
//  * @param me Pointer to Hsm object.
//  * @param initial Function that executes when the Hsm is first initialized (Initial Transition).
//  * Ensure this function calls the TRAN(target) macro to transition to the next state.
//  * 
//  */
// void Hsm_Ctor(Hsm * const me, StateHandler initial)
// {
//     me->state = initial;
// }


// /**
//  * @brief Executes Initial Transition function assign in Hsm_Ctor(). Then
//  * executes the entry event of the next state transitioned into.
//  * 
//  * @param me Pointer to Hsm object.
//  * @param e Event Signal dispatched to the Hsm when it is first initialized.
//  * 
//  */
// void Hsm_Init(Hsm * const me, const Event * const e)
// {
//     if (me->state != (StateHandler)0) /* TODO: Replace with run-time error handler */
//     {
//         (*me->state)(me, e); /* Execute Initial Transition function assigned in Hsm_Ctor. */
//         (*me->state)(me, &entryEvent); /* Execute entry event of the the next state transitioned into. */
//     }
// }



/**
 * @brief Called to locate the LCA when a state transition occurs in the Hsm. The Source
 * State Hierarchy is traversed until:
 * 
 *  -   The Top State is reached. If this occurs, we traverse up one level of the Target State hiearchy and
 *      repeat the process. If both the Source and Target hierarchy traversal reaches the Top State, then the LCA
 *      is the Top State.
 * 
 *  -   The Source State we traversed up to equals the current Target State. If this occurs, the LCA
 *      is whatever this state is.
 * 
 * @param source Source State we just transitioned out of.
 * @param target Target State we just transitioned into.
 * @return State* Pointer to LCA. LCA = Least Common Ancestor. This is the first state 
 * shared between the Source and Target State. This is needed to determine the entry 
 * and exit path of the Hsm when a state transition occured.
 * 
 */
static inline State * LocateLCA(State * source, State * target);
static inline State * LocateLCA(State * source, State * target)
{
    State * LCA = NULL;

    for (; target; target = target->superstate )
    {
        for (; source; source = source->superstate )
        {
            if (source == target)
            {
                LCA = source;
                break;
            }
        }
    }

    if (!LCA)
    {
        // Throw error. LCA not able to be found
    }

    return LCA;
}



/**
 * @brief Runs the Hsm. If a state transition takes place, the dispatcher
 * automatically runs the Exit Event of the previous state and the Entry
 * Event of the state transitioned into.
 * 
 * @param me Pointer to Hsm object.
 * @param e Event Signal dispatched to the Hsm.
 * 
 */
void Hsm_Dispatch(Hsm * const me, const Event * const e)
{
    #define MAX_STATE_EXIT_NESTS        3           /* TODO: Throw run-time error if max nested states is exceeded. Otherwise you'll have a stray pointer!! */
    #define MAX_STATE_ENTRY_NESTS       3           /* TODO: Throw run-time error if max nested states is exceeded. Otherwise you'll have a stray pointer!! */

    State * TempState = me->state;
    Status status = HSM_DISPATCH_STATUS;

    /* Always record Exit Trace for convenience. Will only need if a State Transition takes place. */
    for ( ; (status == SUPER_STATUS || status == HSM_DISPATCH_STATUS); ) /* Exit when event is handled. */
    {
        status = (*me->state->hndlr)(me, e); /* Execute dispatched event in current state's Event Handler. */
    }





    // /* Always record Exit Trace for convenience. Will only need if a State Transition takes place. */
    // for ( *exitTrace = me->state; (status == SUPER_STATUS || status == HSM_DISPATCH_STATUS); *(++exitTrace) = me->state ) /* Exit when event is handled. */
    // {
    //     status = (*me->state->hndlr)(me, e); /* Execute dispatched event in current state's Event Handler. */
    // }

    if (status == TRAN_STATUS)
    {
        /* Declared here to try to reduce Stack allocation since this is only needed if a State Transition occurs. */
        /* TODO: Possibly declare at compile-time? */
        State * entryPath[MAX_STATE_ENTRY_NESTS] = {NULL};
        State ** entryTrace = entryPath;

        State * exitPath[MAX_STATE_EXIT_NESTS] = {NULL};
        State ** exitTrace = exitPath;


        /**
         * LCA = Least Common Ancestor
         * Source State = state we just transitioned out of
         * Target State = state we just transitioned into
         * 
         * We must find the LCA between the Source and Target State. This process is accomplished in a similar fashion
         * to finding the LCA of a binary tree. However we don't have the path of each state defined at compile-time in order
         * to preserve memory. Therefore this is calculated at run-time, only when a State Transition occurs. 
         * 
         * In this case, we start with the Source State and trace back up the State Hierarchy until we reach the Top State. 
         * This path is recorded in exitTrace. The same process is repeated for the Target State, with the path being 
         * recorded in entryTrace. 
         * 
         * We then start traversing through exitPath and entryPath. This is traversing from the Top State back to 
         * the Target and Source State. After traversing down each level, we check if the current state in entryPath 
         * and exitPath are the same. If they are different we know that the LCA is the state one level above.
         * 
         */

        *exitTrace = TempState;
        *entryTrace = me->state;

        while ( (*exitTrace) != NULL && (*entryTrace != NULL) )
        {
            if (*exitTrace)
            {
                *(++exitTrace) = (*exitTrace)->superstate;
            }
            if (*entryTrace)
            {
                *(++entryTrace) = (*entryTrace)->superstate;
            }
        }

        exitTrace--;
        entryTrace--;


        for ( (*exitTrace = TempState, *entryTrace = me->state); (); )
        {
            if (*exitTrace)
            {
                *(++exitTrace) = (*exitTrace)->superstate;
            }
            if (*entryTrace)
            {
                *(++entryTrace) = (*entryTrace)->superstate;
            }
        }

        /* For loop initialization traverses back by one leavl because traces will currently be pointed to Superstate of the Top State which is NULL. */
        for ( (); (*exitTrace != *entryTrace); (exitTrace++, entryTrace++) )
        {

        }



        exitTrace = &exitPath[0];

        // *exitTrace = 0;     /*  At this point exitPath stores the correct Exit Path besides the last added element. The last added
        //                         element contains the state we just transitioned into. We clear this because this is not apart of the
        //                         Exit Path. This State will also already be stored in me->state if we ever need it. */

        State * LCA = LocateLCA(exitPath[0], me->state); /* Find LCA between state we transitioned out of and state we transitioned into. */

        /* Cannot set entryTrace equal to me->state in the iterator because me->state is no longer updating. */
        for ( (*entryTrace = me->state); ( (*entryTrace) && (*entryTrace != LCA) ); (*entryTrace = *entryTrace->superstate) )
        {

        }

        for ( ; (*exitTrace != me->state); exitTrace++ )
        {
            (void)(*exitTrace)->hndlr(me, &exitEvent);
        }

        for ( ; (*entryTrace != me->state); entryTrace-- )
        {
            (void)(*entryTrace)->hndlr(me, &entryEvent);
        }
    }
}
