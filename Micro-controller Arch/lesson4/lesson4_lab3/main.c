/*
 * main.c
 *
 *  Created on: Mar 8, 2023
 *      @Author: Mohamed Eid
*/

#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>


#define _MCUCSR 	(*((volatile uint8_t*)0x54))
#define _GIFR 		(*((volatile uint8_t*)0x5A))
#define _GICR 		(*((volatile uint8_t*)0x5B))
#define _MCUCR 		(*((volatile uint8_t*)0x55))
#define _SREG 	  	(*((volatile uint8_t*)0x5F))
#define _DDRD      	(*((volatile uint8_t*)0x31))
#define _PORTD     	(*((volatile uint8_t*)0x32))
#define _DDRB      	(*((volatile uint8_t*)0x37))
#define _PORTB     	(*((volatile uint8_t*)0x38))


ISR(INT0_vect)
{
	_PORTD |= (1 << 5);
	_delay_ms(1000);

}

ISR(INT1_vect)
{
	_PORTD |= (1 << 6);
	_delay_ms(1000);

}

ISR(INT2_vect)
{
	_PORTD |= (1 << 7);
	_delay_ms(1000);

}


int main()
{
	//• Bit 7 – I: Global Interrupt Enable
		//The Global Interrupt Enable bit must be set for the interrupts to be enabled.
		_SREG |= (1 << 7);

	// EXTI0 configuration
	_DDRD &= ~(1 << 2); // Make pin2 as input
	_MCUCR |= (0b01 << 0);      // IRQ occur when “any logical change”
	_GICR |= (1 << 6); // enable EXTI0

	// EXTI1 configuration
	_DDRD &= ~(1 << 3); // Make pin2 as input
	_MCUCR |= (0b11 << 2);      // IRQ occur when “rising edge”
	_GICR |= (1 << 7); // enable EXTI1

	// EXTI2 configuration
	_DDRB &= ~(1 << 2); // Make pin2 as input
	_MCUCSR &= ~(1 << 6);      // IRQ occur when “falling edge”
	_GICR |= (1 << 5); // enable EXTI2


	_DDRD |= (1 << 5); // LED0
	_DDRD |= (1 << 6); // LED1
	_DDRD |= (1 << 7); // LED2





	while(1)
	{
		_PORTD &= ~(1 << 5);
		_PORTD &= ~(1 << 6);
		_PORTD &= ~(1 << 7);
	}


}
