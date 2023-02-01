#include "Pressure_Dtection.h"

int PD_pressure_val = 0;
int PD_threshold = 20;

void (*PD_state)();

void PressureVal_signal(int PD_pressure_val)
{
    if (PD_pressure_val > PD_threshold)
    {
        PD_state = STATE(PD_high_pressure_detected);
    }
    else
    {
        PD_state = STATE(PD_pressure_detection);
    }
}

STATE_define(PD_pressure_detection)
{
    PD_state_id = PD_pressure_detection;
    PD_state = STATE(PD_pressure_detection);
}

STATE_define(PD_high_pressure_detected)
{
    PD_state_id = PD_high_pressure_detected;
    setAlarm_signal();
    PD_state = STATE(PD_pressure_detection);
}
