/**
 * @file Hsm.c
 * @author Template from Dr. Miro Samek, Quantum Leaps LLC. Adjustments for specific
 * application made by Ian Ress.
 * @brief Hierarchical State Machine Base Class
 * @date 2023-03-20
 * 
 */

#include <stdbool.h>
#include "Hsm.h"

#define NULL_STATE                      ((HsmState *)0)


/**
 * @brief The maximum number of nested states the Hsm can have. For example, if MAX_LEVELS
 * was set to 2:
 * 
 *  - State(A) -> State(A11) -> State(A111) is allowed since this is 2 nesting levels.
 * 
 *  - State(A) -> State(A11) -> State(A111) -> State(A1111) is not allowed since this is 3 nesting levels.
 * 
 * @note A user-definable run-time error will execute if the second scenario occurs.
 * 
 */
#define MAX_LEVELS                      3


static const Event entryEvent   = {ENTRY_EVENT};
static const Event exitEvent    = {EXIT_EVENT};


/**
 * @brief Runs the Initial Transition when Hsm_Begin() is called. This executes
 * the Initial State Handler function that is defined by the user. The Dispatcher
 * will determine the proper State Traversal and Entry Event sequence to execute.
 * 
 * @warning Within the supplied handler function, the user MUST transition into 
 * a State within their Hsm by calling @p HSM_TRAN(target_) macro. 
 * 
 * @note Calling @p HSM_INTERNAL_TRAN(target_) will be treated as if 
 * @p HSM_TRAN(target_) was called.
 * 
 * @param me Pointer to Hsm object.
 * @param inithndlr User-defined Initial State Handler function. See warning above.
 * 
 * @return True if the user properly defined the Initial State Handler function.
 * False otherwise.
 * 
 */
static bool Hsm_Init_Dispatch(Hsm * const me, const HsmInitStateHandler inithndlr);
static bool Hsm_Init_Dispatch(Hsm * const me, const HsmInitStateHandler inithndlr)
{
    bool success = false;
    HsmStatus status = (*inithndlr)(me); /* Execute Initial State Handler function */

    /* The Initial State Handler function must cause a State Transition. Return false if this does not enter. */
    if ( (status == HSM_TRAN_STATUS || status == HSM_INTERNAL_TRAN_STATUS) )
    {
        int levels = 0;
        HsmState * entryPath[MAX_LEVELS+1] = {NULL_STATE};
        HsmState ** entryTrace = &entryPath[0];

        /**
         * Find Entry Path. This is starting from the State you transitioned into up until the Top State.
         */
        for (HsmState * s = me->state; s != &me->top; s = s->superstate)
        {
            if (levels++ > MAX_LEVELS)
            {
                // TODO: throw run-time error
                return;
            }
            else
            {
                *(entryTrace++) = s; /* {0, Substate, Substate,...Substate of Top State}. This excludes Top State */
            }

        }

        /**
         * Execute Entry Events
         */
        (void)(*me->top.hndlr)(me, &entryEvent);
        for (; *entryTrace; entryTrace--)
        {
            (void)(*(*entryTrace)->hndlr)(me, &entryEvent);
        }
        success = true;
    }
    return success;
}


/**
 * @brief Initializes a State within the Hsm. 
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
void HsmState_Ctor(HsmState * const me, const HsmState * const superstate, const HsmStateHandler hndlr)
{
    me->superstate = superstate;
    me->hndlr = hndlr;
}


/**
 * @brief Hsm Base Class Constructor. Initializes the Top-most State of the Hsm. The
 * Superstate of this is NULL.
 * 
 * @warning Unless explicitly defined beforehand by the user, note that me->state is
 * still a NULL pointer.
 * 
 * @param me Pointer to Hsm object.
 * @param tophndlr Function that executes when the Hsm is in the Top-most State.
 * 
 */
void Hsm_Ctor(Hsm * const me, const HsmStateHandler tophndlr)
{
    State_Ctor(&me->top, (HsmState *)0, tophndlr);
}


