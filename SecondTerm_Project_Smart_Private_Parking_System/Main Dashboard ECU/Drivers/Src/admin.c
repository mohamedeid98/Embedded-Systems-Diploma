/*
 * admin.c
 *
 *      Author: Mohamed Eid
 */


#include "../Inc/admin.h"

#define IDs_BASE_ADDRESS	100
#define MAX_IDs				3

uint8_t ADMIN_PASSWORD[] = {1, 2, 3, 4 , 5};

uint8_t ID_COUNTER;
uint8_t Saved_IDs[9];

EXTI_PinConfig_t EXTI1_Config;
EXTI_PinConfig_t EXTI2_Config;

static uint8_t SavedIDsCounter=0;

extern uint8_t Available_Slots;

void (*P_func)(void);

void ADMIN_DefaultMessage()
{
	LCD_send_command(CLEAR_DISPLAY_SCREEN);
	MCAL_TIM2_Delay_mS(200);

	LCD_print((uint8_t*)"Welcome!!!");
	LCD_gotoxy(1, 2);
	LCD_print((uint8_t*)"Private Parking");

	LCD_gotoxy(1, 3);
	LCD_print((uint8_t*)"SW1- Add IDs");
	LCD_gotoxy(1, 4);
	LCD_print((uint8_t*)"SW2- Delete IDs");
}



void ADMIN_Check_Password()
{
	uint8_t i, flag=1;

	if(EXTI->PR & (1 << EXTI1_Config.EXTI_PIN.EXTI_InputLineNumber))
	{
		EXTI->PR |= (1 << 6);
		EXTI->IMR &= ~(1 << EXTI1_Config.EXTI_PIN.EXTI_InputLineNumber);    /* EXTI interrupt Disable */
		P_func = ADMIN_Add_IDs;

	}
	else if (EXTI->PR & (1 << EXTI2_Config.EXTI_PIN.EXTI_InputLineNumber))
	{
		EXTI->PR |= (1 << 10);
		EXTI->IMR &= ~(1 << EXTI2_Config.EXTI_PIN.EXTI_InputLineNumber);    /* EXTI interrupt Disable */
		P_func = ADMIN_Delete_Entire_IDs;

	}

	uint8_t dig='#', digCount=0;
	uint8_t passBuffer[5]={0};

	LCD_send_command(CLEAR_DISPLAY_SCREEN);
	MCAL_TIM2_Delay_mS(200);

	LCD_print((uint8_t*)"Enter password ");
	LCD_gotoxy(1, 2);

	while((dig == '#' || digCount < 5))
	{
		dig = HAL_Keypad_GetKey();
		if(dig != '#' && dig != '*')
		{
			LCD_send_data('*');
			passBuffer[digCount] = (dig);
			//MCAL_USART_Send(USART2, dig+48, USART_polling_enable);
			digCount++;
		}

	}
	MCAL_TIM2_Delay_mS(200);

	for (i = 0 ; i < 5 ; i++)
	{
		if(passBuffer[i] != ADMIN_PASSWORD[i])
			flag=0;
	}
	if(flag)
	{
		LCD_send_command(CLEAR_DISPLAY_SCREEN);
		MCAL_TIM2_Delay_mS(200);

		LCD_print((uint8_t*)"Authorized!");
		MCAL_TIM2_Delay_mS(500);

		P_func();
	}

	else
	{
		LCD_send_command(CLEAR_DISPLAY_SCREEN);
		MCAL_TIM2_Delay_mS(200);

		LCD_print((uint8_t*)"Error Wrong Password");
		MCAL_TIM2_Delay_mS(500);
		ADMIN_DefaultMessage();
	}

	EXTI->IMR |= (1 << EXTI1_Config.EXTI_PIN.EXTI_InputLineNumber); 	/* EXTI interrupt Enable */
	EXTI->IMR |= (1 << EXTI2_Config.EXTI_PIN.EXTI_InputLineNumber); 	/* EXTI interrupt Enable */


}



