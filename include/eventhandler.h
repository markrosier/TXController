#ifndef inc_eventhandler
#define inc_eventhandler

//****************************************************************************
//
//  eventhandler.h
//
//  Iota Electronics Limited 2016
//
//****************************************************************************

void initKeyInterrupt( void );
void resetKeyInterrupt( void );
void initChargerAttachedInterrupt( void );
void resetChargerAttachedInterrupt( void );
void chargerAttachedInterrupt( void );
void keyInterrupt( void );
void switchOff( void );
void switchOn( void );
void gotoSleep( void );
void eventHandlerInit( void );
void eventHandlerService( void );

#define EVENT_HANDLER_PERIOD    100
#define DEBOUNCE_PERIOD 50

#define OFF_BUTTON_TIMEOUT     9000  // 9 seconds
#define OFF_TIMEOUT             5000 // 5 seconds

enum eOnState { onStateOn, 
                onStateWaitingforOff, 
                onStateWaitingforOffRequest, 
                onStateOffWaitingforKeyRelease, 
                onStateOnWaitingforRequestRelease,
                onStateOnWaitingforKeyRelease, 
                onStateOff};


#endif
