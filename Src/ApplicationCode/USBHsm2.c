
/* MOST OF THIS WILL ALL BE CONTAINED IN HSM.H CAN EDIT AFTER PR */
#include <stdint.h>

typedef uint16_t Signal;
typedef struct Hsm Hsm;

typedef struct
{
    Signal sig;
} Event;

typedef enum
{
    ENTRY_SIG,
    EXIT_SIG,
    USER_SIG
} ReservedSignals;

typedef enum
{
    TRAN_STATUS,
    HANDLED_STATUS,
    IGNORED_STATUS,
    INIT_STATUS,
    SUPER_STATUS,       /* Transitioned to superstate */
    TOP_STATUS          /* Reached top state */
} Status;


typedef Status (*EventHandler)(Hsm * const me, const Event * const e);

/* Will define three State structs. Pre-operational state, Operational State, and Error State */
typedef struct 
{
    State *superstate;                          /* pointer to superstate above the current state. E.g. If A11 is nested in A1, superstate of A11 would be A1.
                                                superstate of A1 would be NULL. */
    EventHandler evt;                             /* state's handler function */
} State;

// typedef struct
// {
//     State *child;             /* Substate. If State struct is for a Leaf State, this will be NULL. */
//     State *parent;            /* Superstate. If State struct is for Hsm Top, this will be NULL. */
//     EvtHndlr evt;             /* Event Handler associated with State */
// } State;

// /* E.g. for Pre-op state */
// State USBState =
// {
//     ((void*)0),
//     &USBState;
//     &PreOperationalEvtHndlr;
// };

// State PreOperational =
// {
//     ((void*)0),
//     &USBState;
//     &PreOperationalEvtHndlr;
// };


struct Hsm {                       /* Hierarchical State Machine base class */
    // State *curr;                                           /* current state */
    // State *next;                  /* next state (non 0 if transition taken) */
    // State *source;                   /* source state during last transition */
    // State top;                                     /* top-most state object */
    State *state;    /* Current state */
    // const State super;    /* Super state. This will be Hsm top */
};
/* MOST OF THIS WILL ALL BE CONTAINED IN HSM.H CAN EDIT AFTER PR */

static const Event entryEvt = {&ENTRY_SIG};
static const Event exitEvt  = {&EXIT_SIG};



/**
 * @brief Does NOT support entry through multiple substates. E.g. A->B->C->D.
 * 
 * If you are in State A and transition to State D, entry events of State B and State C will not run
 * 
 * @param me 
 * @param e 
 */
static void USBHsm_Dispatch(Hsm * const me, const Event * const e);
static void USBHsm_Dispatch(Hsm * const me, const Event * const e)
{
    #define MAX_STATE_NESTS     2
    /* TOOD: Cleanup */
    uint8_t i = 0; /* entryPath index */
    uint8_t j = 0; /* exitPath index */
    Status status;
    State * exitPath[MAX_STATE_NESTS];
    State * entryPath[MAX_STATE_NESTS]

    exitPath[0] = (me->state);
    status = (*me->state->evt)(me, e); /* Execute dispatched event in current state */

    /* TODO This finds the EXIT PATH. Must find ENTRY PATH as well */
    while (status == SUPER_STATUS) /* Will get stuck in here if number of nested states is greater than MAX_STATE_NESTS */
    {
        /* Traverse state hierarchy until the event is reached */
        if (i++ < MAX_STATE_NESTS)
        {
            exitPath[i] = (me->state);
            status = (*me->state->evt)(me, e); /* Exits when event is handled. *****LCA WILL BE ONE STATE ABOVE statetree[i] WHEN WHILE LOOP EXITS******/
        }
    }
    /* TODO This finds the EXIT PATH. Must find ENTRY PATH as well */

    if (status == TRAN_STATUS)
    {
        State *LCA = me->state->superstate;
        State *s = me->state;
        /* Find the entry path. This is the path from the target state up to the LCA. */

        
        while (s->superstate != LCA)
        {
            entryPath[j] = s;
            s = s->superstate;
            j++;
        }

        for (s = me->state; s != LCA; (s = me->state->superstate; j++))
        {
            entryPath[j] = s;
        }


        for (i = 0; exitPath[i]; i++) /* Runs exit events up to LCA */
        {
            (*exitPath[i])(me, &exitEvt);
        }

        // (*me->state)(me, &entryEvt);
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
     * Example: In state A1. Press event dispatched, transitioning state A1 to B11, cutting through B1
     * 
     * 1)
     * i = 0
     * statetree[0] = A1_State
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