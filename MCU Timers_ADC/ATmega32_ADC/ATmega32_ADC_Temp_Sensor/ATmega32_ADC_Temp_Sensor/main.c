/*
 * ATmega32_ADC_Temp_Sensor.c
 *
 * Author : Mohamed Eid
 */ 
#include "HAL/lcd/lcd.h"
#include "MCAL/ADC/adc.h"
#include "MCAL/PWM/pwm.h"

uint16_t data;

int main(void)
{
	PWM_CONFIG_t pwm_config = {MODE_PWM_FAST, CLK_PRESCALER_8, OC0_MODE_SET};
	PWM_Init(&pwm_config);
	DDRB |= (1 << 3);
	
	ADC_Config_t adc_config;
	adc_config.adjust_result = LEFT_ADJUSTED;
	adc_config.channel		 = ch1;
	adc_config.divFact		 = DivFact_128;
	adc_config.INT_State	 = ADC_INT_ENABLE;
	adc_config.ref_volt		 = INTERNAL_VOLT_REF;
	
	ADC_Init(&adc_config);
	LCD_Init();
	sei();
	
	LCD_gotoxy(1, 1);
	LCD_print("ADC Value");
	ADCSRA |= (1 << ADSC);					// Activate the start conversion bit.
	while (1) 
    {
		

    }
}

ISR(ADC_vect)
{
	LCD_gotoxy(1, 2);
	LCD_print("    ");
	data = ADCH;
	LCD_gotoxy(1, 2);
	LCD_print_int_number(data);
	//_delay_ms(100);
	ADCSRA |= (1 << ADSC);					// Activate the start conversion bit.

} 