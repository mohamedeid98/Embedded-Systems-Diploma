/*
 * I2C_Slave.c
 *
 * Author : Mohamed Eid
 */ 
#define F_CPU				8000000UL

#include <avr/io.h>

#define SR_SLA_ACK			0x60
#define SR_DATA_ACK			0x80

void I2C_Init(uint8_t address)
{
	TWAR = address;
}

uint8_t I2C_Read(void)
{
	TWCR |= (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
	
	while(!(TWCR & (1 << TWINT)));
	while ((TWSR & 0xF8) != SR_SLA_ACK);

	TWCR |= (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
	while(!(TWCR & (1 << TWINT)));
	while ((TWSR & 0xF8) != SR_DATA_ACK);
	
	return TWDR;
}
int main(void)
{

	DDRA = 0XFF;
	I2C_Init(0b11010000);


    while (1) 
    {
		PORTA = I2C_Read();
    }
}

