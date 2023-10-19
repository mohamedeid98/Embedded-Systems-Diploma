/*
 * servo.c
 *
 *  Author: Mohamed Eid
 */ 
#include "../Inc/servo.h"

void HAL_Servo_Init()
{
	PWM_CONFIG_t pwm_config = {MODE_PWM_PHASE_CORRECT, CLK_PRESCALER_256, OC0_MODE_INVERTED};
	HAL_PWM_Init(&pwm_config);
}
void HAL_Servo_Update(uint8_t dutyCycle)
{
	HAL_PWM_Update_DutyCycle(dutyCycle);
}