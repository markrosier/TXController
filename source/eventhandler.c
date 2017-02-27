//************************************************************************
// 
// eventhandler.c
// handles event related functions
//
// Iota Electronics Limited 2016
//
//************************************************************************

#include "system.h"
#include "timer.h"
#include "hardware.h"
#include "batterymonitor.h"
#include "eventhandler.h"
#include "timer.h"
//#include "led.h"

bool restartIndicated = false;

extern enum eBatteryState batteryState;

BYTE eventHandlerTimer = 0;
bool onOffKeyPressed = false;
enum eOnState onState = onStateOff;
bool chargerAttached = false;
bool switchedOn = false;
BYTE offDelayTimer = 0;

void initKeyInterrupt( void )
{
  INTCONbits.GIE = 1;
  IOCANbits.IOCAN2 = 1;
  onOffKeyPressed = false;
  INTCONbits.IOCIF = 0;
  INTCONbits.IOCIE = 1;
  INTCONbits.TMR0IE = 0;
  INTCONbits.PEIE = 0;
}

void resetKeyInterrupt( void )
{
  IOCAFbits.IOCAF2 = 0;
  INTCONbits.PEIE = 1;
}

void keyInterrupt( void )
{
  if ( INTCONbits.IOCIF == 1)
  {
    // check On Switch
    if (IOCAFbits.IOCAF2 == 1)
    {
      if ( !onOffKeyPressed )
      {
        onOffKeyPressed = true;
        PI_POWER_BUTTON_LATCH = PI_POWER_BUTTON_PRESSED;
        timerSet( eventHandlerTimer, DEBOUNCE_PERIOD );
      }
      IOCAFbits.IOCAF2 = 0;
    }
  }
}

// The unit will go into sleep mode, the only way out is through
// interrupt on change interrupts caused by the ON BUTTON being pressed
// during this period the watchdog timer is disabled

void gotoSleep (void)
{
  
  //clearLED();
  initKeyInterrupt();
  asm("SLEEP");
  asm("NOP");
  resetKeyInterrupt();
}

void switchOff ( void )
{
  SYSTEM_ON_SWITCH_LATCH = SYSTEM_OFF;
  switchedOn = false;
  //clearLED();
 }

void switchOn (void )
{
  if ( ! switchedOn )
  {
    SYSTEM_ON_SWITCH_LATCH = SYSTEM_ON;
    switchedOn = true;
    //setLED();
  }
}

void eventHandlerInit ()
{
  eventHandlerTimer = timerGet ();
  timerSet( eventHandlerTimer, EVENT_HANDLER_PERIOD );
  offDelayTimer = timerGet();
  initKeyInterrupt();
}

void eventHandlerService ()
{
  if ( timerRead(eventHandlerTimer) == EXPIRED )
  {
    // check for key release
    if ( ON_BUTTON_PIN != ON_BUTTON_PRESSED && onOffKeyPressed )
    {
      onOffKeyPressed = false;
      PI_POWER_BUTTON_LATCH = PI_POWER_BUTTON_RELEASED;
    }

    if ( RESTART_INDICATOR_PIN == RESTART_INDICATED) 
    {
      restartIndicated = true;
    }
    
    switch ( onState ) 
    {
        case onStateOff:
            switchOff();
            gotoSleep();
            if (onOffKeyPressed)
            {
                onState = onStateOffWaitingforKeyRelease;
            }
            break;
        case onStateWaitingforOff:
            if ( timerRead( offDelayTimer) == EXPIRED )
            {
                onState = onStateOnWaitingforKeyRelease;
                timerLock( offDelayTimer );
            }
            break;
        case onStateWaitingforOffRequest:
            if ( PI_POWER_OFF_REQUEST_PIN == PI_POWER_OFF_REQUEST && onOffKeyPressed)
            {
                timerSet( offDelayTimer, OFF_TIMEOUT );
                onState =  onStateWaitingforOff;
            }
            else if ( (timerRead( offDelayTimer) == EXPIRED) && onOffKeyPressed)
            {
                switchOff();
                onState = onStateOnWaitingforKeyRelease;
                timerLock( offDelayTimer );
            }
            else if (!onOffKeyPressed )
            {
                onState = onStateOn;
            }
            break;
        case onStateOffWaitingforKeyRelease:
            if ( !onOffKeyPressed )
            {
                switchOn();
                onState = onStateOnWaitingforRequestRelease;
            }
            break;
        case onStateOnWaitingforKeyRelease:
            if ( !onOffKeyPressed )
            {
                switchOff();
                onState = onStateOff;
            }
            break;
        case onStateOnWaitingforRequestRelease:
            if ( PI_POWER_OFF_REQUEST_PIN == PI_POWER_OFF_REQUEST_INACTIVE )
            {
                //switchOn();
                onState = onStateOn;
            }
            break;
        case onStateOn:
        default:
            if ( batteryState == batteryCritical )
            {
                onState = onStateOff;
            }
            else  if ( PI_POWER_OFF_REQUEST_PIN == PI_POWER_OFF_REQUEST )
            {
              if (restartIndicated)
              {
                onState =  onStateOnWaitingforRequestRelease;
                
              } 
              else
              {
                timerSet( offDelayTimer, OFF_TIMEOUT );
                onState =  onStateWaitingforOff;
              }
            }
            else if (onOffKeyPressed) 
            {
                timerSet( offDelayTimer, OFF_BUTTON_TIMEOUT );
                onState =  onStateWaitingforOffRequest;
            }
            else 
            {
                switchOn();
                restartIndicated = false;
            }
            break;
    } 
    timerSet( eventHandlerTimer, EVENT_HANDLER_PERIOD );
  }
}


