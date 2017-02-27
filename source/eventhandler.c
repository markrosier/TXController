//************************************************************************
// 
// eventhandler.c
// handles event related functions
//
// Iota Electronics Limited 2017
//
//************************************************************************

#include "system.h"
#include "timer.h"
#include "hardware.h"
#include "eventhandler.h"
#include "timer.h"
#include "led.h"


BYTE eventHandlerTimer = 0;
enum events lastEvent = INITIALISING_TX;

void initIOCInterrupt( void )
{
  INTCONbits.GIE = 1;
  IOCANbits.IOCAN3 = 1;
  INTCONbits.IOCIF = 0;
  INTCONbits.IOCIE = 1;
  INTCONbits.PEIE = 1;
}

void resetIOCInterrupt( void )
{
  IOCAFbits.IOCAF3 = 0;
  INTCONbits.PEIE = 1;
}

void IOCInterrupt( void )
{
  if ( INTCONbits.IOCIF == 1)
  {
    // check P9242 Buzzer line
    if (IOCAFbits.IOCAF3 == 1)
    {
      
      // do something
      INDICATOR1_PIN_LATCH ^= 1;

      IOCAFbits.IOCAF3 = 0;
    }
  }
}


void eventHandlerInit ()
{
  eventHandlerTimer = timerGet ();
  timerSet( eventHandlerTimer, EVENT_HANDLER_PERIOD );
  initIOCInterrupt();
  setEvent( INITIALISING_TX );
}

void eventHandlerService ()
{
  if ( timerRead(eventHandlerTimer) == EXPIRED )
  {
    newEvent = getNewEvent ();

    if (((newEvent >= 0) && (newEvent < MAX_EVENTS))
    && ((currentState >= 0) && (currentState < MAX_STATES))) {

        stateTable [currentState][newEvent] ();

    } else 
    {
      // Invalid State just start again
      currentState = INITIALISE;
    }

    timerSet( eventHandlerTimer, EVENT_HANDLER_PERIOD );
  }
}

void action_s1_e1 (void)
{
    /* do some processing here */

    currentState = STATE_2; 
}

void action_s1_e2 (void) {} 
void action_s2_e1 (void) {}
void action_s2_e2 (void) {}
void action_s3_e1 (void) {}
void action_s3_e2 (void) {}


enum events getNewEvent (void)
{
    return EVENT_1;
}

void setEvent ( enum events envent) {
  lastEvent = envent;
}

