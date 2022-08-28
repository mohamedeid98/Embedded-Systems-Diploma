#include <stdint.h>

typedef volatile unsigned int vuint32_t ;

#define RCC_BASE 0x40021000
#define GPIOA_BASE  0X40010800

#define APB2ENR        *((vuint32_t *)(RCC_BASE  + 0x18))
#define GPIOA_CRH      *((vuint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_ODR      *((vuint32_t *)(GPIOA_BASE + 0X0C))

uint32_t const  var = 10;

extern NMI_handler(void)
{

}

extern BusFault(void)
{
	
}

typedef union
{
	vuint32_t all_fields;
	struct
	{
		vuint32_t reserved:13;
		vuint32_t pin13:1;
	}pin;
}R_ODR_t;

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(GPIOA_BASE + 0x0c);

int main(void)
{
	int i;
    APB2ENR |= (1 << 2);
    GPIOA_CRH &= 0xFF0FFFFF;
    GPIOA_CRH |= 0X00200000;

    while(1)
    {
    	R_ODR->pin.pin13 = 1;
    	for(i = 0 ; i < 10000 ; i++);
    	R_ODR->pin.pin13 = 0;
    	for(i = 0 ; i < 10000 ; i++);
    }

}
