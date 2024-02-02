//=====[#include guards - begin]===============================================

#ifndef _IGNITION_H_
#define _IGNITION_H_

//=====[Declaration of public defines]=========================================

#define DEBOUNCE_TIME  40
#define DELAY_TIME  10

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void ignitionInit();
void updateIgnition();
bool returnEngineStatus();


//=====[#include guards - end]=================================================

#endif // _FIRE_ALARM_H_