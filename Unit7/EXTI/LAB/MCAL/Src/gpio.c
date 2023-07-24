/*
 * gpio.c
 *
 *  Created on: Jun 30, 2023
 *      Author: Mohamed Eid
 */
#include "../Inc/gpio.h"


uint8_t Get_CRLH_Position (uint16_t PinNumber)
{
	switch(PinNumber)
	{
	// For CRL
		case GPIO_PIN0:return 0;break;
		case GPIO_PIN1:return 4;break;
		case GPIO_PIN2:return 8;break;
		case GPIO_PIN3:return 12;break;
		case GPIO_PIN4:return 16;break;
		case GPIO_PIN5:return 20;break;
		case GPIO_PIN6:return 24;break;
		case GPIO_PIN7:return 28;break;
	// For CRH
		case GPIO_PIN8:return 0;break;
		case GPIO_PIN9:return 4;break;
		case GPIO_PIN10:return 8;break;
		case GPIO_PIN11:return 12;break;
		case GPIO_PIN12:return 16;break;
		case GPIO_PIN13:return 20;break;
		case GPIO_PIN14:return 24;break;
		case GPIO_PIN15:return 28;break;

	}

	return 0;
}

void MCAL_GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig)
{
	/**================================================================
	* @Fn				- MCAL_GPIO_Init
	* @brief 			- Initializes the GPIOx PINy according to the specified parameters in the PinConfig
	* @param [in] 		- GPIOx: where x can be (A -> E depending on device used) to select the GPIO peripheral
	* @param [in] 		- PinConfig: pointer to a GPIO_PinConfig_t structure that contains the configuration of the pin
	* @retval 			- None
	* Note				- STM32F103C6 MCU has GPIO A, B, C, D, E Modules
	* 					  But LQFP48 package has only A, B and part of C, D exported as external pins from the MCU
	*/
	uint8_t temp_pinConfig;
	volatile uint32_t *ConfigRegister = NULL;

	ConfigRegister = (PinConfig->GPIO_PinNumber >= GPIO_PIN8) ? &GPIOx->CRH : &GPIOx->CRL; // Choose between CRL & CRH based on the pin number

	*ConfigRegister &= ~(0xF << (Get_CRLH_Position(PinConfig->GPIO_PinNumber))) ;  // Clear the bits before writing on them

	if((PinConfig->GPIO_PinMode == GPIO_MODE_OUTPUT_PP) || (PinConfig->GPIO_PinMode == GPIO_MODE_OUTPUT_OD) || (PinConfig->GPIO_PinMode == GPIO_MODE_OUTPUT_AF_PP) || (PinConfig->GPIO_PinMode == GPIO_MODE_OUTPUT_AF_OD))
	{
		temp_pinConfig = (((PinConfig->GPIO_PinMode - 4) << 2) | (PinConfig->GPIO_OutputSpeed)) & 0x0f ;
	}
	else
	{
		if ((PinConfig->GPIO_PinMode == GPIO_MODE_ANALOG) || (PinConfig->GPIO_PinMode == GPIO_MODE_INPUT_FLO))
		{
			temp_pinConfig = ((((PinConfig->GPIO_PinMode) << 2) | 0x0) & 0x0F);
		}
		else if (PinConfig->GPIO_PinMode == GPIO_MODE_AF_INPUT) // Is considered as GPIO_MODE_INPUT_FLO
		{
			temp_pinConfig = (((GPIO_MODE_INPUT_FLO << 2) | 0x0) & 0x0F);
		}
		else
		{
			temp_pinConfig = (((GPIO_MODE_INPUT_PU << 2) | 0x0) & 0x0F);

			if (PinConfig->GPIO_PinMode == GPIO_MODE_INPUT_PU)
			{
				GPIOx->ODR |= (PinConfig->GPIO_PinNumber);
			}
			else
			{
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}
		}
	}

	*ConfigRegister |= temp_pinConfig << (Get_CRLH_Position(PinConfig->GPIO_PinNumber));

}



