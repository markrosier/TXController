/* 
 * File:   config.h
 * Author: Mark Rosier
 *
 * Iota Electronics Limited 2017
 */

#ifndef PICCONFIG_H
#define	PICCONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
  
// Word 1
#pragma config (FCMEN=OFF)
#pragma config (IESO=OFF)
#pragma config (CLKOUTEN=OFF)   // CLK OUT function
#pragma config (BOREN=ON)      // Brown out reset
#pragma config (CPD=OFF)        // Data Memory Code Protection
#pragma config (CP=OFF)         // Code Protection
#pragma config (MCLRE=OFF)       // MCLR pin On = Reset off = digital input
#pragma config (PWRTE=OFF)      // Power up timer disabled
#pragma config (WDTE=ON)       // Watchdog Timer enabled
#pragma config (FOSC=INTOSC)  	// Oscillator election

// Word 2
#pragma config (LVP=OFF )
#pragma config (BORV=LO)
#pragma config (STVREN=OFF)
#pragma config (PLLEN=ON)
#pragma config (WRT=OFF)

#ifdef	__cplusplus
}
#endif

#endif	/* PICCONFIG_H */


