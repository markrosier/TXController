#ifndef inc_eventhandler
#define inc_eventhandler

//****************************************************************************
//
//  eventhandler.h
//
//  Iota Electronics Limited 2017
//
//****************************************************************************

void initIOCInterrupt( void );
void resetIOCInterrupt( void );
void IOCInterrupt( void );
void eventHandlerInit( void );
void eventHandlerService( void );

#define EVENT_HANDLER_PERIOD    10

// State Machine stuff
enum initStates {   
                initS1,
                initS2, 
                initS3,
                initS4,
                initS5,
                initS6,
                initS7,
                initS8,
                initialised,
                maxInitStates } initState;
                
enum initEvents {   
                noEvent,
                timeout,
                greenHighEvent,
                greenLowEvent,
                redHighEvent,
                redLowEvent,
                bothHighEvent,
                bothLowEvent,
                maxInitEvents } initEvent;


void noAction (void);
void reInit (void);
void initS1_Timeout (void);
void initS2_Timeout (void);
void initS3_greenHigh (void);
void initS4_greenLow (void);
void initS5_redHigh (void);
void initS6_redLow (void);
void initS7_bothHigh (void);
void initS8_bothLow (void);
enum initEvents getInitEvent (void);
void setInitEvent( enum initEvents event);


void (*const initStateTable [maxInitStates][maxInitEvents]) (void) = {
        //Event     noEvent     timeout         greenHighEvent      greenLowEvent       redHighEvent    redLowEvent     bothHighEvent       bothLowEvent
//State    
/* initS1     */ {  noAction,   initS1_Timeout, reInit,             reInit,             reInit,         reInit,         reInit,             reInit         },
/*initS2      */ {  noAction,   initS2_Timeout, reInit,             reInit,             reInit,         reInit,         reInit,             reInit         },
/*initS3      */ {  noAction,   reInit,         initS3_greenHigh,   reInit,             reInit,         reInit,         reInit,             reInit         },
/*initS4      */ {  noAction,   reInit,         reInit,             initS4_greenLow,    reInit,         reInit,         reInit,             reInit         },
/*initS5      */ {  noAction,   reInit,         reInit,             reInit,             initS5_redHigh, reInit,         reInit,             reInit         },
/*initS6      */ {  noAction,   reInit,         reInit,             reInit,             reInit,         initS6_redLow,  reInit,             reInit         }, 
/*initS7      */ {  noAction,   reInit,         reInit,             reInit,             reInit,         reInit,         initS7_bothHigh,    reInit         },
/*initS8      */ {  noAction,   reInit,         reInit,             reInit,             reInit,         reInit,         reInit,             initS8_bothLow },
/*initialised */ {  noAction,   reInit,         noAction,           noAction,           noAction,       noAction,       noAction,           noAction       }
};

#endif
