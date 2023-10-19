/*
 * pwm.c
 *
 *  Author: Mohamed Eid
 */ 

#include "../Inc/pwm.h"

PWM_CONFIG_t G_pwm_config;

void HAL_PWM_Init(PWM_CONFIG_t *pwm_config)
{
	G_pwm_config = *pwm_config;
	
	TCCR0 |= pwm_config->mode | pwm_config->clk_source | pwm_config->OC0_PIN_MODE;
	
	DDRB |= (1 << 3);

}

void HAL_PWM_Update_DutyCycle(uint8_t Duty_Cycle)
{
	if(G_pwm_config.mode == MODE_PWM_FAST)
	{
		if(G_pwm_config.OC0_PIN_MODE == OC0_MODE_NON_INVERTED)
		{
			OCR0 = ((Duty_Cycle * 256) / 100) - 1;
		}
		else if(G_pwm_config.OC0_PIN_MODE == OC0_MODE_INVERTED)
		{
			OCR0 = 255 - ((Duty_Cycle * 256) / 100);
		}
	}
	else if (G_pwm_config.mode == MODE_PWM_PHASE_CORRECT)
	{
		if(G_pwm_config.OC0_PIN_MODE == OC0_MODE_NON_INVERTED)
		{
			OCR0 = (Duty_Cycle * 255) / 100;
		}
		else if(G_pwm_config.OC0_PIN_MODE == OC0_MODE_INVERTED)
		{
			OCR0 = 255 - (Duty_Cycle * 255) / 100;
		}
	}
}
