#include <stdint.h>

extern uint32_t _E_TEXT;
extern uint32_t _S_DATA;
extern uint32_t _E_DATA;
extern uint32_t _S_BSS;
extern uint32_t _E_BSS;
//extern uint32_t _STACK_TOP;

static unsigned long stack_top[256];



void reset_handler(void)
{
	int i;
	uint32_t data_size = (unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA;
	unsigned char* p_scr = (unsigned char*)&_E_TEXT;
	unsigned char* p_dst = (unsigned char*)&_S_DATA;
	for(i = 0 ; i < data_size ; i++)
	{
		*((unsigned char*) p_dst) = *((unsigned char*) p_scr);
	}

	uint32_t bss_size = (unsigned char*)&_E_BSS - (unsigned char*)&_S_BSS;

	for(i = 0 ; i < bss_size ; i++)
	{	
		p_dst = (unsigned char*)_S_BSS;
		*((unsigned char*) p_dst++) = (unsigned char)0;
	}
	main();
}


void default_handler(void)
{
	reset_handler();
}

void NMI_handler(void)__attribute__((weak, alias("default_handler")));
void MM_Fault_handler(void)__attribute__((weak, alias("default_handler")));
void BusFault(void)__attribute__((weak, alias("default_handler")));
void UsageFault(void)__attribute__((weak, alias("default_handler")));



void (*const vectors[])()__attribute__((section(".vectors"))) =
{
	(void (*)()) ((unsigned long) stack_top + sizeof(stack_top)),
	&reset_handler,
	&NMI_handler,
	&MM_Fault_handler
};

