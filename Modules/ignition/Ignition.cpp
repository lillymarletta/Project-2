//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "Ignition.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} buttonState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalIn driverSeat(D2);
DigitalIn ignition(D3);
DigitalOut engineStarted(LED2);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

int accumualatedDebouncedTime = 0;
int ignitionDebounceTime = 0;

//=====[Declaration and initialization of private global variables]============

bool driverSeatState = OFF;
buttonState_t ignitionState;
bool engineState = OFF;
bool ignitionEnabled = OFF;
bool driverSeatEnabled = OFF;

//=====[Declarations (prototypes) of private functions]========================

void debounceButtonInit();
bool debounceButtonUpdate();

//=====[Implementations of public functions]===================================

void ignitionInit(){
    driverSeat.mode(PullDown);
    ignition.mode(PullDown);
    engineStarted = OFF;
}

void updateIgnition(){
    bool ignitionButtonReleasedEvent = debounceButtonUpdate();
    if (!engineStarted){
        if (driverSeat && ignitionButtonReleasedEvent && ignitionDebounceTime >= DEBOUNCE_TIME){
                engineStarted = ON;
                ignitionDebounceTime = 0;
        }
    }
        
    else{
            if (ignitionButtonReleasedEvent && accumualatedDebouncedTime >= DEBOUNCE_TIME){
                engineStarted = OFF;
                ignitionDebounceTime = 0;  
            }
        }
    ignitionDebounceTime = ignitionDebounceTime + DELAY_TIME;
}

void debounceButtonInit()
{
    if( ignition == 1) {
        ignitionState = BUTTON_UP;
    } else {
        ignitionState = BUTTON_DOWN;
    }
}

bool debounceButtonUpdate()
{
    bool ignitionReleasedEvent = false;
    switch(ignitionState) {

    case BUTTON_UP:
        if( ignition == 1 ) {
            ignitionState = BUTTON_FALLING;
            accumualatedDebouncedTime = 0;
        }
        break;

    case BUTTON_FALLING:
        if( accumualatedDebouncedTime >= DEBOUNCE_TIME ) {
            if( ignition == 0 ) {
                ignitionState = BUTTON_DOWN;
            } else {
                ignitionState = BUTTON_UP;
            }
        }
        accumualatedDebouncedTime = accumualatedDebouncedTime +
                                        DELAY_TIME;
        break;

    case BUTTON_DOWN:
        if( ignition == 1 ) {
            ignitionState = BUTTON_RISING;
            accumualatedDebouncedTime = 0;
        }
        break;

    case BUTTON_RISING:
        if( accumualatedDebouncedTime >= DEBOUNCE_TIME ) {
            if( ignition == 1 ) {
                ignitionState = BUTTON_UP;
                ignitionReleasedEvent = true;
            } else {
                ignitionState = BUTTON_DOWN;
            }
        }
        accumualatedDebouncedTime = accumualatedDebouncedTime +
                                        DELAY_TIME;
        break;

    default:
        debounceButtonInit();
        break;
    }
    return ignitionReleasedEvent;
}

bool returnEngineStatus(){
    return engineStarted;
}

