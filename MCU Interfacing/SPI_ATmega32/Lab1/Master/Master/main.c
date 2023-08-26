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

void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);

int main(void)
{
	SPI_MasterInit();
    sei();
	while (1) 
    {
    	SPI_MasterTransmit('z');
		_delay_ms(100);
	}
}

void SPI_MasterInit(void)
{
	DDRB |= (1 << 7) | (1 << 5) | (1 << 4); // Set MOSI and SCK as output pins.
	PORTB &= ~(1 << 6); // Set MISO as input pin.
	PORTB |= (1 << 4); // Set SS to high.
	SPCR |=(1 << 7) | (1 << 6) | (1 << 4) | (1 << 2) | (1 << 0); // Enable SPI and set it as master with clock of Fosc/16.
}

void SPI_MasterTransmit(char cData)
{
	SPDR = cData;
	PORTB &= ~(1 << 4);
	//while(!(SPSR & (1<<SPIF)));
	//PORTB |= (1 << 4); // Set SS to high.
}

ISR(SPI_STC_vect)
{
	PORTB |= (1 << 4); // Set SS to high.
}