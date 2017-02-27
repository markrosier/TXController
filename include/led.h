#ifndef inc_led
#define inc_led

//****************************************************************************
//
//  led.h
//
//  Iota Electronics Limited 2016
//
//****************************************************************************


void setLED ( void );
void clearLED ( void );
void flashLED ( int period );

void LEDInit (void);
void LEDService (void);

#define DEFAULT_FLASH_PERIOD    1000

#endif
