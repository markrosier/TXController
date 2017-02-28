/* 
 * File:   hardware.h
 * Author: Mark Rosier
 *
 * Iota Electronics 2016
 */

#ifndef HARDWARE_H
#define	HARDWARE_H

#ifdef	__cplusplus
extern "C"
{
#endif

#define false                       0
#define true                        !false
  typedef unsigned char bool;

#define OUTPUT_PIN                  0
#define INPUT_PIN                   1
#define DISABLE_OUTPUT              1
#define ENABLE_OUTPUT		          	0

#define DIGITAL_PIN			            0
#define ANALOGUE_PIN		          	1

#define ADC_GO_NOT_DONE	            0b00000010
#define ADC_ENABLE                  0b00000001

#define LED_ON                      0
#define LED_OFF                     1

 /* 
  // pin 1  Define as Digital output
#define RESTART_INDICATOR_PIN       PORTAbits.RA5
#define RESTART_INDICATOR_PIN_DIR   TRISAbits.TRISA5
#define RESTART_INDICATED           1
  
*/
  // pin 2  Define as Digital Input
#define LED_PIN                      PORTAbits.RA5
#define LED_PIN_DIR                  TRISAbits.TRISA5

  // pin 3  Define as Digital Input
#define INDICATOR1_PIN               PORTAbits.RA4
#define INDICATOR1_PIN_LATCH         LATAbits.LATA4
#define INDICATOR1_PIN_DIR           TRISAbits.TRISA4
#define INDICATOR1_PIN_TYPE          ANSELAbits.ANSA4
  
  // pin 4  is always Digital Input
#define P9243_BUZZER_PIN            PORTAbits.RA3
#define P9241_BUZZER_PIN_DIR        TRISAbits.TRISA3

  // pin 5  Define as Digital Input
#define INDICATOR2_PIN               PORTAbits.RA2
#define INDICATOR2_PIN_LATCH         LATAbits.LATA2
#define INDICATOR2_PIN_DIR           TRISAbits.TRISA2
#define INDICATOR2_PIN_TYPE          ANSELAbits.ANSA2
  
  // pin 6 Define as Digital output
#define BEEPER_PIN_LATCH            LATAbits.LATA1
#define BEEPER_PIN_DIR              TRISAbits.TRISA1
#define BEEPER_PIN_TYPE             ANSELAbits.ANSA1

   // pin 7 Define as Digital output
#define ENABLE_TX_PIN_LATCH         LATAbits.LATA0
#define ENABLE_TX_PIN_DIR           TRISAbits.TRISA0
#define ENABLE_TX_PIN_TYPE          ANSELAbits.ANSA0
#define DISABLE_TX                  1
#define ENABLE_TX                   0   



  

// Using Internal Clock of 8 MHz
#define OSC_FREQUENCY 16000000L
// Delay Function
#define	_delay_us(x) { unsigned us; \
		       us = (x)/(32000000/OSC_FREQUENCY)|1; \
		       while(--us != 0) continue; }


#ifdef	__cplusplus
}
#endif



#endif	/* HARDWARE_H */

