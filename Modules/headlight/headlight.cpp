//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "headlight.h"
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

//=====[Declaration and initialization of public global objects]===============

AnalogIn modeSelector(A0);
DigitalOut leftHeadlight(D8);
DigitalOut rightHeadlight(D9);
UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

//=====[Implementations of public functions]===================================

void headlightInit()
//initializes headlights to off.
{
    leftHeadlight = OFF;
    rightHeadlight = OFF;
}

void headlightUpdate()
//turns headlights on or off depending on the mode.
{
    float lightSensorReading = lightSensorUpdate();
    float modeSelection = modeSelector.read();
    if (modeSelection <= LS_OFF_MAX_VALUE){
        //turns headlights off if potentiometer value is less than 0.35
        leftHeadlight = OFF;
        rightHeadlight = OFF;
    }
    else if (modeSelection <= LS_ON_MAX_VALUE && modeSelection >= LS_ON_MIN_VALUE){
        //turns headlights on if potentiometer value is in between 0.35 and 0.7
        leftHeadlight = ON;
        rightHeadlight = ON;
    }
    else{
        //turns headlights to auto if potentiometer reading is above 0.7
        if (lightSensorReading <= LS_DARKNESS_VALUE){
            //turns headlights on after a 2 second delay if potentiometer is below the set darkness value
            delay(LIGHT_DELAY_2S);
            leftHeadlight = ON;
            rightHeadlight = ON;
        }
        else{
            //turns headlights off after a 1 second delay if potentiometer is above the set darkness value
            delay(LIGHT_DELAY_1S);
            leftHeadlight = OFF;
            rightHeadlight = OFF;
        }
    }
}