//*****************************************************************************
//
//  Timer.h
//
//  Iota Electronics Limited 2015
// 
//*****************************************************************************

#ifndef _inc_timers
#define _inc_timers


#define	EXPIRED	0
#define MAX_TIMERS	16

#define TIMER_1MS_COUNT 32000
#define SECONDS   1000
#define MILLISECONDS 1

typedef unsigned char TTimerIndex;

extern void timerInit( void );
extern TTimerIndex timerGet( void );
extern void timerSet( TTimerIndex index, unsigned int duration );
extern unsigned int timerRead( TTimerIndex index );
extern void timerLock( TTimerIndex index );
extern void timerDelay( unsigned int Duration );

void timerInterrupt( void );

#endif
