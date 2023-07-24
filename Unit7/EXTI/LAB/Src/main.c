/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mohamed EId
 * @brief          : Main program body
 ******************************************************************************/


#include "../MCAL/Inc/gpio.h"
#include "../MCAL/Inc/exti.h"
#include "../HAL/Inc/lcd.h"

void callback_fun()
{
	LCD_write_string("IRQ EXTI9 is happened _|-");
}

int main(void)
{
	RCC_AFIO_CLK_EN();
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	LCD_init();


	EXTI_PinConfig_t EXTI_PIN_CONFIG;

	EXTI_PIN_CONFIG.EXTI_PIN = EXTI9PB9;
	EXTI_PIN_CONFIG.TriggerCase = EXTI_TRIGGER_RISING;
	EXTI_PIN_CONFIG.P_IRQ_CallBack = callback_fun;
	EXTI_PIN_CONFIG.IRQ_EN = EXTI_IRQ_ENABLE;

	MCAL_EXTI_GPIO_Init(&EXTI_PIN_CONFIG);

	while(1)
	{

	}
}
