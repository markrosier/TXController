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
#include "beeper.h"

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
    eventHandlerService();
    LEDService();
    beeperService();
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
  eventHandlerInit();
  LEDInit();
  beeperInit();
  initInterrupt();
  flashLED(1000);
  beepRepeatedly(200, 3);
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

  BEEPER_PIN_DIR = OUTPUT_PIN;
  BEEPER_PIN_TYPE = DIGITAL_PIN;
  BEEPER_PIN_LATCH = 0;

  P9241_BUZZER_PIN_DIR = INPUT_PIN;
  
  ENABLE_TX_PIN_DIR = OUTPUT_PIN;
  ENABLE_TX_PIN_TYPE = DIGITAL_PIN;
  ENABLE_TX_PIN_LATCH = DISABLE_TX;
     
  INDICATOR1_PIN_DIR = INPUT_PIN;
  INDICATOR1_PIN_TYPE = DIGITAL_PIN;          

  INDICATOR2_PIN_DIR = INPUT_PIN;
  INDICATOR2_PIN_TYPE = DIGITAL_PIN;          

  // enable the watchdog timer
  WDTCONbits.SWDTEN = 1;

}
