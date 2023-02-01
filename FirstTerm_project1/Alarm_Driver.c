#include "Alarm_Driver.h"


void (*AL_state)();

void AL_init()
{
    //printf("Alarm init");
}

void setAlarm_signal()
{
    AL_state = STATE(AL_ON);
}


STATE_define(AL_ON)
{
    AL_state_id = AL_ON;
    Set_Alarm_actuator(1);
    Delay(100000);
    AL_state = STATE(AL_OFF);
}
STATE_define(AL_OFF)
{
    AL_state_id = AL_OFF;
    Set_Alarm_actuator(0);
    Delay(100000);

}

