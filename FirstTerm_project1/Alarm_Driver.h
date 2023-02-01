#ifndef ALARM_DRIVER_H_
#define ALARM_DRIVER_H_

#include "state.h"

extern void (*AL_state)();

enum
{
    AL_ON,
    AL_OFF
}AL_state_id;

void AL_init();
STATE_define(AL_ON);
STATE_define(AL_OFF);




#endif