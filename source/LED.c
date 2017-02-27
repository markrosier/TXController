//************************************************************************
// 
// led.c
//
// Iota Electronics Limited 2017
//
//************************************************************************

#include "system.h"
#include "timer.h"
#include "led.h"
#include "hardware.h"

BYTE  LEDTimer = 0;
bool  flasherToggle = false;
INT16 flashRate = DEFAULT_FLASH_PERIOD;
bool  flashing = false;

void setLED ()
{
    flashing = false;
    LED_PIN = LED_ON;
}

void clearLED ()
{
    flashing = false;
    LED_PIN = LED_OFF;
}

void flashLED ( int period)
{
    flashing = true;
    LED_PIN = LED_ON;
    flashRate = period;
    flasherToggle = true;
}


void LEDInit ()
{
  LEDTimer = timerGet ();  
//  flashLED(1000);
  timerSet( LEDTimer, flashRate );
}

void LEDService ()
{
  if (flashing)
  {
    if ( timerRead(LEDTimer) == EXPIRED )
    {
        if (flasherToggle)
        {
          flasherToggle = false;
          LED_PIN = LED_OFF;
        }
        else
        {
          flasherToggle = true;
          LED_PIN = LED_ON;
        }
        timerSet( LEDTimer, flashRate );
    }
  }
}

