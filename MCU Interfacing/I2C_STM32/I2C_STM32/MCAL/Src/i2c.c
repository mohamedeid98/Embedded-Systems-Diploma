/*
 * i2c.c
 *
 *      Author: Mohamed Eid
 */

/************************************************************************
								INCLUDES
 *************************************************************************/

#include "../Inc/i2c.h"




/************************************************************************
							  Generic Macros
 *************************************************************************/
#define I2C1_IDX					0
#define I2C2_IDX					1

#define _1MEGA						1000000U
#define DEFAULT_CLOCK_FRQUENCY		8000000U
/************************************************************************
							  Generic Variables
 *************************************************************************/
I2C_Config_t G_I2C_Config[2] = {{0}, {0}};


/************************************************************************
						APIs Supported by "MCAL I2C Driver"
 *************************************************************************/


void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_Config_t* I2C_Config)
{
	uint32_t tempreg ;
	uint32_t Input_clk_freq = DEFAULT_CLOCK_FRQUENCY;
	uint32_t CCR_Value;

	if (I2Cx == I2C1)
	{
		G_I2C_Config[I2C1_IDX] = *I2C_Config;
		RCC_I2C1_CLK_EN();
	}
	else if (I2Cx == I2C2)
	{
		G_I2C_Config[I2C2_IDX] = *I2C_Config;
		RCC_I2C2_CLK_EN();
	}

	if(I2C_Config->I2C_Mode == I2C_MODE_ENABLE)
	{

		/******************** INIT Timing ******************/

		/*	1- Program the peripheral input clock in I2C_CR2 Register
		 * 	   in order to generate correct timings  */

		/*		Get the I2Cx->CR2 Value   */
		tempreg = I2Cx->CR2;

		/* Clear frequency bits */
		tempreg &= ~(I2C_CR2_FREQ);

		/* Get PCLK1 frequency value */
		Input_clk_freq = MCAL_RCC_Get_PClk1_Freq();

		tempreg |= (Input_clk_freq / (_1MEGA));

		/* Update the CR2 with the clock value */
		I2Cx->CR2 = tempreg;


		/*  2- Configure the clock control registers */
		// In standard mode CCR = (Fpclk1 / (2 * Fi2c))

		/*Bit 15 F/S: I2C master mode selection
		0: Sm mode I2C
		1: Fm mode I2C*/

		I2Cx->CR1 &= ~(I2C_CR1_PE);

		tempreg = 0;

		if(I2C_Config->I2C_ClockSpeed == I2C_CLOCK_SM_50K || I2C_Config->I2C_ClockSpeed == I2C_CLOCK_SM_100K )
		{
			// Configure as standard mode
			tempreg &= ~(1 << 15);

			CCR_Value = (Input_clk_freq/ (I2C_Config->I2C_ClockSpeed << 1));
			tempreg |= CCR_Value;

			/* Write to CCR Register */
			I2Cx->CCR = tempreg;
		}
		else
		{
			//TODO FAST MODE
		}

		/*  3- Configure the rise time register */

		/*  Bits 5:0 TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode)
		    These bits must be programmed with the maximum SCL rise time given in the I2C bus
		    specification, incremented by 1  (Fpclk1 / 1MEGA + 1)*/

		I2Cx->TRISE = Input_clk_freq / _1MEGA + 1;


		/******************** I2C CR1 Configuration ******************/

		tempreg = I2Cx->CR1;

		tempreg |= I2C_Config->Stretch_Mode | I2C_Config->I2C_ACK_Control | I2C_Config->I2C_Mode;

		I2Cx->CR1 = tempreg ;


		/******************** I2C OAR1 & OAR2 Configuration ******************/
		tempreg = 0;

		if(I2C_Config->Slave_Address.DualAdd_Enable == 1)
		{
			tempreg |= I2C_OAR2_ENDUAL;
			tempreg |= (I2C_Config->Slave_Address.Address2 << 1);

			I2Cx->OAR2 = tempreg;

			tempreg = 0;

			if(I2C_Config->Slave_Address.Address_Mode == ADD_MODE_7_BITS)
			{
				tempreg |= ADD_MODE_7_BITS;
				tempreg |= I2C_Config->Slave_Address.Address1 << 1;
				I2Cx->OAR1 = tempreg;
			}
			else
			{
				// TODO ADD_MODE_10_BITS
			}
		}


	}
	else
	{
		//		TODO
		//		SMBUS NOT SUPPORTED
	}



	/***************** Interrupt Mode in slave mode *************/

	if(I2C_Config->P_Slave_Event_CallBack != NULL)
	{
		I2Cx->CR2 |= I2C_CR2_ITERREN;
		I2Cx->CR2 |= I2C_CR2_ITEVTEN;
		I2Cx->CR2 |= I2C_CR2_ITBUFEN;

		if(I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_ENABLE();
			NVIC_IRQ32_I2C1_ER_ENABLE();
		}
		else if(I2Cx == I2C2)
		{
			NVIC_IRQ33_I2C2_EV_ENABLE();
			NVIC_IRQ34_I2C2_ER_ENABLE();
		}

		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;

	}




	/* Program the I2C_CR1 register to enable the peripheral */
	I2Cx->CR1 |= I2C_CR1_PE;



}















