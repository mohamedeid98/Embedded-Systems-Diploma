/*
 * ATmega32_PWM.c
 *
 * Author : Mohamed Eid
 */ 

#include "MCAL/PWM/pwm.h"


int main(void)
{
	DDRB |= (1 << 3);
	PWM_CONFIG_t pwm_config = {MODE_PWM_PHASE_CORRECT, CLK_PRESCALER_256, OC0_MODE_INVERTED, 10};
	PWM_Init(&pwm_config);
    while (1) 
    {
    }
}

