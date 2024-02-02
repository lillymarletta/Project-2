//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "entryway_light.h"
#include "light_sensor.h"

//=====[Declaration of private defines]========================================

#define LS_OFF_MIN_VALUE  0
#define LS_OFF_MAX_VALUE  0.35
#define LS_ON_MIN_VALUE  0.35
#define LS_ON_MAX_VALUE  0.7
#define LS_AUTO_MIN_VALUE  0.7
#define LS_AUTO_MAX_VALUE  1
#define LS_DARKNESS_VALUE 0.75
#define LIGHT_DELAY_2S 200
#define LIGHT_DELAY_1S 100

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn modeSelector(A0);
DigitalOut leftHeadlight(D8);
DigitalOut rightHeadlight(D9);
UnbufferedSerial uartUsb(USBTX, USBRX, 115200);


//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void entryLightInit()
{
    leftHeadlight = OFF;
    rightHeadlight = OFF;
}

void entryLightUpdate()
{
    float lightSensorReading = lightSensorUpdate();
    float modeSelection = modeSelector.read();
    if (modeSelection <= LS_OFF_MAX_VALUE){
        leftHeadlight = OFF;
        rightHeadlight = OFF;
    }
    else if (modeSelection <= LS_ON_MAX_VALUE && modeSelection >= LS_ON_MIN_VALUE){
        leftHeadlight = ON;
        rightHeadlight = ON;
    }
    else{
        if (lightSensorReading <= LS_DARKNESS_VALUE){
//            delay(LIGHT_DELAY_2S);
            leftHeadlight = ON;
            rightHeadlight = ON;
        }
        else{
//            delay(LIGHT_DELAY_1S);
            leftHeadlight = OFF;
            rightHeadlight = OFF;
        }
    }
}