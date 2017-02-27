/* 
 * File:   main.c
 * Author: Mark Rosier
 *
 * Iota electronics Limited 2016
 */

#include "system.h"
#include "main.h"
#include "interrupt.h"
#include "hardware.h"
#include "picconfig.h"
#include "timer.h"
#include "eventhandler.h"
#include "led.h"

void kickWatchDog( void )
{
    asm("CLRWDT");
}

//*****************************************************************************
//	Function:	main
//	Arguments:	None
//  Action:         Program entry
//	Returns:	None
//*****************************************************************************
void main( void )
{
  initialise();
  while( 1 )
  {
    //eventHandlerService();
    LEDService();
    kickWatchDog();
  }
}

//*****************************************************************************
//	Function:	Initialise
//	Arguments: 	None
//	Action: 	Program Initialisation
//	Returns: 	None
//*****************************************************************************
void initialise( void )
{
  hardwareInit();
  timerInit();
  //eventHandlerInit();
  LEDInit();
  initInterrupt();
  flashLED(1000);
}

//*****************************************************************************
//	Function:	HardwareInit
//	Arguments: 	None
//	Action: 	Various Registers are Initialised
//	Returns: 	None
//*****************************************************************************
void hardwareInit( void )
{
  OSCCONbits.SCS = 0;
  OSCCONbits.IRCF = 0xE;
  OSCCONbits.SPLLEN = 1;

  LED_PIN_DIR = OUTPUT_PIN;

/*
  PI_POWER_OFF_REQUEST_PIN_DIR = INPUT_PIN;
  
  RESTART_INDICATOR_PIN = INPUT_PIN;

  SYSTEM_ON_SWITCH_PIN_DIR = OUTPUT_PIN;
  SYSTEM_ON_SWITCH_LATCH = SYSTEM_OFF;

  ENABLE_VIN_MEASURE_PIN_DIR = OUTPUT_PIN;
  ENABLE_VIN_MEASURE_LATCH = DISABLE_VIN_MEASUREMENT;

  PI_POWER_BUTTON_PIN_DIR = OUTPUT_PIN;
  PI_POWER_BUTTON_LATCH = PI_POWER_BUTTON_RELEASED;

  BATTERY_VOLTAGE_PIN_DIR = INPUT_PIN;
  BATTERY_VOLTAGE_PIN_TYPE = ANALOGUE_PIN;

  PI_BATTERY_LOW_PIN_DIR = OUTPUT_PIN;
  PI_BATTERY_LOW_PIN_TYPE = DIGITAL_PIN;
  PI_BATTERY_LOW_LATCH = BATTERY_OK;

  PI_BACKLIGHT_CONTROL_PIN_DIR = INPUT_PIN;
  PI_BACKLIGHT_CONTROL_PIN_TYPE = DIGITAL_PIN;

  ON_BUTTON_PIN_DIR = INPUT_PIN;
  ON_BUTTON_PIN_TYPE = DIGITAL_PIN;
  
  BACKLIGHT_CONTROL_PIN_DIR = OUTPUT_PIN;
  BACKLIGHT_CONTROL_PIN_TYPE = DIGITAL_PIN;
  BACKLIGHT_CONTROL_LATCH = BACKLIGHT_OFF;

  PI_DOCKED_PIN_DIR = OUTPUT_PIN;
  PI_DOCKED_PIN_TYPE = DIGITAL_PIN;
  PI_DOCKED_LATCH = BACKLIGHT_OFF;
*/
  // enable the watchdog timer
  WDTCONbits.SWDTEN = 1;

}
