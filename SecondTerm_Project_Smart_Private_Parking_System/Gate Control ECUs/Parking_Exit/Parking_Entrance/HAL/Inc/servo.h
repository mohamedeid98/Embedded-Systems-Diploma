/*
 * servo.h
 *
 *  Author: Mohamed Eid
 */ 


#ifndef SERVO_H_
#define SERVO_H_

#include "../../MCAL/Inc/pwm.h"

void HAL_Servo_Init();
void HAL_Servo_Update(uint8_t dutyCycle);

#endif /* SERVO_H_ */