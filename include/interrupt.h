/* 
 * File:   interrupt.h
 * Author: Mark Rosier
 *
 * Iota Electronics  Limited 2015
 */

#ifndef INTERRUPT_H
#define	INTERRUPT_H

#ifdef	__cplusplus
extern "C"
{
#endif

void initInterrupt( void );
void disableInterrupts( void );
void enableInterrupts( void );


#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPT_H */

