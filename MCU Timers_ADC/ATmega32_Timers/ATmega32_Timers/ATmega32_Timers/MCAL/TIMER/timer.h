/*
 * timer.h
 *
 * Created: 8/22/2023 2:43:53 AM
 *  Author: Mohamed
 */ 


#ifndef TIMER_H_
#define TIMER_H_

/*******************************************************************************
									INCLUDES
*******************************************************************************/
#include "../../LIB/ATmega32.h"


/*******************************************************************************
							Configuration Structure
*******************************************************************************/

typedef void(*PTR_CallBack_FUN)(void);

typedef struct  
{
	uint8_t mode;			// Specifies the mode of the timer
							// This parameter must be set based on the @ref MODE_define
							
	uint8_t clk_source;		// Specifies the clock source to the timer
							// This parameter must be set based on the @ref CLK_SOURCE_define
							
	uint8_t OCInterrupt;    // Specifies whether the output compare interrupt is enabled or disabled
						   // This parameter must be set based on the @ref OCInterrupt_define
	
	uint8_t TOInterrupt;    // Specifies whether the timer overflow interrupt is enabled or disabled
							// This parameter must be set based on the @ref TOInterrupt_define
							
	PTR_CallBack_FUN TIMER0_CALLBACK_Overflow_INTERRUPT;
	PTR_CallBack_FUN TIMER0_CALLBACK_CompareMatch_INTERRUPT;

}TIMER0_CONFIG_t;







/*******************************************************************************
							Reference Defines
*******************************************************************************/



// @ref MODE_define

// Bit 6, 3 – WGM01:0: Waveform Generation Mode

#define MODE_NORMAL						(uint8_t)(0)
#define MODE_CTC						(uint8_t)(8)  // Clear Timer on Compare Match (CTC) mode



// @ref CLK_SOURCE_define

	//	Table 42. Clock Select Bit Description
	//	CS02 CS01 CS00				Description
	//	0	 0	  0					No clock source (Timer/Counter stopped).
	//	0	 0    1					clkI/O/(No prescaling)
	//	0    1    0					clkI/O/8 (From prescaler)
	//	0    1    1					clkI/O/64 (From prescaler)
	//	1    0    0					clkI/O/256 (From prescaler)
	//	1    0    1					clkI/O/1024 (From prescaler)
	//	1    1    0					External clock source on T0 pin. Clock on falling edge.
	//	1    1    1					External clock source on T0 pin. Clock on rising edge.

#define NO_CLK_SRC						(uint8_t)(0)
#define CLK_PRESCALER_0					(uint8_t)(1)
#define CLK_PRESCALER_8					(uint8_t)(2)
#define CLK_PRESCALER_64				(uint8_t)(3)
#define CLK_PRESCALER_256				(uint8_t)(4)
#define CLK_PRESCALER_1024				(uint8_t)(5)
#define CLK_EXT_FALLING					(uint8_t)(6)
#define CLK_EXT_RISING					(uint8_t)(7)


// @ref @ref OCInterrupt_define
#define OCInterrupt_DISABLE				(uint8_t)(0)
#define OCInterrupt_ENABLE				(uint8_t)(2)


// @ref @ref TOInterrupt_define
#define TOInterrupt_DISABLE				(uint8_t)(0)
#define TOInterrupt_ENABLE				(uint8_t)(1)


/*******************************************************************************
									APIs
*******************************************************************************/

void TIMER0_Init(TIMER0_CONFIG_t *timer_config);
void TIMER0_Stop(void);
void TIMER0_SetCompVal(uint8_t CompVal);
uint8_t TIMER0_GetCompVal(void);
void TIMER0_SetCountVal(uint8_t countVal);
uint8_t TIMER0_GetCountVal(void);






#endif /* TIMER_H_ */