void MCAL_I2C_DeInit(I2C_TypeDef* I2Cx)
{

	if (I2Cx == I2C1)
	{
		RCC_I2C1_CLK_RESET();
		NVIC_IRQ31_I2C1_EV_DISABLE();
		NVIC_IRQ32_I2C1_ER_DISABLE();
	}
	else if (I2Cx == I2C2)
	{
		RCC_I2C2_CLK_RESET();
		NVIC_IRQ33_I2C2_EV_DISABLE();
		NVIC_IRQ34_I2C2_ER_DISABLE();

	}
}

void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx)
{
	GPIO_PinConfig_t pinconfig;

	if (I2Cx == I2C1)
	{
		// SCL --> PORTB.6
		pinconfig.GPIO_PinNumber = GPIO_PIN6;
		pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_OD;
		pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &pinconfig);

		// SDA --> PORTB.7
		pinconfig.GPIO_PinNumber = GPIO_PIN7;
		pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_OD;
		pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &pinconfig);


	}
	else if (I2Cx == I2C2)
	{
		// SCL --> PORTB.10
		pinconfig.GPIO_PinNumber = GPIO_PIN10;
		pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_OD;
		pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &pinconfig);

		// SDA --> PORTB.11
		pinconfig.GPIO_PinNumber = GPIO_PIN11;
		pinconfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_OD;
		pinconfig.GPIO_OutputSpeed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &pinconfig);

	}


}


void MCAL_I2C_Master_Tx(I2C_TypeDef *I2Cx, uint16_t devAdd, uint8_t* dataOut, uint32_t dataLen, stopCondition I2C_stop, repeatedStart Start)
{
	int i = 0;

	/*------------------------------ Start Condition Generation ----------------------------------*/
	I2C_Generate_Start(I2Cx, ENABLE, start);
	while(!(I2C_GetFlagStatus(I2Cx, EV5))); /* Wait until the SB bit is set by hardware */


	/*------------------------------ Slave Address+Write operation ----------------------------------*/

	I2C_Write_Slave_Address(I2Cx, devAdd, I2C_write);
	while(!(I2C_GetFlagStatus(I2Cx, EV6))); /* Wait until the SB bit is set by hardware */

	/*------------------------------ Check TRA, BUSY, MSL, TXE FLAGS ----------------------------------*/
	while(!(I2C_GetFlagStatus(I2Cx, EV8_1)));

	/*------------------------------ Data Write ----------------------------------*/

	if (!(dataOut == NULL || dataLen == 0))
	{
		for (i = 0 ; i < dataLen; i++)
		{
			I2Cx->DR = dataOut[i];
			while(!(I2C_GetFlagStatus(I2Cx, EV8)));

		}
	}
	/*------------------------------ Check BTF ----------------------------------*/

//	Bit 2 BTF: Byte transfer finished
//	0: Data byte transfer not done
//	1: Data byte transfer succeeded
//	– Set by hardware when NOSTRETCH=0 and:
//	– In transmission when a new byte should be sent and DR has not been written yet (TxE=1).
//	– Cleared by software reading SR1 followed by either a read or write in the DR register or by
//	hardware after a start or a stop condition in transmission or when PE=0.
	while(!(I2C_GetFlagStatus(I2Cx, EV8_2)));

	/*------------------------------ Stop Condition Generation ----------------------------------*/
	if (I2C_stop == stopEnable)
	{
		I2C_Generate_Stop(I2Cx, ENABLE);
	}
}




/************************************************************************
								Generic APIs
*************************************************************************/
void I2C_Generate_Start(I2C_TypeDef* I2Cx, FunctionalState Newstate, repeatedStart Start)
{
	if (Start != repeated_start)
	{
		/* Check if the bus is idle */
		while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY) /*TODO Support timeout */);
	}
	/*Bit 8 START: Start generation
	This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
	In Master Mode:
	0: No Start generation
	1: Repeated start generation*/
	if(Newstate == ENABLE)
	{
		I2Cx->CR1 |= I2C_CR1_START;
	}
	else
	{
		I2Cx->CR1 &= ~(I2C_CR1_START);
	}
}



FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, FlagName flag)
{
	volatile uint32_t dummyRead;
	uint32_t flag1, flag2, lastevent;
	FlagStatus bitStatus = RESET;

	switch (flag)
	{
		case I2C_FLAG_BUSY:
			if (I2Cx->SR2 & I2C_SR2_BUSY)
				bitStatus = SET;
			else
				bitStatus = RESET;

			break;

//			Bit 0 SB: Start bit (Master mode)
//			0: No Start condition
//			1: Start condition generated.
//			– Set when a Start condition generated.
//			– Cleared by software by reading the SR1 register followed by writing the DR register, or by
//			hardware when PE=0
		case EV5:
			if (I2Cx->SR1 & I2C_SR1_SB)
			{
				bitStatus = SET;
			}
			else
				bitStatus = RESET;

			break;

/*			ADDR=1, cleared by reading SR1 register followed by reading SR2.	*/
		case EV6:
			if (I2Cx->SR1 & I2C_SR1_ADDR)
			{
				bitStatus = SET;
				dummyRead = I2Cx->SR2;
			}
			else
				bitStatus = RESET;

			break;

		case EV8_1:
			flag1 = I2Cx->SR1;
			flag2 = I2Cx->SR2;
			flag2 = flag2 << 16;
			lastevent = (flag1 | flag2) & ((uint32_t)0x00FFFFFF);
			if((lastevent & (EV8_1)) == flag)
			{
				bitStatus = SET;
			}
			else
			{
				bitStatus = RESET;
			}
			break;

		case EV8:
			if(I2Cx->SR1 & (I2C_SR1_TXE))
			{
				bitStatus = SET;
			}
			else
			{
				bitStatus = RESET;
			}
			break;

		case EV8_2:
			if(I2Cx->SR1 & (I2C_SR1_BTF))
			{
				bitStatus = SET;
			}
			else
			{
				bitStatus = RESET;
			}
			break;

		case EV7:
			if(I2Cx->SR1 & (I2C_SR1_RXNE))
			{
				bitStatus = SET;
			}
			else
			{
				bitStatus = RESET;
			}
			break;
	}


	return bitStatus;
}


void I2C_Write_Slave_Address(I2C_TypeDef* I2Cx, uint16_t address, I2C_flowDirection direction)
{
	address = (address << 1);

	if (direction == I2C_write)
	{
		address &= ~(1 << 0); /* clear the address bit0 for write */
	}
	else
	{
		address |= (1 << 0); /* set the address bit 1 for read operation */
	}
	I2Cx->DR = address;  /* send the address */
}


void I2C_Generate_Stop(I2C_TypeDef* I2Cx, FunctionalState Newstate)
{
	if(Newstate == ENABLE)
	{
		I2Cx->CR1 |= I2C_CR1_STOP;
	}
	else
	{
		I2Cx->CR1 &= ~(I2C_CR1_STOP);

	}
}


void MCAL_I2C_Master_Rx(I2C_TypeDef *I2Cx, uint16_t devAdd, uint8_t* dataOut, uint32_t dataLen, stopCondition I2C_stop, repeatedStart Start)
{

	int i = 0;

	/*------------------------------ Start Condition Generation ----------------------------------*/
	I2C_Generate_Start(I2Cx, ENABLE, Start);
	while(!(I2C_GetFlagStatus(I2Cx, EV5))); /* Wait until the SB bit is set by hardware */


	/*------------------------------ Slave Address+Write operation ----------------------------------*/

	I2C_Write_Slave_Address(I2Cx, devAdd, I2C_read);
	while(!(I2C_GetFlagStatus(I2Cx, EV6))); /* Wait until the SB bit is set by hardware */


	/*------------------------------ Data Read ----------------------------------*/

	if (!(dataOut == NULL || dataLen == 0))
	{
		for (i = dataLen ; i > 1; i--)
		{
			while(!(I2C_GetFlagStatus(I2Cx, EV7)));
			*dataOut = I2Cx->DR ;
			dataOut++;
		}

		I2Cx->CR1 &= ~(I2C_CR1_ACK); /*To generate the nonacknowledge pulse after the last received data byte, the ACK bit
									   must be cleared just after reading the second last data byte (after second last RxNE
									   event).*/

		while(!(I2C_GetFlagStatus(I2Cx, EV7)));
		*dataOut = I2Cx->DR ; /* Receive last byte */


	}

	/*------------------------------ Stop Condition Generation ----------------------------------*/

	if (I2C_stop == stopEnable)
	{
		I2C_Generate_Stop(I2Cx, ENABLE);
	}

	I2Cx->CR1 |= (I2C_CR1_ACK);

}





















