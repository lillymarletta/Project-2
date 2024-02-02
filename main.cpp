//=====[Libraries]=============================================================

#include "Ignition.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "entryway_light.h"
#include "light_sensor.h"

//=====[Defines]===============================================================

#define DELAY_TIME  10

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration and initialization of public global variables]=============

//=====[Declarations (prototypes) of public functions]=========================

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    ignitionInit();
    entryLightInit();
    while (true) {
        updateIgnition();
        if (returnEngineStatus()){
            entryLightUpdate();
        }
        else{
            entryLightInit();
        }
        delay(DELAY_TIME);
    }
}