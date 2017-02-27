#ifndef inc_beeper
#define inc_beeper

//****************************************************************************
//
//  beeper.h
//
//  Iota Electronics Limited 2017
//
//****************************************************************************


void setBeeper ( void );
void clearBeeper ( void );
void beepRepeatedly ( int period, int nBeeps );

void beeperInit (void);
void beeperService (void);

#define BEEPER_TICK_COUNT 0x65 //should be around 4.8kHz
#define DEFAULT_BEEPER_PERIOD    1000

#endif
