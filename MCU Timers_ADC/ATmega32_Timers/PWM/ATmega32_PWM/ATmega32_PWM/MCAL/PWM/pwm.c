/*
 * pwm.c
 *
 *  Author: Mohamed Eid
 */ 

#include "pwm.h"



void PWM_Init(PWM_CONFIG_t *pwm_config)
{
	TCCR0 |= pwm_config->mode | pwm_config->clk_source | pwm_config->OC0_PIN_MODE;
}

void PWM_Start(uint8_t duty_cycle)
{
	uint8_t compare_val = 255 * duty_cycle / 100 ;
	OCR0 = compare_val;
}


