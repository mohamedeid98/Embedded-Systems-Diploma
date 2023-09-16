/*
 * adc.c
 *
 *  Author: Mohamed Eid
 */ 

#include "adc.h"

void ADC_Init(ADC_Config_t* ADC_CFG)
{
	DDRA	&= ~(1 << ADC_CFG->channel);				// Make the pin for the selected ADC channel an input pin.
	ADCSRA	|= (1 << ADEN);								// Turn on the ADC module of the AVR because it is disabled
														// upon power-on reset to save power.
	ADCSRA	&= ~(0b111 << 0);							// Clear first three bits.
	ADCSRA	|= (ADC_CFG->divFact);						// Select conversion speed.
	ADMUX	|= (ADC_CFG->ref_volt);						// Select voltage reference.
	ADMUX	&= ~(0b1111 << 0);							// Clear first four bits.
	ADMUX	|= (ADC_CFG->channel);						// Select ADC input channel.
	ADCSRA	|= ADC_CFG->INT_State;						// Configure interrupt.
	ADMUX	|= ADC_CFG->adjust_result;					// Adjust the output result.
}

uint16_t ADC_Read(void)
{
	uint16_t converted_data;
#ifdef POLLING	 
	ADCSRA |= (1 << ADSC);					// Activate the start conversion bit.
	while(!(ADCSRA & (1 << ADIF)));			// Wait for the conversion to complete by polling the ADIF flag.
#endif
	converted_data = ADCL;					// Read ADCL register.
	converted_data |=  (ADCH << 8);         // Read ADCH register.
	return converted_data;
}