void ADMIN_Add_IDs()
{
	uint8_t IDs_Buffer[MAX_IDs];
	uint8_t i;
	uint8_t ID_count='#', ID_Number='#';
	/* 1- Disable all interrupts so that the system can get the IDs and store them correctly */
	//TODO

	/* 2-  Clear display and print some messages*/
	LCD_send_command(CLEAR_DISPLAY_SCREEN);
	MCAL_TIM2_Delay_mS(200);

	//LCD_gotoxy(1, 1);
	LCD_print((uint8_t*)"Enter Number of IDs");
	LCD_gotoxy(1, 2);
	LCD_print((uint8_t*)"Max 3 at a time: ");

	while(ID_count == '#')
	{
		ID_count = HAL_Keypad_GetKey();
	}


	LCD_print_int_number(ID_count);
	MCAL_TIM2_Delay_mS(300);
	LCD_send_command(CLEAR_DISPLAY_SCREEN);
	MCAL_TIM2_Delay_mS(200);

	for(i = 1 ; i <= ID_count ; i++)
	{
		LCD_gotoxy(1, i);
		LCD_print((uint8_t*)"Enter ID: ");

		while(ID_Number == '#')
		{
			ID_Number = HAL_Keypad_GetKey();
		}
		Saved_IDs[SavedIDsCounter++] = ID_Number;   // Save the IDs into an array to pass it later to the RFID
													// To avoid access the EEPROM each time reading RFID card.
		IDs_Buffer[i-1] = ID_Number;
		LCD_print_int_number(ID_Number);
		ID_Number = '#';

	}

	HAL_SPI_EEPROM_Write(SPI1, (IDs_BASE_ADDRESS+ID_COUNTER), IDs_Buffer, ID_count);

	LCD_send_command(CLEAR_DISPLAY_SCREEN);
	MCAL_TIM2_Delay_mS(200);

	LCD_print((uint8_t*)"IDs Saved Correctly!");
	MCAL_TIM2_Delay_mS(300);

	//ADMIN_Display_IDs();

	ADMIN_DefaultMessage();

	ID_COUNTER += ID_count;


}


void ADMIN_Delete_Entire_IDs()
{

	ID_COUNTER = 0;
	SavedIDsCounter=0;

	LCD_send_command(CLEAR_DISPLAY_SCREEN);
	MCAL_TIM2_Delay_mS(200);

	LCD_print((uint8_t*)"Deleted successfully");
	MCAL_TIM2_Delay_mS(1000);

	Available_Slots = 3;
	HAL_7SEG_Update(Available_Slots);

	ADMIN_DefaultMessage();


}


void ADMIN_Init()
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

	MCAL_TIM2_Init();

	/************ 1- Initialize external interrupt for "Add IDs Push Button" ****************/

	EXTI1_Config.EXTI_PIN 		= EXTI6PB6;
	EXTI1_Config.TriggerCase 	= EXTI_TRIGGER_RISING;
	EXTI1_Config.IRQ_EN			= EXTI_IRQ_ENABLE;
	EXTI1_Config.P_IRQ_CallBack	= ADMIN_Check_Password;

	MCAL_EXTI_GPIO_Init(&EXTI1_Config);

	/************ 2- Initialize external interrupt for "Delete IDs Push Button" ****************/
	EXTI2_Config.EXTI_PIN 		= EXTI10PB10;
	EXTI2_Config.TriggerCase 	= EXTI_TRIGGER_RISING;
	EXTI2_Config.IRQ_EN			= EXTI_IRQ_ENABLE;
	EXTI2_Config.P_IRQ_CallBack	= ADMIN_Check_Password;

	MCAL_EXTI_GPIO_Init(&EXTI2_Config);


	LCD_Init();					// Initialize LCD
	HAL_Keypad_Init();			// Initialize Keypad
	HAL_SPI_EEPROM_Init(SPI1);	// Initialize EEPROM

	/************ 3- Display the default message for ADMIN LCD  ****************/
	ADMIN_DefaultMessage();

	MCAL_TIM2_Delay_mS(200);


}


void ADMIN_Display_IDs(void)
{
	uint8_t SavedIDsBuffer[64];
	uint8_t i;

	LCD_send_command(CLEAR_DISPLAY_SCREEN);
	MCAL_TIM2_Delay_mS(200);



	if(ID_COUNTER > 0)
	{
		HAL_SPI_EEPROM_Read(SPI1, IDs_BASE_ADDRESS, SavedIDsBuffer, ID_COUNTER);

		LCD_print((uint8_t*)"Saved IDs...");
		for(i = 0 ; i < ID_COUNTER ; i++)
		{
			LCD_gotoxy(1, i+2);
			LCD_print((uint8_t*)"ID Number: ");
			LCD_print_int_number(SavedIDsBuffer[i]);

		}
	}

	else
	{
		LCD_print((uint8_t*)"No IDs Saved..!");
	}

	MCAL_TIM2_Delay_mS(2000);

	/************ 3- Display the default message for ADMIN LCD  ****************/
	//ADMIN_DefaultMessage();
}










