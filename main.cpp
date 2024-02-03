//=====[Libraries]=============================================================

#include "Ignition.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "headlight.h"
#include "light_sensor.h"

//=====[Defines]===============================================================

#define DELAY_TIME  10

//=====[Main function, the program entry point after power on or reset]========

int main()
//runs the functions from the other modules to implement the system
{
    ignitionInit();
    headlightInit();
    while (true) {
        updateIgnition();
        if (returnEngineStatus()){
            headlightUpdate();
        }
        else{
            headlightInit();
        }
        delay(DELAY_TIME);
    }
}