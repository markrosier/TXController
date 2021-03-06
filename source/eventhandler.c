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

extern unsigned int systick;

BYTE eventHandlerTimer = 0;
int initSMTimer = 0;  //timer used by init state machine
int runSMTimer = 0;  //timer used by run State Machine
int buzzerTimer = 0;  //timer used for determining buzzer event
int minuteTimer = 0;    //long timer used for restarting once in a while
BYTE errorCount = 0;

struct event {
    bool eventFlag;
    unsigned int eventTime;
};

struct event greenWentHigh = {false, 0}, 
             greenWentLow  = {false, 0},
             redWentHigh   = {false, 0}, 
             redWentLow    = {false, 0};

struct event chargerInitialised;

//int buzzerDetected = 1;
//bool buzzerStarted = false;

void initIOCInterrupt( void )
{
  INTCONbits.GIE = 1;
  IOCANbits.IOCAN3 = 1;
  IOCANbits.IOCAN2 = 1;
  IOCAPbits.IOCAP2 = 1;
  IOCANbits.IOCAN4 = 1;
  IOCAPbits.IOCAP4 = 1;
  INTCONbits.IOCIF = 0;
  INTCONbits.IOCIE = 1;
  INTCONbits.PEIE = 1;
}

int buzzerTransitionCount = 0;

void IOCInterrupt( void )
{
  if ( INTCONbits.IOCIF == 1)
  {
    // check P9242 Buzzer line
    if (IOCAFbits.IOCAF3 == 1)
    {
        if (buzzerTransitionCount ++ > N_IGNORE_BUZZER_TRANSITIONS )
        {
            // start the buzzerTimer it will keep running until
            // it has stopped being retriggered by this
            // so the timeout occurs when the buzzer has stopped buzzing
            timerSet( buzzerTimer, BUZZER_PERIOD );
            //INDICATOR1_PIN_LATCH ^= 1;
        }
        else 
            timerLock(buzzerTimer);
      
        IOCAFbits.IOCAF3 = 0;
    }
    if (IOCAFbits.IOCAF2 == 1)
    {
       if (INDICATOR2_PIN == 0)
      {
        greenWentHigh.eventFlag = true;
        greenWentHigh.eventTime = systick;
      }
      else
      {
        greenWentLow.eventFlag = true;
        greenWentLow.eventTime = systick;
      }
      IOCAFbits.IOCAF2 = 0;
    }
    if (IOCAFbits.IOCAF4 == 1)
    {
      if (INDICATOR1_PIN == 0)
      {
        redWentHigh.eventFlag = true;
        redWentHigh.eventTime = systick;
      }
      else
      {
        redWentLow.eventFlag = true;
        redWentLow.eventTime = systick;
      }
      IOCAFbits.IOCAF4 = 0;
    }
  }
}

void eventHandlerInit ()
{
  eventHandlerTimer = timerGet ();
  timerSet( eventHandlerTimer, EVENT_HANDLER_PERIOD );
  initIOCInterrupt();
  buzzerTimer = timerGet();
  initSMTimer = timerGet();
  runSMTimer = timerGet();
  minuteTimer = longTimerGet();
  init_Restart();
  
}

void eventHandlerService ()
{
  if ( timerRead(eventHandlerTimer) == EXPIRED )
  {
    if (initState != initialised) 
    {
        initEvent = getInitEvent();

        if (((initEvent >= 0) && (initEvent < maxInitEvents))
        && ((initState >= 0) && (initState < maxInitStates))) 
        {
            initStateTable [initState][initEvent]();
        } 
        else 
        {
          // Invalid State just start again
            init_Restart();
        }
    }
    else
    {
        runEvent = getRunEvent();

        if (((runEvent >= 0) && (runEvent < maxRunEvents))
        && ((runState >= 0) && (runState < maxRunStates))) 
        {
            runStateTable [runState][runEvent]();
        } 
        else 
        {
        // Invalid State just start again
            init_Restart();
        }
    }
    timerSet( eventHandlerTimer, EVENT_HANDLER_PERIOD );
  }
}


void init_NoAction (void) 
{
    // do nothing
}

void init_Restart (void)
{
  timerSet( initSMTimer, 2000 * MILLISECONDS );
  ENABLE_TX_PIN_LATCH = DISABLE_TX;
  initState = initS1;
  greenWentHigh.eventFlag = false;
  greenWentLow.eventFlag = false;
  redWentHigh.eventFlag = false;
  redWentLow.eventFlag = false;
  runState =  runS1;
  flashLED(200);
}

void initS1_Timeout (void)
{
  timerSet( initSMTimer, 3000 * MILLISECONDS );
  ENABLE_TX_PIN_LATCH = ENABLE_TX;
  initState = initS5;
}

void initS2_Timeout (void)
{
  timerSet( initSMTimer, 2000 * MILLISECONDS );
  initState = initS3;
 
  // test to see if it reInitialises after 15 seconds
  //timerSet( initSMTimer, 15 * SECONDS );
//  timerLock( initSMTimer );
//  longTimerSet( minuteTimer, (DWORD) 10 * MINUTES);
//  initState = initialised;
}

void initS3_greenHigh (void)
{
  timerSet( initSMTimer, 2000 * MILLISECONDS );
  initState = initS4;
}

void initS4_greenLow (void)
{
  timerSet( initSMTimer, 2000 * MILLISECONDS );
  initState = initS7;
}

void initS5_redHigh (void)
{
  timerSet( initSMTimer, 2000 * MILLISECONDS );
  initState = initS6;
}

void initS6_redLow (void)
{
  timerSet( initSMTimer, 2000 * MILLISECONDS );
  initState = initS4;
}

