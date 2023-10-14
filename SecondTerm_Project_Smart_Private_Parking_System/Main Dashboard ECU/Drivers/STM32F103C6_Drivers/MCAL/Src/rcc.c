/*
 * rcc.c
 *
 *      Author: Mohamed Eid
 */


/****************************************************************************************
									Includes
*****************************************************************************************/
#include "../Inc/rcc.h"


/****************************************************************************************
								Generic Variables
*****************************************************************************************/
RCC_ClkInitTypedef_t G_RCC_Config;

/****************************************************************************************
								APIs Implementation
*****************************************************************************************/

void MCAL_RCC_Init(RCC_ClkInitTypedef_t* RCC_Config)
{
	G_RCC_Config = *RCC_Config;

	if(RCC_Config->ClockSource == RCC_SYSCLKSRC_PLL)
	{
		RCC->CFGR |= RCC_Config->PLL_Config.PLL_Source;
		RCC->CFGR |= RCC_Config->PLL_Config.PLL_Multiplier;
	}

	RCC->CFGR |= RCC_Config->ClockSource;

	RCC->CFGR |= RCC_Config->AHB_Prescaler;

	RCC->CFGR |= RCC_Config->APB1_Prescaler;

	RCC->CFGR |= RCC_Config->APB2_Prescaler;

	if(RCC_Config->ClockSource == RCC_SYSCLKSRC_PLL)
	{
		RCC->CR |= (1 << 24);
	}
	else if (RCC_Config->ClockSource == RCC_SYSCLKSRC_HSE)
	{
		RCC->CR |= (1 << 16);

	}
	else if (RCC_Config->ClockSource == RCC_SYSCLKSRC_HSI)
	{
		RCC->CR |= (1 << 0);

	}
}





uint32_t MCAL_RCC_GetSysClockFreq(void)
{
	uint32_t pll_src, sys_clk;

	if (G_RCC_Config.ClockSource == RCC_SYSCLKSRC_HSI)
	{
		return HSI;
	}
	else if(G_RCC_Config.ClockSource == RCC_SYSCLKSRC_HSE)
	{
		return HSE;
	}
	else if(G_RCC_Config.ClockSource == RCC_SYSCLKSRC_PLL)
	{
		if(G_RCC_Config.PLL_Config.PLL_Source == PLL_CLK_SRC_HSE)
		{
			//TODO Check this
//			Bit 17 PLLXTPRE: HSE divider for PLL entry
//			Set and cleared by software to divide HSE before PLL entry. This bit can be written only
//			when PLL is disabled.
//			0: HSE clock not divided
//			1: HSE clock divided by 2

			/* Assuming the pre-scaler is always one */
			pll_src = HSE;
		}
		else if (G_RCC_Config.PLL_Config.PLL_Source == PLL_CLK_SRC_HSI)
		{
			pll_src = HSI / 2;
		}
		sys_clk = pll_src * (G_RCC_Config.PLL_Config.PLL_Multiplier >> 18);

		return sys_clk;
	}

	return HSI;
}

uint32_t MCAL_RCC_GetHCLKFreq(void)
{
	uint32_t AHB_PRE = G_RCC_Config.AHB_Prescaler;
	uint32_t sys_clk = MCAL_RCC_GetSysClockFreq();
	uint32_t HCLK;

	switch(AHB_PRE)
	{
		case AHB_PRESCALER_DIV1:
			HCLK = sys_clk;
			break;
		case AHB_PRESCALER_DIV2:
			HCLK = sys_clk / 2;
			break;
		case AHB_PRESCALER_DIV4:
			HCLK = sys_clk / 4;
			break;
		case AHB_PRESCALER_DIV8:
			HCLK = sys_clk / 8;
			break;
		case AHB_PRESCALER_DIV16:
			HCLK = sys_clk / 16;
			break;
		case AHB_PRESCALER_DIV64:
			HCLK = sys_clk / 64;
			break;
		case AHB_PRESCALER_DIV128:
			HCLK = sys_clk / 128;
			break;
		case AHB_PRESCALER_DIV256:
			HCLK = sys_clk / 256;
			break;
		case AHB_PRESCALER_DIV512:
			HCLK = sys_clk / 512;
			break;
	}

	return HCLK;

}

uint32_t MCAL_RCC_GetPCLK1Freq(void)
{
	uint32_t APB1_PRE = G_RCC_Config.APB1_Prescaler;
	uint32_t HCLK	  = MCAL_RCC_GetHCLKFreq();
	uint32_t PCLK1;

	switch(APB1_PRE)
	{
		case APB1_PRESCALER_DIV1:
			PCLK1 = HCLK;
			break;
		case APB1_PRESCALER_DIV2:
			PCLK1 = HCLK / 2;
			break;
		case APB1_PRESCALER_DIV4:
			PCLK1 = HCLK / 4;
			break;
		case APB1_PRESCALER_DIV8:
			PCLK1 = HCLK / 8;
			break;
		case APB1_PRESCALER_DIV16:
			PCLK1 = HCLK / 16;
			break;

	}

	return PCLK1;

}

uint32_t MCAL_RCC_GetPCLK2Freq(void)
{
	uint32_t APB2_PRE = G_RCC_Config.APB2_Prescaler;
	uint32_t HCLK	  = MCAL_RCC_GetHCLKFreq();
	uint32_t PCLK2;

	switch(APB2_PRE)
	{
		case APB2_PRESCALER_DIV1:
			PCLK2 = HCLK;
			break;
		case APB2_PRESCALER_DIV2:
			PCLK2 = HCLK / 2;
			break;
		case APB2_PRESCALER_DIV4:
			PCLK2 = HCLK / 4;
			break;
		case APB2_PRESCALER_DIV8:
			PCLK2 = HCLK / 8;
			break;
		case APB2_PRESCALER_DIV16:
			PCLK2 = HCLK / 16;
			break;

	}

	return PCLK2;
}










