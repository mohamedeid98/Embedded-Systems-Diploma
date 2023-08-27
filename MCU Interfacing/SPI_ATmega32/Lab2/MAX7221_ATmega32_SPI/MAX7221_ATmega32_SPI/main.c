/*
 * Master.c
 *
 * Created: 8/26/2023 7:50:42 PM
 * Author : Mohamed Eid
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL

#include <Util/delay.h>
#include <avr/interrupt.h>

#define MOSI			5
#define SCK				7
#define SS				4
#define SPR0			0


void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
void excute(unsigned char byte1, unsigned char byte2);

int main(void)
{
	unsigned counter = 0;
	unsigned disp_idx;
	SPI_MasterInit();
    //sei();
	
	excute(0x09, 0xFF);
	excute(0x0B, 0x07);
	excute(0x0A, 0x0F);
	excute(0x0C, 0x01);
	
	while (1) 
    {
		for(disp_idx = 1 ; disp_idx < 9 ; disp_idx++)
		{
			excute(disp_idx, counter++);
			_delay_ms(1000);
			if(counter == 10)counter=0;
		}
	}
}

void SPI_MasterInit(void)
{
	DDRB |= (1 << 7) | (1 << 5) | (1 << 4); // Set MOSI and SCK as output pins.
	PORTB &= ~(1 << 6); // Set MISO as input pin.
	PORTB |= (1 << 4); // Set SS to high.
	SPCR |= (1 << 6) | (1 << 4) | (1 << 0); // Enable SPI and set it as master with clock of Fosc/16.
}

void SPI_MasterTransmit(char cData)
{
	SPDR = cData;
	while(!(SPSR & (1<<SPIF)));
}

void excute(unsigned char byte1, unsigned char byte2)
{
	PORTB &= ~(1 << 4);
	SPI_MasterTransmit(byte1);
	SPI_MasterTransmit(byte2);
	PORTB |= (1 << 4);
}