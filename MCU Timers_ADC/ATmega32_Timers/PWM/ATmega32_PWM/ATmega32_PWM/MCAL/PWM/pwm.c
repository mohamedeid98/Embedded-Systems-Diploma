/*
 * pwm.c
 *
 *  Author: Mohamed Eid
 */ 

#include "pwm.h"



void PWM_Init(PWM_CONFIG_t *pwm_config)
{
	
	TCCR0 |= pwm_config->mode | pwm_config->clk_source | pwm_config->OC0_PIN_MODE;
	
	if(pwm_config->mode == MODE_PWM_FAST)
	{
		if(pwm_config->OC0_PIN_MODE == OC0_MODE_NON_INVERTED)
		{
			OCR0 = ((pwm_config->Duty_Cycle * 256) / 100) - 1;
		}
		else if(pwm_config->OC0_PIN_MODE == OC0_MODE_INVERTED)
		{
			OCR0 = 255 - ((pwm_config->Duty_Cycle * 256) / 100);
		}
	}
	else if (pwm_config->mode == MODE_PWM_PHASE_CORRECT)
	{
		if(pwm_config->OC0_PIN_MODE == OC0_MODE_NON_INVERTED)
		{
			OCR0 = (pwm_config->Duty_Cycle * 255) / 100;
		}
		else if(pwm_config->OC0_PIN_MODE == OC0_MODE_INVERTED)
		{
			OCR0 = 255 - (pwm_config->Duty_Cycle * 255) / 100;
		}
	}
}

