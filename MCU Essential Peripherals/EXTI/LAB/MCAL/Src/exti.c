/*
 * exti.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Mohamed Eid
 */


#include "../Inc/exti.h"






/*
 * =====================================================================
 * 									Generic Macros
 * =====================================================================
 */


#define AFIO_GPIO_EXTI_MAPPING(x)			(x==GPIOA)?0:\
											(x==GPIOB)?1:\
											(x==GPIOC)?2:\
											(x==GPIOD)?3:0




/*
 * =====================================================================
 * 									Generic Variables
 * =====================================================================
 */

void (*GP_IRQ_CallBack[15])(void);



/*
 * =====================================================================
 * 									Generic Functions
 * =====================================================================
 */



void NVIC_ENABLE(uint8_t EXTI_InputLineNumber)
{
	switch(EXTI_InputLineNumber)
	{
		case 0:
			NVIC_IRQ6_EXTI0_ENABLE();
			break;
		case 1:
			NVIC_IRQ7_EXTI1_ENABLE();
			break;
		case 2:
			NVIC_IRQ8_EXTI2_ENABLE();
			break;
		case 3:
			NVIC_IRQ9_EXTI3_ENABLE();
			break;
		case 4:
			NVIC_IRQ10_EXTI4_ENABLE();
			break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			NVIC_IRQ23_EXTI5_9_ENABLE();
			break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			NVIC_IRQ40_EXTI10_15_ENABLE();
			break;
	}
}

void NVIC_DISABLE(uint8_t EXTI_InputLineNumber)
{
	switch(EXTI_InputLineNumber)
		{
			case 0:
				NVIC_IRQ6_EXTI0_DISABLE();
				break;
			case 1:
				NVIC_IRQ7_EXTI1_DISABLE();
				break;
			case 2:
				NVIC_IRQ8_EXTI2_DISABLE();
				break;
			case 3:
				NVIC_IRQ9_EXTI3_DISABLE();
				break;
			case 4:
				NVIC_IRQ10_EXTI4_DISABLE();
				break;
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				NVIC_IRQ23_EXTI5_9_DISABLE();
				break;
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
				NVIC_IRQ40_EXTI10_15_DISABLE();
				break;
		}
}


void Update_EXTI(EXTI_PinConfig_t *EXTI_Config)
{
	/*
	 * 1- Configure the GPIO pin to be input --> input floating
	 */
	GPIO_PinConfig_t pinConfig;

	pinConfig.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN;
	pinConfig.GPIO_PinMode   = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_Port, &pinConfig);

	/*
	 * 2- Configure the AFIO registers to set up the routing between ports and EXTI peripheral
	 */

	uint8_t AFIO_EXTICR_Index;
	uint8_t AFIO_EXTICR_POS;

	AFIO_EXTICR_Index = (EXTI_Config->EXTI_PIN.EXTI_InputLineNumber / 4)     ;
	AFIO_EXTICR_POS   = (EXTI_Config->EXTI_PIN.EXTI_InputLineNumber % 4) * 4 ;

	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~(0xF << AFIO_EXTICR_POS);
	AFIO->EXTICR[AFIO_EXTICR_Index] |= (((AFIO_GPIO_EXTI_MAPPING(EXTI_Config->EXTI_PIN.GPIO_Port) & 0xF) << AFIO_EXTICR_POS));


	/*
	 * 3- Configure the EXTI falling/rising registers based on the EXTI_Config values.
	 */
	EXTI->RTSR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	EXTI->FTSR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);


	if(EXTI_Config->TriggerCase == EXTI_TRIGGER_RISING)
	{
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}
	else if(EXTI_Config->TriggerCase == EXTI_TRIGGER_FALLING)
	{
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}
	else if(EXTI_Config->TriggerCase == EXTI_TRIGGER_RISING_AND_FALLING)
	{
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	}


	/*
	 * 4- Update the IRQ handling callback
	 */

	GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.EXTI_InputLineNumber] = EXTI_Config->P_IRQ_CallBack;


	/*
	 * 5- Enable / Disable IRQ for EXTI & NVIC
	 */

	if (EXTI_Config->IRQ_EN == EXTI_IRQ_ENABLE)
	{
		EXTI->IMR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber); 	/* EXTI interrupt Enable                           */
		NVIC_ENABLE(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);			/* NVIC Enable                          		   */

	}
	else if (EXTI_Config->IRQ_EN == EXTI_IRQ_DISABLE)
	{
		EXTI->IMR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);    /* EXTI interrupt Disable                           */
		NVIC_DISABLE(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);			/* NVIC Disable                          		   */

	}



}




/*
 * =====================================================================
 * 									APIs Functions Definitions
 * =====================================================================
 */

void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t *EXTI_Config)
{
	/**================================================================
	 * @Fn				- MCAL_EXTI_GPIO_Init
	 * @brief 			- Initializes the EXTI of a specific GPIO pin and specify the mask/trigger condition and IRQ callback
	 * @param [in] 		- EXTI_Config: Set based upon @ref EXTI define, @ref EXTI_Trigger_case and @ref EXTI_IRQ_define
	 * @retval 			- None
	 * Note				- STM32F103C6 MCU has GPIO A, B, C, D, E Modules
	 * 					  But LQFP48 package has only A, B and part of C, D exported as external pins from the MCU
	 *
	 */

	Update_EXTI(EXTI_Config);
}


