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
#include "beeper.h"


BYTE eventHandlerTimer = 0;
enum initEvents lastEvent = noEvent;
int initSMTimer = 0;  //timer used by init state machine

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
      //INDICATOR1_PIN_LATCH ^= 1;

      IOCAFbits.IOCAF3 = 0;
    }
  }
}


void eventHandlerInit ()
{
  eventHandlerTimer = timerGet ();
  timerSet( eventHandlerTimer, EVENT_HANDLER_PERIOD );
  initIOCInterrupt();
  initSMTimer = timerGet ();
  reInit();
}

void eventHandlerService ()
{
  if ( timerRead(eventHandlerTimer) == EXPIRED )
  {
    initEvent = getInitEvent ();

    if (((initEvent >= 0) && (initEvent < maxInitEvents))
    && ((initState >= 0) && (initState < maxInitStates))) {

        initStateTable [initState][initEvent] ();

    } else 
    {
      // Invalid State just start again
        reInit();
    }

    timerSet( eventHandlerTimer, EVENT_HANDLER_PERIOD );
  }
}


void noAction (void) 
{
    // do nothing
}

void reInit (void)
{
  timerSet( initSMTimer, 100 * MILLISECONDS );
  ENABLE_TX_PIN_LATCH = DISABLE_TX;
  initState = initS1;
}

void initS1_Timeout (void)
{
  timerSet( initSMTimer, 100 * MILLISECONDS );
  ENABLE_TX_PIN_LATCH = ENABLE_TX;
  initState = initS2;
}

void initS2_Timeout (void)
{
  //timerSet( initSMTimer, 100 * MILLISECONDS );
  //initState = initS3;
 
  // test to see if it reInitialises after 15 seconds
  timerSet( initSMTimer, 15 * SECONDS );
  initState = initialised;
}

void initS3_greenHigh (void)
{
  timerSet( initSMTimer, 100 * MILLISECONDS );
  initState = initS4;
}

void initS4_greenLow (void)
{
  timerSet( initSMTimer, 100 * MILLISECONDS );
  initState = initS5;
}

void initS5_redHigh (void)
{
  timerSet( initSMTimer, 100 * MILLISECONDS );
  initState = initS6;
}

void initS6_redLow (void)
{
  timerSet( initSMTimer, 100 * MILLISECONDS );
  initState = initS7;
}

void initS7_bothHigh (void)
{
  timerSet( initSMTimer, 100 * MILLISECONDS );
  initState = initS8;
}

void initS8_bothLow (void)
{
  timerLock( initSMTimer );
  initState = initialised;
  beepRepeatedly(500, 5);
}

enum initEvents getInitEvent (void)
{
    if ( timerRead(initSMTimer) == EXPIRED )
    {
        timerLock( initSMTimer );
        return timeout;
    }
    else
        return lastEvent;
}

void setInitEvent ( enum initEvents event) {
  lastEvent = event;
}

