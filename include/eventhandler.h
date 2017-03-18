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
#define BUZZER_PERIOD           2

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
                noInitEvent,
                initTimeoutEvent,
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


void (*const initStateTable [maxInitStates][maxInitEvents]) (void) = {
        //Event     noEvent         initTimeoutEvent greenHighEvent    greenLowEvent    redHighEvent    redLowEvent    bothHighEvent    bothLowEvent
//State    
/* initS1     */ { init_NoAction,   initS1_Timeout,  init_NoAction,     init_NoAction,    init_NoAction,   init_NoAction,  init_NoAction,    init_NoAction   },
/*initS2      */ { init_NoAction,   initS2_Timeout,  init_NoAction,     init_NoAction,    init_NoAction,   init_NoAction,  init_NoAction,    init_NoAction   },
/*initS3      */ { init_NoAction,   init_Restart,    initS3_greenHigh, init_NoAction,    init_NoAction,   init_NoAction,  init_NoAction,    init_NoAction   },
/*initS4      */ { init_NoAction,   init_Restart,    init_NoAction,     initS4_greenLow, init_NoAction,   init_NoAction,  init_NoAction,    init_NoAction   },
/*initS5      */ { init_NoAction,   init_Restart,    init_NoAction,     init_NoAction,    initS5_redHigh, init_NoAction,  init_NoAction,    init_NoAction   },
/*initS6      */ { init_NoAction,   init_Restart,    init_NoAction,     init_NoAction,    init_NoAction,   initS6_redLow, init_NoAction,    init_NoAction   }, 
/*initS7      */ { init_NoAction,   init_Restart,    init_NoAction,     init_NoAction,    init_NoAction,   init_NoAction,  initS7_bothHigh, init_NoAction   },
/*initS8      */ { init_NoAction,   init_Restart,    init_NoAction,     init_NoAction,    init_NoAction,   init_NoAction,  init_NoAction,    initS8_bothLow },
/*initialised */ { init_NoAction,   init_NoAction,    init_NoAction,    init_NoAction,   init_NoAction,  init_NoAction, init_NoAction,   init_NoAction  }
};

enum runStates {
                runS1,
                runS2,
                runS3,
                runS4,
                maxRunStates
} runState;

enum runEvents {
                noRunEvent,
                runTimeoutEvent,
                initialisedEvent,
                beepEvent,
                greenFlashingEvent,
                greenSteadyLowEvent,
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
void runS4_Timeout (void);
void runS4_GreenSteadyLow (void);

enum runEvents getRunEvent (void);


void (*const runStateTable [maxRunStates][maxRunEvents]) (void) = {
        //Event     noEvent         runTimeoutEvent  initialisedEvent    beepEvent          greeenFlashingEvent       greenSteadyLowEvent   errorEvent 
//State  
/* runs1 */  {     run_NoAction,    runS1_Timeout,   runS1_Initialised,  runS1_Error,           runS1_Error,          run_NoAction,         runS1_Error },
/* runs2 */  {     run_NoAction,    runS2_Timeout,   runS2_Error,        runS2_BeepReceived,    runS2_Error,          run_NoAction,         runS2_Error },
/* runs3 */  {     run_NoAction,    runS3_Timeout,   runS3_Error,        runS3_Error,           runS3_GreenFlashing,  run_NoAction,         runS3_Error },
/* runs4 */  {     run_NoAction,    runS4_Timeout,   runS3_Error,        runS3_Error,           run_NoAction,         runS4_GreenSteadyLow, runS4_Error }
};

#endif