void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t *EXTI_Config)
{
	/**================================================================
	 * @Fn				- MCAL_EXTI_GPIO_Update
	 * @brief 			- Initializes the EXTI of a specific GPIO pin and specify the mask/trigger condition and IRQ callback
	 * @param [in] 		- EXTI_Config: Set based upon @ref EXTI define, @ref EXTI_Trigger_case and @ref EXTI_IRQ_define
	 * @retval 			- None
	 * Note				- STM32F103C6 MCU has GPIO A, B, C, D, E Modules
	 * 					  But LQFP48 package has only A, B and part of C, D exported as external pins from the MCU
	 *
	 */

	Update_EXTI(EXTI_Config);
}







void MCAL_EXTI_GPIO_DeInit(void)
{
	/**================================================================
	 * @Fn				- MCAL_EXTI_GPIO_DeInit
	 * @brief 			- Reset EXTI registers and NVIC corresponding IRQ mask
	 * @param [in] 		- None
	 * @retval 			- None
	 */

	// Reset EXTI Registers

	EXTI->IMR 	= 0x00000000;
	EXTI->EMR 	= 0x00000000;
	EXTI->RTSR 	= 0x00000000;
	EXTI->FTSR 	= 0x00000000;
	EXTI->SWIER = 0x00000000;

	EXTI->PR	= 0xFFFFFFFF; /*PRx: Pending bit

								0: No trigger request occurred
								1: selected trigger request occurred
								This bit is set when the selected edge event arrives on the external interrupt line. This bit is
								cleared by writing a ‘1’ into the bit.
								*/


	// Reset NVIC Registers
		NVIC_IRQ6_EXTI0_DISABLE();
		NVIC_IRQ7_EXTI1_DISABLE();
		NVIC_IRQ8_EXTI2_DISABLE();
		NVIC_IRQ9_EXTI3_DISABLE();
		NVIC_IRQ10_EXTI4_DISABLE();

		NVIC_IRQ23_EXTI5_9_DISABLE();
		NVIC_IRQ40_EXTI10_15_DISABLE();
}



/*
 * =====================================================================================
 * 									Interrupt Service Routine (ISR)
 * =====================================================================================
 */

void EXTI0_IRQHandler()
{
	/* EXTI Line0 interrupt                             */

	EXTI->PR |= (1 << 0);
	GP_IRQ_CallBack[0]();
}

void EXTI1_IRQHandler()
{
	/* EXTI Line1 interrupt                             */

	EXTI->PR |= (1 << 1);
	GP_IRQ_CallBack[1]();
}

void EXTI2_IRQHandler()
{
	/* EXTI Line2 interrupt                             */

	EXTI->PR |= (1 << 2);
	GP_IRQ_CallBack[2]();
}

void EXTI3_IRQHandler()
{
	/* EXTI Line3 interrupt                             */

	EXTI->PR |= (1 << 3);
	GP_IRQ_CallBack[3]();
}

void EXTI4_IRQHandler()
{
	/* EXTI Line4 interrupt                             */

	EXTI->PR |= (1 << 4);
	GP_IRQ_CallBack[4]();
}

void EXTI9_5_IRQHandler()
{
	/* EXTI Line[9:5] interrupts                        */

	if(EXTI->PR & (1 << 5)){ EXTI->PR |= (1 << 5); GP_IRQ_CallBack[5](); }
	if(EXTI->PR & (1 << 6)){ EXTI->PR |= (1 << 6); GP_IRQ_CallBack[6](); }
	if(EXTI->PR & (1 << 7)){ EXTI->PR |= (1 << 7); GP_IRQ_CallBack[7](); }
	if(EXTI->PR & (1 << 8)){ EXTI->PR |= (1 << 8); GP_IRQ_CallBack[8](); }
	if(EXTI->PR & (1 << 9)){ EXTI->PR |= (1 << 9); GP_IRQ_CallBack[9](); }


}

void EXTI15_10_IRQHandler()
{
	/* EXTI Line[15:10] interrupts                      */

	if(EXTI->PR & (1 << 10)){ EXTI->PR |= (1 << 10); GP_IRQ_CallBack[10](); }
	if(EXTI->PR & (1 << 11)){ EXTI->PR |= (1 << 11); GP_IRQ_CallBack[11](); }
	if(EXTI->PR & (1 << 12)){ EXTI->PR |= (1 << 12); GP_IRQ_CallBack[12](); }
	if(EXTI->PR & (1 << 13)){ EXTI->PR |= (1 << 13); GP_IRQ_CallBack[13](); }
	if(EXTI->PR & (1 << 14)){ EXTI->PR |= (1 << 14); GP_IRQ_CallBack[14](); }
	if(EXTI->PR & (1 << 15)){ EXTI->PR |= (1 << 15); GP_IRQ_CallBack[15](); }

}



