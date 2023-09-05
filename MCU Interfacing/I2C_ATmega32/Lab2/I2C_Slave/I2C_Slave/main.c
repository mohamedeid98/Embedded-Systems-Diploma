/*
 * I2C_Slave.c
 *
 * Author : Mohamed Eid
 */ 
#define F_CPU				8000000UL

#include <avr/io.h>


#define ST_SLA_ACK			0xA8
#define ST_DATA_NACK			0xC0

void I2C_Init(uint8_t address)
{
	TWAR = address;
}

void I2C_Transmit(uint8_t Data)
{
	TWCR |= (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
		/* TWI waits until it is addressed by its own	slave address*/
	while(!(TWCR & (1 << TWINT))); 	
	while ((TWSR & 0xF8) != ST_SLA_ACK);

	TWDR = Data;
	TWCR |= (1 << TWINT) | (1 << TWEN);
	while(!(TWCR & (1 << TWINT)));
	while ((TWSR & 0xF8) != ST_DATA_NACK);
	
}


int main(void)
{

	uint8_t ch = 0;
	I2C_Init(0b11010000);


    while (1) 
    {
		I2C_Transmit(ch++);
    }
}

