/*
 * ATmega32_PWM.c
 *
 * Author : Mohamed Eid
 */ 

#include "MCAL/PWM/pwm.h"


int main(void)
{
	PWM_CONFIG_t pwm_config = {MODE_PWM_FAST, CLK_PRESCALER_8, OC0_MODE_SET};
	PWM_Init(&pwm_config);
	DDRB |= (1 << 3);
	PWM_Start(20);
    /* Replace with your application code */
    while (1) 
    {
    }
}

