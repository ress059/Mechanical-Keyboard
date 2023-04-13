/**
 * @file Hsm.c
 * @author Dr. Miro Samek, Quantum Leaps LLC 
 * @brief Hierarchical State Machine and Event Base Class
 * @date 2023-03-20
 * 
 */

#include <stdbool.h>
#include "Hsm.h"

/**
 * @brief The Superstate of the Hsm's Top State (root) is always set to this NULL value.
 * This is used as an identifier for the Top State.
 * 
 */
#define NULL_STATE                      ((State *)0)


/**
 * @brief The maximum number of nested states the Hsm can have. For example, if MAX_LEVELS
 * was set to 2:
 * 
 *  - State(A) -> State(A11) -> State(A111) is allowed since this is 2 nesting levels.
 * 
 *  - State(A) -> State(A11) -> State(A111) -> State(A1111) is not allowed since this is 3 nesting levels.
 * 
 * @note If the second scenario occurs, a run-time error will execute if you are currently 
 * in State A1111 and an event defined in State A is dispatched to the Hsm. The user will 
 * be notified of the Source State (A1111) and the Target State (A) combination that resulted 
 * in the error.
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
 * @warning The user MUST transition into a State within the Hsm by calling
 * @p HSM_TRAN(target_) macro. Calling @p HSM_INTERNAL_TRAN(target_) will be
 * treated as if @p HSM_TRAN(target_) was called.
 * 
 * @param me Pointer to Hsm object.
 * @param inithndlr User-defined Initial State Handler function. See warning above.
 * 
 * @return true if the user properly defined the Initial State Handler Function,
 * false otherwise.
 * 
 */
static void Hsm_Init_Dispatch(Hsm * const me, const InitStateHandler inithndlr);
static void Hsm_Init_Dispatch(Hsm * const me, const InitStateHandler inithndlr)
{
    bool success = false;
    Status status = (*inithndlr)(me); /* Execute Initial State Handler function */

    /* The Initial State Handler function must cause a State Transition. Return false if this does not enter. */
    if ( (status == TRAN_STATUS || status == INTERNAL_TRAN_STATUS) )
    {
        int levels = 0;
        State * entryPath[MAX_LEVELS+1] = {NULL_STATE};
        State ** entryTrace = &entryPath[0];

        /**
         * Find Entry Path. This is the State you transitioned into up to the Top State.
         */
        for (State * s = me->state; s != &me->top; s = s->superstate)
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
void State_Ctor(State * const me, State * const superstate, const StateHandler hndlr)
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
void Hsm_Ctor(Hsm * const me, const StateHandler tophndlr)
{
    State_Ctor(&me->top, (State *)0, tophndlr);
}


/**
 * @brief Sets the Hsm's State to the user-defined Initial State. If
 * the Initial State object is defined correctly, the Initial State Handler
 * function will execute. The Hsm Dispatcher will determine the proper
 * State Traversal and Entry Event sequence to execute.
 * 
 * @warning @p HSM_Ctor() must be called beforehand.
 * 
 * @warning In the Initial State Handler function, the user MUST define a 
 * @p HSM_ENTRY_EVENT case. Within this, the user must transition to
 * a State within the Hsm by calling the @p HSM_INIT(target_) macro. Do 
 * not use the @p HSM_TRAN(target_) or @p HSM_INTERNAL_TRAN(target_) macros 
 * within the Initial State Handler. If this is not followed, the Hsm
 * will have undefined behavior. 
 * 
 * @param me Pointer to Hsm object.
 * @param initstate The Initial State the user wants assigned to the Hsm.
 * 
 * @return true if the Hsm successfully started, false otherwise.
 * 
 */
bool Hsm_Begin(Hsm * const me, const State * const initstate)
{
    bool success = false;

    if ( ((me->top).hndlr != (StateHandler)0) && (initstate != (State *)0) && (initstate->hndlr != (StateHandler)0) ) /* Hsm_Ctor called beforehand and Initial State defined correctly by user. */
    {
        me->state = initstate;
        Hsm_Dispatch(me, &entryEvent);   /* Execute Initial Transition function assigned in Hsm_Ctor and relevant State Entry Events. */
        success = true;
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
    State * const StartState = me->state;
    Status status = HSM_DISPATCH_STATUS;
    State * HandledState;   /* Stores the state that handled the dispatched event. */

    /* Execute dispatched event in current state's Event Handler. Exits when event is handled. */
    while ( (status == SUPER_STATUS || status == HSM_DISPATCH_STATUS) )
    {
        HandledState = me->state;
        status = (*me->state->hndlr)(me, e);
    }

    /* Did the dispatched event cause a State Transition? */
    if ( (status == TRAN_STATUS || status == INTERNAL_TRAN_STATUS) )
    {
        /* Declared here to try to reduce Stack allocation since this is only needed if a State Transition occurs. */
        State * LCA;
        
        State * entryPath[MAX_LEVELS+1] = {NULL_STATE};
        State ** entryTrace = &entryPath[0];

        State * exitPath[MAX_LEVELS+1] = {NULL_STATE};
        State ** exitTrace = &exitPath[0];

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
        *exitTrace = StartState;
        *entryTrace = me->state;


        /**
         * Trace up to the Top State
         */
        for (   int levels = 0; \
                ( ((*exitTrace)->superstate != NULL_STATE) && ((*entryTrace)->superstate != NULL_STATE) ); \
                levels++    )
        {
            if (levels >= MAX_LEVELS)
            {
                // Throw run-time error here since we can notify user of guilty state combination that caused the error.
                // Source State = StartState
                // Target State = me->state 
                return;
            }
            else
            {
                if ( (*exitTrace)->superstate != NULL_STATE )
                {
                    *(exitTrace+1) = (*exitTrace)->superstate;
                    exitTrace++;
                }
                if ( (*entryTrace)->superstate != NULL_STATE )
                {
                    *(entryTrace+1) = (*entryTrace)->superstate;
                    entryTrace++;
                }
            }
        }


        /**
         * Find LCA
         */
        while ( ((*exitTrace == *entryTrace) && (exitTrace != &exitPath[0]) && (entryTrace != &entryPath[0]) && (*exitTrace != HandledState) && (*entryTrace != HandledState)) )
        {
            exitTrace--;
            entryTrace--;
        }

        if ( (*exitTrace == *entryTrace) && (status == INTERNAL_TRAN_STATUS) ) /* Nested, Internal State Transition. See INTERNAL_TRAN(target_) macro */
        {
            LCA = (*exitTrace); /* Same as (*entryTrace) */
        }
        else /* State to State Transition. */
        {
            LCA = (*exitTrace)->superstate; /* Same as (*entryTrace)->superstate. */
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
