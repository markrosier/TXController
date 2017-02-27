//************************************************************************
// 
// beeper.c
//
// Iota Electronics Limited 2017
//
//************************************************************************

#include "system.h"
#include "timer.h"
#include "beeper.h"
#include "hardware.h"

BYTE  beeperTimer = 0;
bool  beeperToggle = false;
INT16 beepRate = DEFAULT_BEEPER_PERIOD;
bool  repeatedBeeping = false;
bool  beeperOn = false;
int   nBeeps = 0;


//*****************************************************************************
//*	Function:	timerInit
//*	Arguments:	None
//*	Action:		Initialise Timer
//*	Returns:	None
//*****************************************************************************

void timer2Init( void )
{

  T2CONbits.T2CKPS = 0b00;
  T2CONbits.T2OUTPS = 0b0111;;

  PR2 =  BEEPER_TICK_COUNT;
  
  PIE1bits.TMR2IE = 1; //Enable TIMER2 Interrupt

  INTCONbits.PEIE = 1; //Enable Peripheral Interrupt
  T2CONbits.TMR2ON = 1;
}

//*****************************************************************************
//*	Function:	timer2Interrupt
//*	Arguments:	None
//*	Action:	Timer Interrupt
//*	Returns:	None
//*****************************************************************************

void timer2Interrupt( void )
{
  unsigned char i;

  if ( PIE1bits.TMR2IE && PIR1bits.TMR2IF )
  {
    T2CONbits.TMR2ON = 0;

    if (beeperOn) 
    {
      BEEPER_PIN_LATCH ^= 1;
    }
    T2CONbits.TMR2ON = 1;
    PIR1bits.TMR2IF = 0;
  }
}




void setBeeper ()
{
    repeatedBeeping = false;
    beeperOn = true;
 }

void clearBeeper ()
{
    repeatedBeeping = false;
    beeperOn = false;
}

void beepRepeatedly ( int period, int n)
{
    repeatedBeeping = true;
    if (n != -1)
      nBeeps = n * 2;
    else 
      nBeeps = -1;
    beeperOn = false;
    beepRate = period;
    beeperToggle = false;
}


void beeperInit ()
{
  timer2Init();
  beeperOn = false;
  beeperTimer = timerGet ();  
  timerSet( beeperTimer, beepRate );
}

void beeperService ()
{
  if (repeatedBeeping)
  {
    if ( timerRead(beeperTimer) == EXPIRED )
    {
      if (beeperToggle)
      {
        beeperToggle = false;
        beeperOn = false;
      }
      else
      {
        beeperToggle = true;
        beeperOn = true;
      }
    
      if (nBeeps != -1) 
      {
        nBeeps--;
        if (nBeeps == 0)
        {
          repeatedBeeping = false;
          beeperOn = false;
        }
      }
      timerSet( beeperTimer, beepRate );
    }
  }
}

