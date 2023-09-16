/*
 * pwm.c
 *
 *  Author: Mohamed Eid
 */ 

#include "pwm.h"

PWM_CONFIG_t pwm_config;

void MCAL_PWM_Init(PWM_CONFIG_t *pwm_cfg)
{
	pwm_config = *pwm_cfg;
	
	TCCR0 |= pwm_cfg->clk_source | pwm_cfg->mode | pwm_cfg->OC0_PIN_MODE;
	
	
}

void MCAL_PWM_Start(uint8_t Duty_Cycle)
{
	if(pwm_config.mode == MODE_PWM_FAST)
	{
		if(pwm_config.OC0_PIN_MODE == OC0_MODE_NON_INVERTED)
		{
			OCR0 = ((Duty_Cycle * 256) / 100) - 1;
		}
		else if(pwm_config.OC0_PIN_MODE == OC0_MODE_INVERTED)
		{
			OCR0 = 255 - ((Duty_Cycle * 256) / 100);
		}
	}
	else if (pwm_config.mode == MODE_PWM_PHASE_CORRECT)
	{
		if(pwm_config.OC0_PIN_MODE == OC0_MODE_NON_INVERTED)
		{
			OCR0 = (Duty_Cycle * 255) / 100;
		}
		else if(pwm_config.OC0_PIN_MODE == OC0_MODE_INVERTED)
		{
			OCR0 = 255 - (Duty_Cycle * 255) / 100;
		}
	}
	
}
