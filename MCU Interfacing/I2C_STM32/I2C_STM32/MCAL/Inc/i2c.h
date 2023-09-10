/*
 * i2c.h
 *
 *  Created on: Sep 9, 2023
 *      Author: Mohamed
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

/************************************************************************
								INCLUDES
*************************************************************************/
#include "gpio.h"
#include "rcc.h"

/************************************************************************
						 Generic Structs&&enums
*************************************************************************/

#define I2C_EVENT_MASTER_BYTE_TRANSMITTER		(uint32_t)0x00070080


typedef enum
{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_ADD_Matched,
	I2C_EV_DATA_REQ, /* The APP should send data using SendData API */
	I2C_EV_DATA_RCV  /* The APP should receive the data using ReceiveData API */

}Slave_State;


typedef enum
{
	stopEnable,
	stopDisable
}stopCondition;

typedef enum
{
	start,
	repeated_start
}repeatedStart;


typedef enum
{
	ENABLE,
	DISABLE
}FunctionalState;


typedef enum
{
	RESET,
	SET
}FlagStatus;


typedef enum
{
	I2C_FLAG_BUSY=0, /* Indicate if the bus is idle or taking by another master */

	EV5,	/* EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address. */

	EV6, 	/*	EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2. */

	EV8, 	/*	EV8: TxE=1, shift register not empty, d . ata register empty, cleared by writing DR register */

	EV8_2,  /* EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition */

	EV7,    /* RXNE=1 cleared by reading DR register. */

	EV8_1 = I2C_EVENT_MASTER_BYTE_TRANSMITTER

}FlagName;


typedef enum
{
	I2C_write,
	I2C_read
}I2C_flowDirection;


/************************************************************************
						 Configuration Structure
*************************************************************************/

struct I2C_Slave_Address
{
	uint32_t 					Address_Mode; 			/*!< Specifies the 7-bit or 10-bit address mode.
										 	 	 	 	 	 This parameter can be a value of @ref ADD_MODE_define */

	uint32_t 					DualAdd_Enable; 		/* 1 to enable, 0 to disable */

	uint32_t 					Address1;
	uint32_t 					Address2;
};



typedef struct
{

	uint32_t 					I2C_ClockSpeed;		 /*!< Specifies the clock frequency.
                                  	 	 	 	 	 	  This parameter must be set to a value lower than 100kHz.
                                  	 	 	 	 	 	  This parameter can be a value of @ref I2C_ClockSpeed_define */

	uint32_t 					Stretch_Mode; 		/*!< Specifies if nostretch mode is selected.
                                	 	 	 	 	 	 This parameter can be a value of @ref I2C_nostretch_mode */

	uint32_t 					I2C_Mode;			/*!< Specifies the mode I2C OR SMBUS
	 	 	 	 	 	 	 	 	 	 	 	 	 	 This parameter can be a value of @ref I2C_Mode_define */


	uint32_t 					I2C_ACK_Control;	/*!< Specifies the auto acknowledge enable or disable
	 	 	 	 	 	 	 	 	 	 	 	 	 	 This parameter can be a value of @ref I2C_ACK_define */

	struct I2C_Slave_Address	Slave_Address;


	void (*P_Slave_Event_CallBack)(Slave_State state);

}I2C_Config_t;




/************************************************************************
							Reference Macros
*************************************************************************/


/* @ref I2C_nostretch_mode */

#define I2C_NOSTRETCH_MODE_ENABLE							I2C_CR1_NOSTRETCH
#define I2C_NOSTRETCH_MODE_DISABLE							(0x00000000U)

/* @ref I2C_ClockSpeed_define */

#define I2C_CLOCK_SM_50K									(50000U)
#define I2C_CLOCK_SM_100K									(100000U)


/* @ref I2C_Mode_define */

#define I2C_MODE_ENABLE										(0x00000000U)
#define SMBUS_MODE_ENABLE									I2C_CR1_SMBUS


/* @ref I2C_ACK_define */


#define I2C_ACK_ENABLE										I2C_CR1_ACK
#define I2C_ACK_DISABLE										(0x00000000U)

/*@ref ADD_MODE_define*/
#define ADD_MODE_7_BITS										(0x00000000U)
#define ADD_MODE_10_BITS									(1 << 15)




/************************************************************************
						APIs Supported by "MCAL I2C Driver"
*************************************************************************/

void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_Config_t* I2C_Config);
void MCAL_I2C_DeInit(I2C_TypeDef* I2Cx);

void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx);

void MCAL_I2C_Master_Tx(I2C_TypeDef *I2Cx, uint16_t devAdd, uint8_t* dataOut, uint32_t dataLen, stopCondition I2C_stop, repeatedStart Start);
void MCAL_I2C_Master_Rx(I2C_TypeDef *I2Cx, uint16_t devAdd, uint8_t* dataOut, uint32_t dataLen, stopCondition I2C_stop, repeatedStart Start);


/************************************************************************
								Generic APIs
*************************************************************************/

void I2C_Generate_Start(I2C_TypeDef* I2Cx, FunctionalState Newstate, repeatedStart Start);
void I2C_Generate_Stop(I2C_TypeDef* I2Cx, FunctionalState Newstate);

void I2C_Write_Slave_Address(I2C_TypeDef* I2Cx, uint16_t address, I2C_flowDirection direction);

FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, FlagName flag);

#endif /* INC_I2C_H_ */
