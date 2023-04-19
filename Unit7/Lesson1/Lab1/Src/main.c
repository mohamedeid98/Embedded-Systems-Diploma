
#include <stdint.h>

//GPIOA
#define GPIOA_BASE 		0x40010800
#define GPIOA_CRL		(*((volatile uint32_t*)(GPIOA_BASE + 0x00)))
#define GPIOA_CRH		(*((volatile uint32_t*)(GPIOA_BASE + 0x04)))
#define GPIOA_IDR		(*((volatile uint32_t*)(GPIOA_BASE + 0x08)))
#define GPIOA_ODR		(*((volatile uint32_t*)(GPIOA_BASE + 0x0c)))

//GPIOB
#define GPIOB_BASE		0x40010C00
#define GPIOB_CRL		(*((volatile uint32_t*)(GPIOB_BASE + 0x00)))
#define GPIOB_CRH		(*((volatile uint32_t*)(GPIOB_BASE + 0x04)))
#define GPIOB_IDR		(*((volatile uint32_t*)(GPIOB_BASE + 0x08)))
#define GPIOB_ODR		(*((volatile uint32_t*)(GPIOB_BASE + 0x0c)))

//RCC
#define RCC_BASE 		0x40021000
#define RCC_APB2ENR		(*((volatile uint32_t*)(RCC_BASE + 0x18)))


void GPIO_init()
{
	// PA.1 input mode floating

	/*MODEy[1:0]: Port x mode bits (y= 0 .. 7)
	00: Input mode (reset state)*/
	GPIOA_CRL &= ~(0b11 << 4);

	/*CNFy[1:0]: Port x configuration bits (y= 0 .. 7)
	In input mode (MODE[1:0]=00):
	01: Floating input (reset state)*/
	GPIOA_CRL |= (0b01 << 6);

	// PB.1 output push pull mode

	/*CNFy[1:0]: Port x configuration bits (y= 0 .. 7)
	In output mode (MODE[1:0] > 00):
	00: General purpose output push-pull*/
	GPIOB_CRL &= ~(0b11 << 6);

	/*MODEy[1:0]: Port x mode bits (y= 0 .. 7)
	01: Output mode, max speed 10 MHz.*/
	GPIOB_CRL |= (0b01 << 4);



//====================================================

	// PA.13 input mode floating

	/*MODEy[1:0]: Port x mode bits (y= 8 .. 15)
	00: Input mode (reset state)*/
	GPIOA_CRH &= ~(0b11 << 20);

	/*CNFy[1:0]: Port x configuration bits (y= 8 .. 15)
	In input mode (MODE[1:0]=00):
	01: Floating input (reset state)*/
	GPIOA_CRH |= (0b01 << 22);


	// PB.13 output push pull mode

	/*MODEy[1:0]: Port x mode bits (y= 0 .. 7)
	01: Output mode, max speed 10 MHz.*/
	GPIOB_CRH |= (0b01 << 20);

	/*CNFy[1:0]: Port x configuration bits (y= 0 .. 7)
	In output mode (MODE[1:0] > 00):
	00: General purpose output push-pull*/
	GPIOB_CRH &= ~(0b11 << 22);
}


void clock_init()
{
	RCC_APB2ENR |= (1 << 2); // enable clock to port A
	RCC_APB2ENR |= (1 << 3); // enable clock to port B
}

void wait_ms(int m_sec)
{
	for(int i = 0 ; i < m_sec ; i++)
	{
		for(int j = 0 ; j < 1000 ; j++);
	}
}

int main(void)
{
	clock_init();
	GPIO_init();
	GPIOB_ODR = 0xFFFFFFFF;

	/* Loop forever */
	while(1)
	{

		if(((GPIOA_IDR & (1 << 1)) >> 1) == 0)
		{
			GPIOB_ODR ^= 1 << 1;
			while(((GPIOA_IDR & (1 << 1)) >> 1) == 0);
		}
		if(((GPIOA_IDR & (1 << 13)) >> 13) == 1)
		{
			GPIOB_ODR ^= (1 << 13);
		}
		wait_ms(5);


	}
}
