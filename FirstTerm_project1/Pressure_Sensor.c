#include "Pressure_Sensor.h"


int PS_pressure_val = 0;

void (*PS_state)();

void PS_init()
{
    //printf("Pressure Sensor init!");
}

STATE_define(PS_reading)
{
    PS_state_id = PS_reading;
    PS_pressure_val = getPressureVal();
    PressureVal_signal(PS_pressure_val);
    PS_state = STATE(PS_idle);
}

STATE_define(PS_idle)
{
    PS_state_id = PS_idle;
    Delay(100000);
    PS_state = STATE(PS_reading);
}