/**
 * @brief Sets the Hsm's State to the user-defined Initial State. If
 * the Initial State object is defined correctly, the Initial State Handler
 * function will execute. The Hsm Dispatcher will determine the proper
 * State Traversal and Entry Event sequence to execute.
 * 
 * @warning @p HSM_Ctor() MUST be called beforehand.
 * 
 * @warning Within the Initial State Handler function, the user MUST 
 * transition into a State within their Hsm by calling @p HSM_TRAN(target_) 
 * macro. If this is not followed, then the Initial State Handler 
 * function will execute and the Hsm will remain in a pending (not started)
 * state. This function will return false if this occurs. 
 * 
 * PLEASE NOTE THIS DOES NOT SUPPORT TRANSITION EVENTS IN THE ENTRY AND
 * EXIT EVENTS OF THE HSM
 * 
 * @param me Pointer to Hsm object.
 * @param initstate The Initial State the user wants assigned to the Hsm.
 * 
 * @return True if the Hsm successfully started. This means the user supplied
 * a correctly defined Initial State object and called Hsm_Ctor() before
 * calling this routine. False otherwise.
 * 
 */
bool Hsm_Begin(Hsm * const me, const HsmState * const initstate)
{
    bool success = false;

    /* Hsm_Ctor called beforehand and Initial State defined correctly by user. */
    if ( ((me->top).hndlr != (HsmStateHandler)0) && (initstate != (HsmState *)0) && (initstate->hndlr != (HsmStateHandler)0) )
    {
        success = Hsm_Init_Dispatch(me, initstate->hndlr);
    }
    return success;
}


/**
 * @brief Runs the Hsm. If a state transition takes place, the dispatcher
 * determines the entry and exit paths and executes the Entry and Exit
 * Events of the appropriate states.
 * 
 * @warning Do not execute this in multiple threads. If you need multiple
 * threads or ISRs to dispatch events to the Hsm, add the event to a queue.
 * In a separate thread pass each member of the queue one-by-one to the 
 * dispatcher.
 * 
 * @param me Pointer to Hsm object.
 * @param e Event Signal dispatched to the Hsm.
 * 
 */
