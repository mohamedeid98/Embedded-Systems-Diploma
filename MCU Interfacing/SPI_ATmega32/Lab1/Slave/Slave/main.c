/*
 * Slave.c
 *
 * Created: 8/26/2023 7:51:20 PM
 * Author : Mohamed Eid
 */ 



#include "lcd.h"

void SPI_SlaveInit(void);
char SPI_SlaveReceive(void);

int main(void)
{
	char data;
	
	LCD_init();
	SPI_SlaveInit();
    sei();

	while (1) 
    {
		//data = SPI_SlaveReceive();
	    //LCD_write_char(data);
    }
}

void SPI_SlaveInit(void)
{
	PORTB |= (1 << 6) ; // Set MISO as output pin.
	PORTB &= ~(1 << 7) | (1 << 5) | (1 << 4); // Set other pins as input.
	
	SPCR |= (1 << 7) | (1 << 6) | (1 << 2); // Enable SPI and corresponding interrupt.
}


char SPI_SlaveReceive(void)
{
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}



ISR(SPI_STC_vect)
{
	LCD_write_char(SPDR);
}