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
#define ERROR_LIMIT             10
#define N_IGNORE_BUZZER_TRANSITIONS 100

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
void run_Initialised (void);
void run_BeepReceived (void);
void run_GreenFlashing (void);
void run_GreenSteadyLow (void);

enum runEvents getRunEvent (void);

void (*const runStateTable [maxRunStates][maxRunEvents]) (void) = {
        //Event     noEvent         runTimeoutEvent  initialisedEvent    beepEvent          greeenFlashingEvent       greenSteadyLowEvent   errorEvent 
//State  
/* runs1 */  {     run_NoAction,    init_Restart,    run_Initialised,    init_Restart,        init_Restart,          run_NoAction,         init_Restart },
/* runs2 */  {     run_NoAction,    init_Restart,    init_Restart,       run_BeepReceived,    init_Restart,          run_NoAction,         init_Restart },
/* runs3 */  {     run_NoAction,    init_Restart,    init_Restart,       init_Restart,        run_GreenFlashing,     run_GreenSteadyLow,   init_Restart }
};

#endif
