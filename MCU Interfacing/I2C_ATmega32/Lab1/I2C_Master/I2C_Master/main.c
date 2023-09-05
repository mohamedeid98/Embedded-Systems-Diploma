/*
 * I2C_Master.c
 * 
 * Author : Mohamed Eid
 */ 
#define F_CPU				8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#define START				0x08
#define MT_SLA_ACK			0x18
#define MT_DATA_ACK			0x28
#define SCL_Clock			100000U
#define PRESCALAR			1

void I2C_Init(void)
{
	switch(PRESCALAR)
	{
		case 1:
			TWSR = 0;
			break;
		case 4:
			TWSR = 1;
			break;
		case 16:
			TWSR = 2;
			break;
		case 64:
			TWSR = 3;
			break;
	}
	TWBR = ((F_CPU / SCL_Clock) - 16) / (2 * powf(4, (TWSR & 0x03)));
}

void I2C_Start(void)
{
	/* A START condition is sent by writing the following value to TWCR */
	TWCR |= (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	
	/* Poll until the interrupt status bit is set by hardware */
	while(!(TWCR & (1 << TWINT)));
	
	/* Check if the START condition has been transmitted */
	while ((TWSR & 0xF8) != START);
}

void I2C_WriteAdd(uint8_t Add)
{
	TWDR = Add;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	while ((TWSR & 0xF8) != MT_SLA_ACK);
}

void I2C_WriteData(uint8_t Data)
{
	TWDR = Data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	while ((TWSR & 0xF8) != MT_DATA_ACK);
}


void I2C_Stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

int main(void)
{
	char ch = 0;
	
	I2C_Init();

    while (1) 
    {
		
		I2C_Start();
		I2C_WriteAdd(0b11010000);
		I2C_WriteData(ch++);
		I2C_Stop();
		_delay_ms(500);
    }
}

