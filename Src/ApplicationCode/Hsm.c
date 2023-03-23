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
    #define MAX_STATE_NESTS     10

    State *s;
    Status status = HSM_DISPATCH_STATUS;
    
    State *path[MAX_STATE_NESTS] = {(void*)0};
    State **trace = path;
    State *LCA; /*  Least Common Ancestor. This is the first state shared between the Source and Target State.
                    Used to determine (if needed) the entry and exit path of the Hsm when a state transition occured. */


    State *exitPath[MAX_STATE_NESTS];
    State *entryPath[MAX_STATE_NESTS];

    



    for ( (s = me->state); (status == SUPER_STATUS || status == HSM_DISPATCH_STATUS); (s = s->superstate) ) /* Exit when status isn't SUPER_STATUS */
    {

        status = (*me->state->hndlr)(me, e); /* Execute dispatched event in current state's Event Handler. */
    }
    LCA = s;

    if (status == TRAN_STATUS)
    {

    }

    s = (me->state);
    status = (*me->state->hndlr)(me, e); /* Execute dispatched event in current state's Event Handler. */

    if (status == SUPER_STATUS || status == TRAN_STATUS)
    {
        /* traverse up */
        /* break when status = ignored or handled */
        for ( s; status != SUPER_STATUS; (s = me->state) )
        {

        }
    }

    /* TODO This finds the EXIT PATH. Must find ENTRY PATH as well */
    while (status == SUPER_STATUS) /* Will get stuck in here if number of nested states is greater than MAX_STATE_NESTS */
    {
        /* Traverse state hierarchy until the event is reached */
        if (i++ < MAX_STATE_NESTS)
        {
            LCA = (me->state->superstate);
            exitPath[i] = (me->state);
            status = (*me->state->hndlr)(me, e); /* Exits when event is handled. *****LCA WILL BE ONE STATE ABOVE statetree[i] WHEN WHILE LOOP EXITS******/
        }
    }

    /* TODO This finds the EXIT PATH. Must find ENTRY PATH as well */
    if (status == TRAN_STATUS)
    {

        /* Find the entry path. This is the path from the target state up to the LCA. */
        for ( (s = me->state); (s->superstate != LCA); (s = s->superstate) )
        {
            entryPath[j] = s;
            j++;
        }

        for (i = 0; exitPath[i]; i++) /* Runs exit events up to LCA */
        {
            (*exitPath[i]->hndlr)(me, &exitEvent);
        }

        for (j = 0; entryPath[j]; j++)
        {}

        for (j-1; j != 0; j--)
        {
            (*entryPath[j]->hndlr)(me, &entryEvent);
        }
    }



    /* 
    0) if status == SUPER_STATUS 

    1) When transition occurs, there will be a source state (state your transitioning out of) and
    target state (state you're transitioning into).
    
    2) Must find LCA between these two states

    3) Exit Path = source state to LCA

    4) Entry Path = LCA to target state 

    */


    /**
     * Example: In state A11. Press event dispatched, transitioning state A11 to B11. Have to go up to A1 and cut through B1
     * 
     * 1)
     * i = 0
     * exitPath[0] = A11_State
     * default case of A11_State executes. SUPER(A1_State)
     * status = SUPER_STATUS
     * me->state = A1_State
     * 
     * 2)
     * While loop enters
     * i = 1
     * *****LCA = A1_State->superstate = A;*****
     * exitPath[1] = A1_State
     * PRESS_EVENT executes in A1_State handler. TRAN(B11_State)
     * status = TRAN_STATUS
     * me->state = B11_State
     * while loop exits
     * 
     * 3)
     * if statement enters
     * s = me->state = B11_State
     * 
     * for loop enters
     * j = 0
     * entryPath[0] = me->state = B11_State
     * 
     * j = 1
     * s = me->state->superstate = B1_State
     * entryPath[1] = B1_State
     * 
     * j = 2
     * s->superstate = B1_State->superstate = A = LCA. So forloop exits
     * 
     * 4)
     * exitPath[0] exit event = A11_State Exit executes
     * exitPath[1] exit event = A1_State Exit executes
     * exitPath[2] empty. for loop exits
     * 
     * SHOULD BE REVERSED
     * entryPath[0] entry event = B11_State entry executes
     * entryPath[1] entry event = B1_State entry executes
     * 
     * 
     * 
     * PRESS_EVENT of A1_State runs. TRAN(B11)
     * status = TRAN_STATUS
     * me->state = B11_State
     * 
     * 2) while loop doesnt enter
     * 
     * 3) if statement enters
     * 
     * for loop enters
     * statetree[0] = A1_State exit event runs
     * 
     * TODO: DOESN'T RUN B1 ENTRY EVENT
     * B11_State Entry Event runs.
     * 
     */




    /**
     * Example: Operational state, REQ_POWER_CYCLE event dispatched
     * 
     * 1)
     * i = 0
     * statetree[0] = Operational_State
     * Default case of Operational_State runs. SUPER(USB_Hsm_State)
     * status = SUPER_STATUS
     * me->state = USB_Hsm_State
     * 
     * 2) while loop enters
     * i = 1
     * statetree[1] = USB_Hsm_State
     * REQ_POWER_CYCLE event in USB_Hsm_State runs. TRAN(Error_State).
     * status = TRAN_STATUS
     * me->state = Error_State
     * while loop exits
     * 
     * 3) if statement enters
     * for loop enters
     * statetree[0] = Operational_State Exit Event runs
     * statetree[1] = USB_Hsm_State Exit Event runs
     * for loop ends since statetree[2] empty
     * 
     * Error State Entry Event runs
     * 
     */

}
