#ifndef PRESSURE_SENSOR_H_
#define PRESSURE_SENSOR_H_

#include "state.h"

enum
{
    PS_reading,
    PS_idle
}PS_state_id;

extern void (*PS_state)();

STATE_define(PS_reading);
STATE_define(PS_idle);
void PS_init();


#endif