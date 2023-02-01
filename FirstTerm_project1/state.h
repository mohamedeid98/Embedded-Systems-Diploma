#ifndef STATE_H_
#define STATE_H_

#include "driver.h"

#define STATE_define(_stateFUN)     void ST_##_stateFUN()
#define STATE(_stateFUN)            ST_##_stateFUN


void PressureVal_signal(int);

void setAlarm_signal();



#endif /* STATE_H_ */