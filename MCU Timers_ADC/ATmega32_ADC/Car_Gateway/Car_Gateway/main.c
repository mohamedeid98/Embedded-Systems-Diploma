/*
 * Car_Gateway.c
 *
 * Author : Mohamed Eid
 */ 
#define F_CPU 8000000UL
#include "MCAL/ADC/adc.h"
#include "MCAL/PWM/pwm.h"
#include "HAL/LCD/lcd.h"

uint16_t adc_data;
uint16_t PIR_volt;
uint8_t flag;

int main(void)
{
	uint32_t count=0;
	ADC_Config_t adc_config;
	adc_config.adjust_result = RIGHT_ADJUSTED;
	adc_config.channel		 = ch1;
	adc_config.divFact		 = DivFact_128;
	adc_config.INT_State	 = ADC_INT_ENABLE;
	adc_config.ref_volt		 = VCC_REF_VOLT;
	
	ADC_Init(&adc_config);
	LCD_Init();
	sei();
	
	DDRB |= (1 << 3);
	PWM_CONFIG_t pwm_config = {MODE_PWM_PHASE_CORRECT, CLK_PRESCALER_256, OC0_MODE_INVERTED};
	MCAL_PWM_Init(&pwm_config);
	
	LCD_gotoxy(1, 1);
	LCD_print("Number of Cars");
	ADCSRA |= (1 << ADSC);					// Activate the start conversion bit.
	
    while (1) 
    {
		
		
		if(flag)
		{
			
			MCAL_PWM_Start(15);
			count++;
			LCD_gotoxy(1, 2);
			LCD_print("    ");
			LCD_gotoxy(1, 2);
			LCD_print_int_number(count);
			while(flag)
			{
				
			}
			
			//_delay_ms(1000);
							
		}
		else
		{
			MCAL_PWM_Start(5);
			//_delay_ms(2000);
		}
	}
}

ISR(ADC_vect)
{
	adc_data = ADCL;
	adc_data |= (ADCH << 8);
	PIR_volt = (adc_data / 1023.0) * 5;
	
	if(PIR_volt > 3)
	{
		flag=1;
	}
	else
	{
		flag=0;
	}
	ADCSRA |= (1 << ADSC);					// Activate the start conversion bit.

}