void MCAL_GPIO_DeInit (GPIO_TypeDef *GPIOx)
{
	/**================================================================
	 * @Fn				- MCAL_GPIO_DeInit
	 * @brief 			- Reset the GPIOx registers
	 * @param [in] 		- GPIOx: where x can be (A -> E depending on device used) to select the GPIO peripheral
	 * @retval 			- None
	 * Note				- None
	 */

	if (GPIOx == GPIOA)			// IO port A reset
	{
		RCC->APB2RSTR |= (1 << 2);
		RCC->APB2RSTR &= ~(1 << 2);
	}
	else if (GPIOx == GPIOB)	// IO port B reset
	{
		RCC->APB2RSTR |= (1 << 3);
		RCC->APB2RSTR &= ~(1 << 3);
	}
	else if (GPIOx == GPIOC)    // IO port C reset
	{
		RCC->APB2RSTR |= (1 << 4);
		RCC->APB2RSTR &= ~(1 << 4);
	}
	else if (GPIOx == GPIOD)	// IO port D reset
	{
		RCC->APB2RSTR |= (1 << 5);
		RCC->APB2RSTR &= ~(1 << 5);
	}
	else if (GPIOx == GPIOE)	// IO port E reset
	{
		RCC->APB2RSTR |= (1 << 6);
		RCC->APB2RSTR &= ~(1 << 6);
	}


}


uint8_t MCAL_GPIO_ReadPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	/**================================================================
		* @Fn				- MCAL_GPIO_ReadPin
		* @brief 			- Read a specific pin
		* @param [in] 		- GPIOx: where x can be (A -> E depending on device used) to select the GPIO peripheral
		* @param [in] 		- PinNumber: The pin number to be read
		* @retval 			- The input pin value
		* Note				- None
		*/

	uint8_t bitStatus;

	if ((GPIOx->IDR & PinNumber) != 0)
		bitStatus = GPIO_PIN_SET;
	else
		bitStatus = GPIO_PIN_RESET;

	return bitStatus;
}


uint16_t MCAL_GPIO_ReadPort (GPIO_TypeDef *GPIOx)
{
	/**================================================================
			* @Fn				- MCAL_GPIO_ReadPort
			* @brief 			- Read a specific port
			* @param [in] 		- GPIOx: where x can be (A -> E depending on device used) to select the GPIO peripheral
			* @retval 			- The input port value
			* Note				- None
			*/

	return (uint16_t)GPIOx->IDR;
}


void MCAL_GPIO_WritePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t value)
{
	/**================================================================
		* @Fn				- MCAL_GPIO_WritePin
		* @brief 			- Write specific value on a specific pin
		* @param [in] 		- GPIOx: where x can be (A -> E depending on device used) to select the GPIO peripheral
		* @param [in] 		- PinNumber: The pin number to be written on
		* @param [in] 		- value: The value number to be written
		* @retval 			- None
		*/

	if (value == (GPIO_PIN_SET))
	{
		GPIOx->BSRR = (uint32_t)PinNumber;
	}
	else
	{
		GPIOx->BRR = (uint32_t)PinNumber;
	}
}


void MCAL_GPIO_WritePort (GPIO_TypeDef *GPIOx, uint16_t value)
{
	/**================================================================
		* @Fn				- MCAL_GPIO_WritePort
		* @brief 			- Write specific value on a specific port
		* @param [in] 		- GPIOx: where x can be (A -> E depending on device used) to select the GPIO peripheral
		* @param [in] 		- value: The value number to be written
		* @retval 			- None
		*/

	GPIOx->ODR = (uint32_t)value;
}

void MCAL_GPIO_TogglePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	/**================================================================
	 * @Fn				- MCAL_GPIO_TogglePin
	 * @brief 			- Toggle a specific pin
	 * @param [in] 		- GPIOx: where x can be (A -> E depending on device used) to select the GPIO peripheral
	 * @param [in] 		- PinNumber: The pin number to be toggled
	 * @retval 			- None
	 */

	GPIOx->ODR ^= (uint32_t)PinNumber;
}


uint8_t MCAL_GPIO_LockPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	/**================================================================
	 * @Fn				- MCAL_GPIO_LockPin
	 * @brief 			- Lock a specific pin
	 * @param [in] 		- GPIOx: where x can be (A -> E depending on device used) to select the GPIO peripheral
	 * @param [in] 		- PinNumber: The pin number to be locked
	 * @retval 			- None
	 */
	volatile uint32_t tmp = 1 << 16;
	tmp |= PinNumber;

	GPIOx->LCKR = tmp;
	GPIOx->LCKR = PinNumber;
	GPIOx->LCKR = tmp;

	tmp = GPIOx->LCKR;

	if((uint32_t)(GPIOx->LCKR & 1 << 16))
		return GPIO_RETURN_LOCK_ENABLED;
	else
		return GPIO_RETURN_LOCK_ENABLED;

	return 0;

}


