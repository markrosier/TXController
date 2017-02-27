/* 
 * File:   main.h
 * Author: Mark Rosier
 *
 * Iota electronics limited 2015
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include "system.h"

void initialise( void );
void hardwareInit( void );
void interruptsInit( void );
void kickWatchDog( void );


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

