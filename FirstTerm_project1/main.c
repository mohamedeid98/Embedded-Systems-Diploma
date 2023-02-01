#include "Alarm_Driver.h"
#include "Pressure_Dtection.h"
#include "Pressure_Sensor.h"


void setup()
{
    PS_init();
    AL_init();
    PS_state = STATE(PS_reading);
    PD_state = STATE(PD_pressure_detection);
    AL_state = STATE(AL_OFF);
}

int main()
{
    GPIO_INITIALIZATION();
    setup();

    while(1)
    {
        PS_state();
        PD_state();
        AL_state();
    }

    return 0;
}