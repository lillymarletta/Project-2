//=====[Libraries]=============================================================

#include "mbed.h"

#include "light_sensor.h"

//=====[Declaration of private defines]========================================

#define LS_NUMBER_OF_SAMPLES    10

//=====[Declaration and initialization of public global objects]===============

AnalogIn ls(A2);

//=====[Declaration and initialization of private global variables]============

float lsReadingsArray[LS_NUMBER_OF_SAMPLES];

//=====[Implementations of public functions]===================================

void lightSensorInit()
//initialiazes the array of readings of the light sensor. 
{
    int i;
    
    for( i=0; i<LS_NUMBER_OF_SAMPLES ; i++ ) {
        lsReadingsArray[i] = 0;
    }
}

float lightSensorUpdate()
//takes the average of all of the last 10 readings and returns that average number
{
    static int lsSampleIndex = 0;
    float lsReadingsSum = 0.0;
    float lsReadingsAverage = 0.0;

    int i = 0;

    lsReadingsArray[lsSampleIndex] = ls.read();
       lsSampleIndex++;
    if ( lsSampleIndex >= LS_NUMBER_OF_SAMPLES) {
        lsSampleIndex = 0;
    }
    
   lsReadingsSum = 0.0;
    for (i = 0; i < LS_NUMBER_OF_SAMPLES; i++) {
        lsReadingsSum = lsReadingsSum + lsReadingsArray[i];
    }
    lsReadingsAverage = lsReadingsSum / LS_NUMBER_OF_SAMPLES;
    return lsReadingsAverage;
}
