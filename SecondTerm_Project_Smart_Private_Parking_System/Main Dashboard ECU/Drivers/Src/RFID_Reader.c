/*
 * RFID_Reader.c
 *
 *      Author: Mohamed Eid
 */


#include "../Inc/RFID_Reader.h"


USART_Config_t UART1_Config;
USART_Config_t UART2_Config;

extern uint8_t ID_COUNTER;
extern uint8_t Saved_IDs[9];


typedef enum
{
	OPEN_AUTHORIZED		=1,
	UNAUTHORIZED		=2,
	NO_AVAILABLE_SLOTS	=3

}SPI_COMMAND;

uint8_t Available_Slots;

typedef enum
{
	EXIT_GATE,
	ENTRANCE_GATE
}GATE;

void RFID_Init()
{
	Available_Slots = 3;

	/***************************** Initialize UART1 ***********************************************/
	UART1_Config.USART_Mode				= USART_Mode_Tx_Rx;
	UART1_Config.BaudRate				= USART_BuadRate_9600;
	UART1_Config.HwFlowCtl				= UART_HwFlowCtl_NONE;
	UART1_Config.Parity					= USART_Parity_disabled;
	UART1_Config.Payload_Length			= USART_Payload_8_bits;
	UART1_Config.Stop					= USART_Stop__1;
	UART1_Config.IRQ_Enable				= USART_IRQ_Enable_RXNEIE;
	UART1_Config.P_IRQ_CallBack			= RFID_Entrance_Reader;

	MCAL_USART_Init(USART1, &UART1_Config);

	/***************************** Initialize UART2 ***********************************************/
	UART2_Config.USART_Mode				= USART_Mode_Tx_Rx;
	UART2_Config.BaudRate				= USART_BuadRate_9600;
	UART2_Config.HwFlowCtl				= UART_HwFlowCtl_NONE;
	UART2_Config.Parity					= USART_Parity_disabled;
	UART2_Config.Payload_Length			= USART_Payload_8_bits;
	UART2_Config.Stop					= USART_Stop__1;
	UART2_Config.IRQ_Enable				= USART_IRQ_Enable_RXNEIE;
	UART2_Config.P_IRQ_CallBack			= RFID_Exit_Reader;

	MCAL_USART_Init(USART2, &UART2_Config);
	/*********************** Configure Slave Select for Entrance Gate ****************************/

	// Use PIN11 of PORTA to act as software configured slave select signal.
	GPIO_PinConfig_t pinconfig;

	pinconfig.GPIO_PinMode		= GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_PinNumber	= GPIO_PIN11;
	pinconfig.GPIO_OutputSpeed	= GPIO_SPEED_10M;

	MCAL_GPIO_Init(GPIOA, &pinconfig);

	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN11, GPIO_PIN_SET);

	/*********************** Configure Slave Select for Exit Gate ****************************/

	// Use PIN11 of PORTB to act as software configured slave select signal.

	pinconfig.GPIO_PinMode		= GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_PinNumber	= GPIO_PIN11;
	pinconfig.GPIO_OutputSpeed	= GPIO_SPEED_10M;

	MCAL_GPIO_Init(GPIOB, &pinconfig);

	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN11, GPIO_PIN_SET);


	/***************************** Initialize 7SEG Display ****************************************/
	HAL_7SEG_Init();
	HAL_7SEG_Update(Available_Slots);
}

SPI_COMMAND ID_Check(uint8_t ID, GATE gate)
{
	int i;

	for (i = 0 ; i < ID_COUNTER ; i++)
	{
		if(ID == Saved_IDs[i])
		{
			if(gate == ENTRANCE_GATE)
			{
				if(Available_Slots > 0)
				{
					return OPEN_AUTHORIZED;
				}
				else
				{
					return NO_AVAILABLE_SLOTS;
				}
			}
			else if(gate == EXIT_GATE)
			{
				return OPEN_AUTHORIZED;
			}
		}

	}

	return UNAUTHORIZED;
}

void RFID_Entrance_Reader()
{
	uint16_t ID;
	uint8_t GateCommand;

	// Read the ID sent over UART.
	MCAL_USART_Receive(USART1, &ID, USART_polling_disable);

	/* Check if it is an authorized ID or not, and get the appropriate command to be sent the gate. */
	GateCommand = (uint8_t)ID_Check((ID-48), ENTRANCE_GATE);

	/* Send the command to the gate controller over SPI */
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN11, GPIO_PIN_RESET);
	MCAL_SPI_Send(SPI1, GateCommand, Polling_Enable);	 // Send write enable instruction.
	//MCAL_TIM2_Delay_mS(5);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN11, GPIO_PIN_SET);

	if(GateCommand == OPEN_AUTHORIZED)
	{
		Available_Slots--;

		/* Update the 7SEG Display with the available slots */
		HAL_7SEG_Update(Available_Slots);
	}
}




void RFID_Exit_Reader()
{
	uint16_t ID;
	uint8_t GateCommand;

	if(Available_Slots < 3)
	{
		// Read the ID sent over UART.
		MCAL_USART_Receive(USART2, &ID, USART_polling_disable);

		/* Check if it is an authorized ID or not, and get the appropriate command to be sent the gate. */
		GateCommand = (uint8_t)ID_Check((ID-48), EXIT_GATE);

		/* Send the command to the gate controller over SPI */
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN11, GPIO_PIN_RESET);
		MCAL_SPI_Send(SPI1, GateCommand, Polling_Enable);	 // Send write enable instruction.
		//MCAL_TIM2_Delay_mS(5);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN11, GPIO_PIN_SET);

		if(GateCommand == OPEN_AUTHORIZED)
		{
			Available_Slots++;

			/* Update the 7SEG Display with the available slots */
			HAL_7SEG_Update(Available_Slots);
		}
	}
}






