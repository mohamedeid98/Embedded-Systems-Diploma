/*
 * adc.h
 *
 *  Author: Mohamed Eid
 */ 


#ifndef ADC_H_
#define ADC_H_
/********************************************************************************************
										Includes
*********************************************************************************************/

#include<avr/io.h>
#include<util/delay.h>
#include<stdint.h>
#include<avr/interrupt.h>

/********************************************************************************************
								Configuration Structure
*********************************************************************************************/

typedef struct  
{
	uint8_t channel;				// Specifies the ADC input channel.
									// This parameter can be a value of @ref ADC_CHANNEL_define
	
	uint8_t divFact;				// Specifies the conversion speed of ADC.
									// This parameter can be a value of @ref ADC_DIV_FACT_define
	
	uint8_t INT_State;				// Specifies the ADC interrupt enable state. 
									// This parameter can be a value of @ref ADC_INT_define
	
	uint8_t adjust_result;			// Specifies how result is stored into data registers.
									// This parameter can be a value of @ref ADC_ADJUST_RESULT_define
	
	uint8_t ref_volt;				// Specifies the ADC reference voltage.
									// This parameter can be a value of @ref ADC_REFERENCE_VOLTAGE_define  
}ADC_Config_t;

/********************************************************************************************
									Reference MACROS AND ENUMS
*********************************************************************************************/
// @ref ADC_CHANNEL_define
typedef enum
{
	ch1=0,
	ch2,
	ch3,
	ch4,
	ch5,
	ch6,
	ch7
}ChannelNumber;

// @ref ADC_DIV_FACT_define
typedef enum
{
	DivFact_2=1,
	DivFact_4,
	DivFact_8,
	DivFact_16,
	DivFact_32,
	DivFact_64,
	DivFact_128
}DivionFactor;

// @ref ADC_INT_define
#define ADC_INT_DISABLE		(uint8_t)(0x00)
#define ADC_INT_ENABLE		(1 << ADIE)

// @ref ADC_ADJUST_RESULT_define
#define	RIGHT_ADJUSTED		(uint8_t)(0x00)
#define LEFT_ADJUSTED		(1 << ADLAR)

// @ref ADC_REFERENCE_VOLTAGE_define
#define EXTERNAL_REF_VOLT	(uint8_t)(0x00)
#define VCC_REF_VOLT		(1 << 6)
#define INTERNAL_VOLT_REF	(3 << 6) // The internal voltage reference is 2.56V.


/********************************************************************************************
										ADC APIs
*********************************************************************************************/

void ADC_Init(ADC_Config_t* ADC_CFG);
uint16_t ADC_Read(void);

#endif /* ADC_H_ */