void initS7_bothHigh (void)
{
  timerSet( initSMTimer, 2000 * MILLISECONDS );
  initState = initS8;
}

void initS8_bothLow (void)
{
  timerLock( initSMTimer );
  initState = initialised;
  chargerInitialised.eventFlag = true;
  chargerInitialised.eventTime = systick;
  timerSet( runSMTimer, 2000 * MILLISECONDS );

  //beepRepeatedly(500, 5);
}

enum initEvents getInitEvent (void)
{
    if ( timerRead(initSMTimer) == EXPIRED )
    {
        timerLock( initSMTimer );
        return initTimeoutEvent;
    }
    else if ( redWentHigh.eventFlag ) 
    {
        // check to see if the green has gone high in the last 2ms
        if (greenWentHigh.eventFlag ) 
        {
            if ( systick - greenWentHigh.eventTime >= 2) 
            {
                greenWentHigh.eventFlag = false;
                redWentHigh.eventFlag = false;
                return bothHighEvent;
            }
        }
        else 
        {
            redWentHigh.eventFlag = false;
            return redHighEvent;
        }
    }
    else if ( redWentLow.eventFlag )
    {
         if (greenWentLow.eventFlag ) 
        {
            if ( systick - greenWentLow.eventTime >= 2) 
            {
                greenWentLow.eventFlag = false;
                redWentLow.eventFlag = false;
                return bothLowEvent;
            }
        }
        else 
        {
            redWentLow.eventFlag = false;
            return redLowEvent;
        }
    }
    else if ( greenWentHigh.eventFlag ) 
    {
        if (redWentHigh.eventFlag ) 
        {
            if ( systick - redWentHigh.eventTime >= 2) 
            {
                greenWentHigh.eventFlag = false;
                redWentHigh.eventFlag = false;
                return bothHighEvent;
            }
        }
        else 
        {
            greenWentHigh.eventFlag = false;
            return greenHighEvent;
        }
        
    }
    else if ( greenWentLow.eventFlag )
    {
        if (redWentLow.eventFlag ) 
        {
            if ( systick - redWentLow.eventTime >= 2) 
            {
                greenWentLow.eventFlag = false;
                redWentLow.eventFlag = false;
                return bothLowEvent;
            }
        }
        else 
        {
            greenWentLow.eventFlag = false;
            return greenLowEvent;
        }
    }

    return noInitEvent;
    
}

void run_NoAction (void)
{
    
}

void run_Initialised (void)
{
   timerLock(runSMTimer);
   clearLED();
   longTimerSet(minuteTimer, (unsigned long) 1 * MINUTES);
   runState = runS2;
}

void run_BeepReceived (void)
{
   longTimerLock(minuteTimer);
   //beepRepeatedly ( 100, 1);
   timerSet(runSMTimer, 10 * SECONDS);
   runState = runS3;
}

void run_GreenFlashing (void)
{
    timerSet(runSMTimer, 10 * SECONDS);
    setLED();
}

void run_GreenSteadyLow (void)
{
   timerLock(runSMTimer); 
   longTimerSet(minuteTimer, (unsigned long)1 * MINUTES);
   runState = runS2;
   clearLED();
   //beepRepeatedly ( 200, 2);

}

enum runEvents multipleErrorEvent(void)
{
    errorCount+=1;
    if (errorCount > ERROR_LIMIT) 
    {
        //beepRepeatedly ( 100, 1);
        errorCount = 0;
        timerLock(runSMTimer);
        return errorEvent;
    }

    return noRunEvent;
}

enum runEvents getRunEvent(void)
{
    if ( chargerInitialised.eventFlag )
    {
        chargerInitialised.eventFlag = false;
        return initialisedEvent;
    }
    else if ( timerRead(runSMTimer) == EXPIRED )
    {
        timerLock( runSMTimer );
        return runTimeoutEvent;
    }
    else if (timerRead(buzzerTimer) == EXPIRED )
    {
        buzzerTransitionCount = 0;
        timerLock( buzzerTimer );
        return beepEvent;
    }
    else if (longTimerRead(minuteTimer) == EXPIRED)
     {
        longTimerLock( minuteTimer );
        return runTimeoutEvent;
    }
    else if ( greenWentLow.eventFlag )
    {
        if (greenWentHigh.eventFlag && greenWentLow.eventFlag ) 
        {
            if ( greenWentLow.eventTime - greenWentHigh.eventTime <= 600) 
            {
                greenWentHigh.eventFlag = false;
                //greenWentLow.eventFlag = false;
                return greenFlashingEvent;
            }
            else if ( greenWentHigh.eventTime - greenWentLow.eventTime <= 600)
            {
                greenWentHigh.eventFlag = false;
                greenWentLow.eventFlag = false;
                return greenFlashingEvent;
            }
            else
            {
               greenWentHigh.eventFlag = false;
               greenWentLow.eventFlag = false;
               return multipleErrorEvent();
            }
        }
        else if (systick - greenWentLow.eventTime > 600)
        {
            greenWentHigh.eventFlag = false;
            greenWentLow.eventFlag = false;
            return greenSteadyLowEvent;
        }
    }
    else if ( greenWentHigh.eventFlag )
    {
        if (systick - greenWentHigh.eventTime > 1000)
        {
            greenWentHigh.eventFlag = false;
            greenWentLow.eventFlag = false;
            return multipleErrorEvent();
        }
    }
    else if (redWentHigh.eventFlag || redWentLow.eventFlag)
    {
            redWentHigh.eventFlag = false;
            redWentLow.eventFlag = false;
            return multipleErrorEvent();
    }
    
    return noRunEvent;
}