void Hsm_Dispatch(Hsm * const me, const Event * const e)
{
    HsmState * const StartState = me->state;
    HsmState * HandledState = me->state; /* Stores the state that handled the dispatched event. */

    /* Execute dispatched event in current state's Event Handler. Exits when event is handled. */
    HsmStatus status = (*me->state->hndlr)(me, e);
    while (status == HSM_SUPER_STATUS)
    {
        HandledState = me->state;
        status = (*me->state->hndlr)(me, e);
    }

    /* Did the dispatched event cause a State Transition? */
    if ( (status == HSM_TRAN_STATUS || status == HSM_INTERNAL_TRAN_STATUS) )
    {
        /* Declared here to try to reduce Stack allocation since this is only needed if a State Transition occurs. */
        int levels = 0;
        HsmState * LCA;
        HsmState * s;
        
        HsmState * entryPath[MAX_LEVELS+1] = {NULL_STATE};
        HsmState ** entryTrace = &entryPath[0];

        HsmState * exitPath[MAX_LEVELS+1] = {NULL_STATE};
        HsmState ** exitTrace = &exitPath[0];

        /**
         * Source State = state we just transitioned out of. Similar to the node of a tree.
         * Target State = state we just transitioned into. Similar to the node of a tree.
         * Top State = similar to the root of a tree
         * LCA = Least Common Ancestor. Lowest level state shared between two states.
         * Leaf State = state that has no substates. (state with no children).
         * 
         * We must figure out the correct order of Entry and Exit events to run for each state
         * if a transition occured.
         * 
         * We do this by finding the LCA between the Source and Target State, which is 
         * similar to finding the LCA of a tree. However the path from the root (Top State)
         * to each node (Target/Source States) is not defined at compile-time to save memory. 
         * This is calculated here at run-time for only the nodes of interest (Source and Target
         * States). 
         * 
         * Only the path from node to root is defined at compile-time since each 
         * node can only have one parent (superstate).
         * Therefore we start with the Source State and trace up the State Hierarchy 
         * until we reach the Top State. This path is recorded in exitTrace. The same 
         * process is repeated for the Target State, with the path being recorded in entryTrace. 
         * 
         * With the path from root to node now known, we follow the standard LCA algorithm if
         * a State to State Transition occured. We traverse back down exitPath and entryPath. 
         * (From root to node). After traversing down each level, we check if the current 
         * state in entryPath and exitPath are the same. If they are different we know 
         * that the LCA is the state one level above.
         * 
         * For Nested State Transitions, the LCA will be the highest level State from
         * the following list: the State that handled the dispatched event, the Source State, 
         * or the Target State. 
         * 
         * The order of Exit Events will be from the Source State up to the LCA.
         * The order of Entry Events will be from the LCA to the Target State.
         * 
         */

        /**
         * Trace up to Top State
         */
        for ( s = StartState; s != NULL_STATE; s = s->superstate )
        {
            if (levels++ > MAX_LEVELS)
            {
                // TODO: throw run-time error
                return;
            }
            else
            {
                *(exitTrace++) = s; /* {0, StartState, ...TopState} */ 
            }
        }

        levels = 0;
        for ( s = me->state; s != NULL_STATE; s = s->superstate )
        {
            if (levels++ > MAX_LEVELS)
            {
                // TODO: throw run-time error
                return;
            }
            else
            {
                *(entryTrace++) = s; /* {0, CurrentState, ...TopState} */ 
            }
        }


        /**
         * Find LCA
         */
        while ( (*exitTrace == *entryTrace) && (*exitTrace != &exitPath[1]) && (*entryTrace != &entryPath[1]) && (*exitTrace != HandledState) && (*entryTrace != HandledState) )
        {
            exitTrace--;
            entryTrace--;
        }

        LCA = (*exitTrace)

        if ( (*exitTrace == *entryTrace) && (status == HSM_INTERNAL_TRAN_STATUS) ) /* Nested, Internal State Transition. See INTERNAL_TRAN(target_) macro */
        {
            LCA = (*exitTrace); /* Same as (*entryTrace) */
        }
        else /* State to State Transition. */
        {
            LCA = (*exitTrace)->superstate; /* Same as (*entryTrace)->superstate. */
        }


        /**
         * Execute Exit and Entry Events
         */
        if (LCA)
        {
            for ( s = StartState; s != LCA; s = s->superstate )
            {
                (void)(*s->hndlr)(me, &exitEvent);
            }

            for ( s = *entryTrace; s; s = *(entryTrace--) )  /* Recall first element of entryTrace is (HsmState *)0 */
            {
                (void)(*s->hndlr)(me, &entryEvent);
            }
        }
        else
        {
            // TODO: throw run-time error
        }





        /**
         * At this point we know our Entry and Exit paths. Execute Exit and Entry Events
         */
        for ( entryTrace = &entryPath[0]; *entryTrace != LCA; entryTrace++ ){} /* Find Entry startpoint */
        if ( *entryTrace != &entryPath[0] )
        {
            entryTrace--;
        }

        for ( exitTrace = &exitPath[0]; *exitTrace != LCA; exitTrace++ ) /* Exit Events are executed from the Source State up to the LCA. */
        {
            (void)(*(*exitTrace)->hndlr)(me, &exitEvent);
        }

        for ( ; entryTrace != &entryPath[0]; entryTrace-- ) /* Entry Events are executed from the LCA to the Target State. */
        {
            (void)(*(*entryTrace)->hndlr)(me, &entryEvent);
        }
        (void)(*me->state->hndlr)(me, &entryEvent);
    }
}
