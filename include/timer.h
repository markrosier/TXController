//*****************************************************************************
//
//  Timer.h
//
//  Iota Electronics Limited 2017
// 
//*****************************************************************************

#ifndef _inc_timers
#define _inc_timers


#define	EXPIRED	0
#define MAX_TIMERS	10
#define MAX_LONG_TIMERS 1 // long period timers

#define TIMER_1MS_COUNT 32000
#define SECONDS   1000
#define MINUTES   60 * SECONDS
#define MILLISECONDS 1

typedef unsigned char TTimerIndex;
typedef unsigned char LTTimerIndex;

extern void timerInit( void );
extern TTimerIndex timerGet( void );
extern void timerSet( TTimerIndex index, unsigned int duration );
extern unsigned int timerRead( TTimerIndex index );
extern void timerLock( TTimerIndex index );
extern void timerDelay( unsigned int Duration );

extern LTTimerIndex longTimerGet( void );
extern void longTimerSet( LTTimerIndex, unsigned long duration );
extern unsigned long longTimerRead( LTTimerIndex );
extern void longTimerLock( LTTimerIndex );


void timerInterrupt( void );

#endif
