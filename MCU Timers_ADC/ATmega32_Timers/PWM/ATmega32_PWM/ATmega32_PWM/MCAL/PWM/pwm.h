/*
 * pwm.h
 *
 *  Author: Mohamed Eid
 */ 


#ifndef PWM_H_
#define PWM_H_

/*******************************************************************************
									INCLUDES
*******************************************************************************/
#include "../../LIB/ATmega32.h"


/*******************************************************************************
							Configuration Structure
*******************************************************************************/


typedef struct  
{
	uint8_t mode;			// Specifies the mode of the timer
							// This parameter must be set based on the @ref MODE_define
							
	uint8_t clk_source;		// Specifies the clock source to the timer
							// This parameter must be set based on the @ref CLK_SOURCE_define
	
	uint8_t OC0_PIN_MODE;   // Specifies the output compare pin behavior.
							// This parameter must be set based on @ref OC0_MODE_define
							
	uint8_t Duty_Cycle;    // Specifies the duty cycle. Can be a value from 0% to 100%.
}PWM_CONFIG_t;







/*******************************************************************************
							Reference Defines
*******************************************************************************/



// @ref MODE_define

// Bit 6, 3 – WGM01:0: Waveform Generation Mode

#define MODE_PWM_PHASE_CORRECT			(uint8_t)(1 << 6)
#define MODE_PWM_FAST					(uint8_t)(0x48)

// @ref CLK_SOURCE_define

	//	Table 42. Clock Select Bit Description
	//	CS02 CS01 CS00				Description
	//	0	 0	  0					No clock source (Timer/Counter stopped).
	//	0	 0    1					clkI/O/(No prescaling)
	//	0    1    0					clkI/O/8 (From prescaler)
	//	0    1    1					clkI/O/64 (From prescaler)
	//	1    0    0					clkI/O/256 (From prescaler)
	//	1    0    1					clkI/O/1024 (From prescaler)

#define NO_CLK_SRC						(uint8_t)(0)
#define CLK_PRESCALER_0					(uint8_t)(1)
#define CLK_PRESCALER_8					(uint8_t)(2)
#define CLK_PRESCALER_64				(uint8_t)(3)
#define CLK_PRESCALER_256				(uint8_t)(4)
#define CLK_PRESCALER_1024				(uint8_t)(5)


// @ref OC0_MODE_define
#define OC0_MODE_DISCONNECTED			(uint8_t)(0)
//#define OC0_MODE_TOGGLE				(uint8_t)(1 << 4)
#define OC0_MODE_NON_INVERTED			(uint8_t)(2 << 4) /* - In MODE_PWM_FAST Clear OC0 on compare match, set OC0 at BOTTOM,
															   (non-inverting mode)
															 - In MODE_PWM_PHASE_CORRECT Clear OC0 on compare match when up-counting. 															   Set OC0 on compare match when down counting. */

#define OC0_MODE_INVERTED				(uint8_t)(3 << 4) /* - In MODE_PWM_FAST Set OC0 on compare match, clear OC0 at BOTTOM,
													           (inverting mode)
															 - In MODE_PWM_PHASE_CORRECT Set OC0 on compare match when up-counting. 															   Clear OC0 on compare match when down counting. */






/*******************************************************************************
									APIs
*******************************************************************************/

void PWM_Init(PWM_CONFIG_t *pwm_config);
void PWM_Start(uint8_t duty_cycle);





#endif /* PWM_H_ */