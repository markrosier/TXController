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
#define LED_PIN                  PORTAbits.RA5
#define LED_PIN_DIR              TRISAbits.TRISA5

 /*
  
  // pin 3  is always Digital Input
#define PI_POWER_OFF_REQUEST_PIN      PORTAbits.RA3
#define PI_POWER_OFF_REQUEST_PIN_DIR  TRISAbits.TRISA3
#define PI_POWER_OFF_REQUEST          1
#define PI_POWER_OFF_REQUEST_INACTIVE 0

  // pin 4  Define as Digital Output
#define SYSTEM_ON_SWITCH_LATCH      LATCbits.LATC5
#define SYSTEM_ON_SWITCH_PIN_DIR   TRISCbits.TRISC5
#define SYSTEM_ON                   0
#define SYSTEM_OFF                  1

  // pin 5 Define as Digital Output
#define ENABLE_VIN_MEASURE_LATCH    LATCbits.LATC4
#define ENABLE_VIN_MEASURE_PIN_DIR  TRISCbits.TRISC4
#define ENABLE_VIN_MEASUREMENT      1
#define DISABLE_VIN_MEASUREMENT     0

  // pin 6 Define as Digital Output
#define PI_POWER_BUTTON_LATCH       LATCbits.LATC3
#define PI_POWER_BUTTON_PIN_DIR     TRISCbits.TRISC3
#define PI_POWER_BUTTON_PIN_TYPE    ANSELCbits.ANSC3
#define PI_POWER_BUTTON_PRESSED     1
#define PI_POWER_BUTTON_RELEASED    0

  // pin 7  Define as Analogue Input
#define BATTERY_VOLTAGE_PIN         PORTCbits.RC2
#define BATTERY_VOLTAGE_PIN_DIR     TRISCbits.TRISC2
#define BATTERY_VOLTAGE_PIN_TYPE    ANSELCbits.ANSC2
#define BATTERY_VOLTAGE_CHANNEL     6

  // pin 8 Define as Digital output
#define PI_BATTERY_LOW_LATCH          LATCbits.LATC1
#define PI_BATTERY_LOW_PIN_DIR      TRISCbits.TRISC1
#define PI_BATTERY_LOW_PIN_TYPE     ANSELCbits.ANSC1
#define BATTERY_LOW                 1
#define BATTERY_OK                 0

  // pin 9  Define as Digital Input
#define PI_BACKLIGHT_CONTROL_PIN      PORTCbits.RC0
#define PI_BACKLIGHT_CONTROL_PIN_DIR  TRISCbits.TRISC0
#define PI_BACKLIGHT_CONTROL_PIN_TYPE ANSELCbits.ANSC0
#define BACKLIGHT_ON_REQUEST          1

  // pin 10  Define as Digital Input
#define ON_BUTTON_PIN               PORTAbits.RA2
#define ON_BUTTON_PIN_DIR           TRISAbits.TRISA2
#define ON_BUTTON_PIN_TYPE          ANSELAbits.ANSA2
#define ON_BUTTON_PRESSED           0

  // pin 11 Define as Digital Output
#define BACKLIGHT_CONTROL_LATCH     LATAbits.LATA1
#define BACKLIGHT_CONTROL_PIN_DIR   TRISAbits.TRISA1
#define BACKLIGHT_CONTROL_PIN_TYPE  ANSELAbits.ANSA1
#define BACKLIGHT_ON                1
#define BACKLIGHT_OFF               0

  // pin 12 Define as Digital Output
#define PI_DOCKED_LATCH             LATAbits.LATA0
#define PI_DOCKED_PIN_DIR           TRISAbits.TRISA0
#define PI_DOCKED_PIN_TYPE          ANSELAbits.ANSA0
#define PI_DOCKED                   1
#define PI_NOT_DOCKED               0
  
  */
  

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

