/*
 * uart.h
 *
 *  Created on: Aug 9, 2023
 *      Author: Mohamed Eid
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "gpio.h"
#include "rcc.h"

// ----------------------------------
// Includes
// ----------------------------------

#endif /* INC_UART_H_ */

// =================================================================================

// ----------------------------------
// User Type Definitions
// ----------------------------------


typedef struct
{
	uint8_t 		USART_Mode; 		// Specifies the Tx/Rx mode
										// This parameter must be set based on the @ref USART_Mode_define

	uint32_t		BaudRate;			// Specifies the data rate
										// This parameter must be set based on the @ref USART_BuadRate_define

	uint8_t 		Payload_Length;		// Specifies the word length
										// This parameter must be set based on the @ref USART_Payload_define

	uint8_t 		Parity;				// Specifies the parity selection
										// This parameter must be set based on the @ref USART_Parity_define

	uint8_t 		Stop;				// Specifies the number of stop bits
										// This parameter must be set based on the @ref USART_Stop_define

	uint8_t 		HwFlowCtl;			// Specifies whether the hardware flow control mode is enabled or disabled
										//@ref UART_HwFlowCtl_define

	uint8_t 		IRQ_Enable;			// Enable or disable USART Tx/Rx IRQ
										// This parameter must be set based on the @ref USART_IRQ_Enable_define


	void (*P_IRQ_CallBack)(void);		//Set the C Function() which will be called once the IRQ  Happen

}USART_Config_t;




// =====================================================================================

// -------------------------------------
// Reference Macros
// -------------------------------------

// @ref USART_Mode_define

#define USART_Mode_Tx						(uint32_t)(1 << 3) // Set TE bit in USART_CR1
#define USART_Mode_Rx						(uint32_t)(1 << 2) // Set RE bit in USART_CR1
#define USART_Mode_Tx_Rx					(uint32_t)(1 << 3 | 1 << 2) // Set TE bit in USART_CR1


// @ref USART_BuadRate_define

#define USART_BuadRate_2400									2400
#define USART_BuadRate_9600									9600
#define USART_BuadRate_19200								19200
#define USART_BuadRate_57600								57600
#define USART_BuadRate_115200								115200
#define USART_BuadRate_230400								230400
#define USART_BuadRate_460800								460800
#define USART_BuadRate_921600								921600
#define USART_BuadRate_2250000								2250000
#define USART_BuadRate_4500000								4500000


// @ref USART_Payload_define

#define USART_Payload_8_bits				(uint32_t)(0)
#define USART_Payload_9_bits				(uint32_t)(1 << 12)


// @ref USART_Parity_define

#define USART_Parity_disabled				(uint32_t)(0)
#define USART_Parity_Even					(uint32_t)(1 << 10)
#define USART_Parity_Odd					(uint32_t)(1 << 9 | 1 << 10)


// @ref USART_Stop_define

#define USART_Stop__1						(uint32_t)(0)
#define USART_Stop__half					(uint32_t)(1 << 12)
#define USART_Stop__2						(uint32_t)(2 << 12)
#define USART_Stop__1_half					(uint32_t)(3 << 12)


// @ref UART_HwFlowCtl_define

#define UART_HwFlowCtl_NONE                  (uint32_t)(0)
#define UART_HwFlowCtl_RTS                   ((uint32_t)1<<8)
#define UART_HwFlowCtl_CTS                   ((uint32_t)1<<9)
#define UART_HwFlowCtl_RTS_CTS               ((uint32_t)(1<<8 | 1<<9))

// @ref USART_IRQ_Enable_define

#define USART_IRQ_Enable_NONE				(uint32_t)(0)
#define USART_IRQ_Enable_TXEIE				(uint32_t)(1 << 7)
#define USART_IRQ_Enable_TCIE				(uint32_t)(1 << 6)
#define USART_IRQ_Enable_PEIE				(uint32_t)(1 << 8)
#define USART_IRQ_Enable_RXNEIE 			(uint32_t)(1 << 5)


//BaudRate Calculation
//USARTDIV = fclk / (16 * Baudrate)
//USARTDIV_MUL100 =
// uint32((100 *fclk ) / (16 * Baudrate) == (25 *fclk ) / (4* Baudrate) )
//DIV_Mantissa_MUL100 = Integer Part (USARTDIV  )  * 100
//DIV_Mantissa = Integer Part (USARTDIV  )
//DIV_Fraction = (( USARTDIV_MUL100  - DIV_Mantissa_MUL100  ) * 16 ) / 100

#define USARTDIV(_PCLK_, _BAUD_)							(uint32_t) (_PCLK_/(16 * _BAUD_ ))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)						(uint32_t) ( (25 * _PCLK_ ) / (4  * _BAUD_ ))
#define Mantissa_MUL100(_PCLK_, _BAUD_)						(uint32_t) (USARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_, _BAUD_)							(uint32_t) (USARTDIV(_PCLK_, _BAUD_) )
#define DIV_Fraction(_PCLK_, _BAUD_)						(uint32_t) (((USARTDIV_MUL100(_PCLK_, _BAUD_) -  Mantissa_MUL100(_PCLK_, _BAUD_) ) * 16 ) / 100 )
#define UART_BRR_Register(_PCLK_, _BAUD_)					(( Mantissa (_PCLK_, _BAUD_) ) <<4 )|( (DIV_Fraction(_PCLK_, _BAUD_)) & 0xF )


typedef enum Polling_mechism{
	enable ,
	disable
}Polling_mechism;
// =====================================================================================


/*
* ===============================================
* APIs Supported by "MCAL USART DRIVER"
* ===============================================
*/


void MCAL_USART_Init(USART_TypeDef *USARTx, USART_Config_t* USART_Config);
void MCAL_USART_DeInit(USART_TypeDef *USARTx);


void MCAL_USART_Send(USART_TypeDef *USARTx, uint16_t *pTxBuffer, Polling_mechism PollingEn);
void MCAL_USART_Receive(USART_TypeDef *USARTx, uint16_t *pRxBuffer, Polling_mechism PollingEn);













