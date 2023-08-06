/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mohamed Eid
 * @brief          : Main program body
 ******************************************************************************
 */

#include <stdint.h>

#define RCC_BASE 0x40021000
#define RCC_APB2ENR *((volatile uint32_t*)(RCC_BASE + 0x18))

#define EXTI_BASE 0x40010400
#define EXTI_IMR *((volatile uint32_t*)(EXTI_BASE + 0x00))
#define EXTI_RTSR *((volatile uint32_t*)(EXTI_BASE + 0x08))
#define EXTI_PR *((volatile uint32_t*)(EXTI_BASE + 0x14))
#define EXTI_FTSR *((volatile uint32_t*)(EXTI_BASE + 0x0c))

#define ِAFIO_BASE 0x40010000
#define AFIO_EXTICR1 *((volatile uint32_t*)(ِAFIO_BASE + 0x08))

#define GPIOA_BASE 0x40010800
#define GPIOA_CRL *(volatile uint32_t*)(GPIOA_BASE + 0x00)
#define GPIOA_CRH *(volatile uint32_t*)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t*)(GPIOA_BASE + 0x0c)


#define NVIC_ISER0 *(volatile uint32_t*)(0xE000E100)

void GPIO_init();
void clock_init();

int main(void)
{
	clock_init() ;

	GPIO_init() ;
	/*Bits 19:0 MRx: Interrupt Mask on line x
	0: Interrupt request from Line x is masked
	1: Interrupt request from Line x is not masked*/
	EXTI_IMR |= (1 << 0) ;


	/*	EXTIx[3:0]: EXTI x configuration (x= 0 to 3)
		These bits are written by software to select the source input for EXTIx external interrupt.
		Refer to Section 10.2.5: External interrupt/event line mapping
		0000: PA[x] pin*/

	AFIO_EXTICR1 = 0 ;

/*	Bits 19:0 TRx: Rising trigger event configuration bit of line x
	0: Rising trigger disabled (for Event and Interrupt) for input line
	1: Rising trigger enabled (for Event and Interrupt) for input line.
	*/
	EXTI_FTSR |= (1 << 0) ;
	EXTI_RTSR |= (1 << 0) ;



	//Enable NVIC IRQ (EXTIO)
	NVIC_ISER0 |= (1 << 6);

    /* Loop forever */
	while(1);
}


void GPIO_init()
{
	// PINA.0 ----> input floating
	GPIOA_CRL |= (1 << 2) ;
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;


}

void clock_init()
{
	RCC_APB2ENR |= (1 << 0) ; //enable clock for AFIO
	RCC_APB2ENR |= (1 << 2) ; //enable clock for IOPA
}


void EXTI0_IRQHandler(void)
{
	GPIOA_ODR ^= (1 << 13) ;

/*	Bits 19:0 PRx: Pending bit
	0: No trigger request occurred
	1: selected trigger request occurred
	This bit is set when the selected edge event arrives on the external interrupt line. This bit is
	cleared by writing a ‘1’ into the bit. */
	EXTI_PR |= (1 << 0);
}






