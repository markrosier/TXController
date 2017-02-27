//****************************************************************************
//
//  interrupt.c
//
//  Iota Electronics Limited 2016
//
//****************************************************************************

#include "system.h"
#include "timer.h"
#include "interrupt.h"
#include "eventhandler.h"


void initInterrupt( void )
{
  INTCONbits.PEIE = 1; //Enable Peripheral Interrupt
  INTCONbits.GIE = 1; //Enable INTs globally
}

void disableInterrupts( void )
{
  INTCONbits.GIE = 0;
}

void enableInterrupts( void )
{
  INTCONbits.GIE = 1;
}

void interrupt ISRCode( )
{
//  keyInterrupt();
  timerInterrupt( );
}
