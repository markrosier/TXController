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
                maxInitStates 
} initState;
                
enum initEvents {   
                noEvent,
                timeoutEvent,
                greenHighEvent,
                greenLowEvent,
                redHighEvent,
                redLowEvent,
                bothHighEvent,
                bothLowEvent,
                maxInitEvents 
} initEvent;


void init_NoAction (void);
void init_Restart (void);
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
        //Event     noEvent         timeoutEvent     greenHighEvent    greenLowEvent    redHighEvent    redLowEvent    bothHighEvent    bothLowEvent
//State    
/* initS1     */ { init_NoAction,   initS1_Timeout,  init_Restart,     init_Restart,    init_Restart,   init_Restart,  init_Restart,    init_Restart   },
/*initS2      */ { init_NoAction,   initS2_Timeout,  init_Restart,     init_Restart,    init_Restart,   init_Restart,  init_Restart,    init_Restart   },
/*initS3      */ { init_NoAction,   init_Restart,    initS3_greenHigh, init_Restart,    init_Restart,   init_Restart,  init_Restart,    init_Restart   },
/*initS4      */ { init_NoAction,   init_Restart,    init_Restart,     initS4_greenLow, init_Restart,   init_Restart,  init_Restart,    init_Restart   },
/*initS5      */ { init_NoAction,   init_Restart,    init_Restart,     init_Restart,    initS5_redHigh, init_Restart,  init_Restart,    init_Restart   },
/*initS6      */ { init_NoAction,   init_Restart,    init_Restart,     init_Restart,    init_Restart,   initS6_redLow, init_Restart,    init_Restart   }, 
/*initS7      */ { init_NoAction,   init_Restart,    init_Restart,     init_Restart,    init_Restart,   init_Restart,  initS7_bothHigh, init_Restart   },
/*initS8      */ { init_NoAction,   init_Restart,    init_Restart,     init_Restart,    init_Restart,   init_Restart,  init_Restart,    initS8_bothLow },
/*initialised */ { init_NoAction,   init_Restart,    init_NoAction,    init_NoAction,   init_NoAction,  init_NoAction, init_NoAction,   init_NoAction  }
};

enum runStates {
                runS1,
                runS2,
                runS3,
                runS4,
                maxRunStates
} runState;

enum runEvents {
                noEvent,
                timeoutEvent,
                initialisedEvent,
                beepEvent,
                greenFlashingEvent,
                errorEvent,
                maxRunEvents 
} runEvent;

void run_NoAction (void);
void runS1_Error (void);
void runS1_Timeout (void);
void runS1_Initialised (void);
void runS2_Error (void);
void runS2_Timeout (void);
void runS2_BeepReceived (void);
void runS3_Error (void);
void runS3_Timeout (void);
void runS3_GreenFlashing (void);
void runS4_Error (void);
void runS4_GreenSteadyLow (void);

void (*const runStateTable [maxRunStates][maxRunEvents]) (void) = {
        //Event     noEvent         timeoutEvent     greenHighEvent    greenLowEvent    redHighEvent    redLowEvent    bothHighEvent    bothLowEvent
//State    
};

#endif
