//*****************************************************************************
//
//  Timer.c
//
//  Iota Electronics Ltd 
//
//*****************************************************************************
#include "system.h"
#include "timer.h"

unsigned int timers[MAX_TIMERS];
unsigned int delayTimer;
unsigned char numTimers;


//*****************************************************************************
//*	Function:	timerInit
//*	Arguments:	None
//*	Action:		Initialise Timer
//*	Returns:	None
//*****************************************************************************

void timerInit( void )
{
  numTimers = 0;

  T1GCONbits.TMR1GE = 0;

  T1CONbits.TMR1CS1 = 0;
  T1CONbits.TMR1CS0 = 1;
  T1CONbits.T1CKPS1 = 0;
  T1CONbits.T1CKPS0 = 0;

  TMR1 = TIMER_1MS_COUNT;
  
  PIE1bits.TMR1IE = 1; //Enable TIMER1 Interrupt

  INTCONbits.PEIE = 1; //Enable Peripheral Interrupt
  T1CONbits.TMR1ON = 1;
}


//*****************************************************************************
//*	Function:	timerInterrupt
//*	Arguments:	None
//*	Action:	Timer Interrupt
//*	Returns:	None
//*****************************************************************************
//bool tog2 = false;

void timerInterrupt( void )
{
  unsigned char i;

  if ( PIE1bits.TMR1IE && PIR1bits.TMR1IF )
  {
    T1CONbits.TMR1ON = 0;
    if ( ( delayTimer != 0 ) )
    {
      delayTimer--;
    }

    for ( i = 0; i < numTimers; i++ )
    {
      if ( ( timers[i] != 0 ) && ( timers[i] != 0xFFFF ) )
      {
        timers[i]--;
      }
    }

    TMR1 = TIMER_1MS_COUNT;
    T1CONbits.TMR1ON = 1;
    PIR1bits.TMR1IF = 0;
    //if (!tog2) {PI_DOCKED_LATCH = 1; tog2 = true;} else {PI_DOCKED_LATCH = 0; tog2 = false;}

  }
}

//*****************************************************************************
//*	Function:	timerGet
//*	Arguments:	None
//*	Action:		Assign the next timer
//*	Returns:	TTimerIndex - the timer id
//*****************************************************************************

TTimerIndex timerGet( void )
{
  TTimerIndex result;

  result = numTimers;
  numTimers++;
  timerLock( result );
  return ( result );
}

//*****************************************************************************
//*	Function:	timerSet
//*	Arguments:	
//*				TTimerIndex Index - the timer id
//*				WORD Duration - required duration (ms)
//*	Action:		Set the specified timer
//*	Returns:	None
//*****************************************************************************

void timerSet( TTimerIndex index, unsigned int duration )
{
  if ( index < numTimers )
  {
    timers[index] = duration;
  }
}

//*****************************************************************************
//*	Function:	timerRead
//*	Arguments:	
//*				TTimerIndex Index - the timer id
//*	Action:		Read remaining time for the specified timer
//*	Returns:	Duration - remaining duration (ms)
//*****************************************************************************

unsigned int timerRead( TTimerIndex index )
{
  unsigned int result = 0xFFFF;
  if ( index < numTimers )
  {
    result = timers[index];
  }
  return ( result );
}

//*****************************************************************************
//*	Function:	timerLock
//*	Arguments:	
//*				TTimerIndex Index - the timer id
//*	Action:		Lock the specified timer
//*	Returns:	None
//*****************************************************************************

void timerLock( TTimerIndex index )
{
  if ( index < numTimers )
  {
    timers[index] = 0xFFFF;
  }
}

//*****************************************************************************
//*	Function:	timerDelay
//*	Arguments:	
//*			WORD Duration - required duration (ms)
//*	Action:		Blocking delay
//*	Returns:	None
//*****************************************************************************

void timerDelay( unsigned int duration )
{
  delayTimer = duration;
  while ( delayTimer != 0)
  {
    continue;
  }
}

