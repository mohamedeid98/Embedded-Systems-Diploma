
#ifndef PRESSURE_DETECTION_H_
#define PRESSURE_DETECTION_H_

#include "state.h"

enum 
{
    PD_pressure_detection,
    PD_high_pressure_detected

}PD_state_id;

STATE_define(PD_pressure_detection);
STATE_define(PD_high_pressure_detected);

extern void (*PD_state)();








#endif