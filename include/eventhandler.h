#ifndef inc_eventhandler
#define inc_eventhandler

//****************************************************************************
//
//  eventhandler.h
//
//  Iota Electronics Limited 2017
//
//****************************************************************************

void initIOCInterrupt( void );
void resetIOCInterrupt( void );
void IOCInterrupt( void );
void eventHandlerInit( void );
void eventHandlerService( void );

#define EVENT_HANDLER_PERIOD    100

// State Machine stuff
enum states { INITIALISE, STATE_2, STATE_3, MAX_STATES } currentState;
enum events { INITIALISING_TX, EVENT_1, MAX_EVENTS } newEvent;


void action_s1_e1 (void);
void action_s1_e2 (void);
void action_s2_e1 (void);
void action_s2_e2 (void);
void action_s3_e1 (void);
void action_s3_e2 (void);
enum events getNewEvent (void);
void setEvent( enum events event);


void (*const stateTable [MAX_STATES][MAX_EVENTS]) (void) = {

    { action_s1_e1, action_s1_e2 }, /* procedures for state 1 */
    { action_s2_e1, action_s2_e2 }, /* procedures for state 2 */
    { action_s3_e1, action_s3_e2 }  /* procedures for state 3 */
};




#endif
