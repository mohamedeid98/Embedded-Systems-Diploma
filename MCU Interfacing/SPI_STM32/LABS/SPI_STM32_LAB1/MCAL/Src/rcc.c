
#include "../Inc/rcc.h"

/*
 * 		@Fn			-	MCAL_RCC_Get_SysClk_Freq
 * 		@brief			-	Get System clock frequency
 * 		@param[in]		-	none
 * 		@param[out]		-	none
 * 		@return value		-	SysClk frequency
 * 		Note			-	none
 */
uint32_t MCAL_RCC_Get_SysClk_Freq (void) {
	switch ((RCC->CFGR >> 2) & 0b11) {
	case 0 :
		return HSI_CLK ;
		break ;
	case 1 :
		return HSE_CLK ;
		break ;
	case 2 :
		return PLL_CLK ;
		break ;
	}
}

/*
 * 		@Fn			-	MCAL_RCC_Get_HClk_Freq
 * 		@brief			-	Get AHB clock frequency
 * 		@param[in]		-	none
 * 		@param[out]		-	none
 * 		@return value		-	AHB clock frequency
 * 		Note			-	none
 */
uint32_t MCAL_RCC_Get_HClk_Freq (void) {
	uint32_t prescaler ;
	uint32_t cfg_value ;
	uint32_t Hclk ;
	cfg_value = (RCC->CFGR >> 4) & 0b1111 ;
	/*
	 * 	0xxx: SYSCLK not divided
		1000: SYSCLK divided by 2
		1001: SYSCLK divided by 4
		1010: SYSCLK divided by 8
		1011: SYSCLK divided by 16
		1100: SYSCLK divided by 64
		1101: SYSCLK divided by 128
		1110: SYSCLK divided by 256
		1111: SYSCLK divided by 512
	 *
	 */
	switch (cfg_value) {
	case 0b0000 :
	case 0b0001 :
	case 0b0010 :
	case 0b0011 :
	case 0b0100 :
	case 0b0101 :
	case 0b0110 :
	case 0b0111 :
		prescaler = 1 ;
		break ;
	case 0b1000 :
		prescaler = 2 ;
		break ;
	case 0b1001 :
		prescaler = 4 ;
		break ;
	case 0b1010 :
		prescaler = 8 ;
		break ;
	case 0b1011 :
		prescaler = 16 ;
		break ;
	case 0b1100 :
		prescaler = 64 ;
		break ;
	case 0b1101 :
		prescaler = 128 ;
		break ;
	case 0b1110 :
		prescaler = 256 ;
		break ;
	case 0b1111 :
		prescaler = 512 ;
		break ;
	}
	Hclk = (uint32_t)(MCAL_RCC_Get_SysClk_Freq() / prescaler) ;
	return Hclk ;
}

/*
 * 		@Fn			-	MCAL_RCC_Get_PClk1_Freq
 * 		@brief			-	Get APB1 clock frequency
 * 		@param[in]		-	none
 * 		@param[out]		-	none
 * 		@return value		-	APB1 clock frequency
 * 		Note			-	none
 */
uint32_t MCAL_RCC_Get_PClk1_Freq (void) {
	uint32_t prescaler ;
	uint32_t cfg_value ;
	uint32_t Pclk1 ;
	cfg_value = (RCC->CFGR >> 8) & 0b111 ;
	/*
	 * 	0xx: HCLK not divided
		100: HCLK divided by 2
		101: HCLK divided by 4
		110: HCLK divided by 8
		111: HCLK divided by 16
	 */
	switch (cfg_value) {
	case 0b000 :
	case 0b001 :
	case 0b010 :
	case 0b011 :
		prescaler = 1 ;
		break ;
	case 0b100 :
		prescaler = 2 ;
		break ;
	case 0b101 :
		prescaler = 4 ;
		break ;
	case 0b110 :
		prescaler = 8 ;
		break ;
	case 0b111 :
		prescaler = 16 ;
		break ;
	}
	Pclk1 = (uint32_t)(MCAL_RCC_Get_HClk_Freq() / prescaler) ;
	return Pclk1 ;
}

/*
 * 		@Fn			-	MCAL_RCC_Get_PClk2_Freq
 * 		@brief			-	Get APB2 clock frequency
 * 		@param[in]		-	none
 * 		@param[out]		-	none
 * 		@return value		-	APB2 clock frequency
 * 		Note			-	none
 */
uint32_t MCAL_RCC_Get_PClk2_Freq (void) {
	uint32_t prescaler ;
	uint32_t cfg_value ;
	uint32_t Pclk2 ;
	cfg_value = (RCC->CFGR >> 11) & 0b111 ;
	/*
	 * 	0xx: HCLK not divided
		100: HCLK divided by 2
		101: HCLK divided by 4
		110: HCLK divided by 8
		111: HCLK divided by 16
	 */
	switch (cfg_value) {
	case 0b000 :
	case 0b001 :
	case 0b010 :
	case 0b011 :
		prescaler = 1 ;
		break ;
	case 0b100 :
		prescaler = 2 ;
		break ;
	case 0b101 :
		prescaler = 4 ;
		break ;
	case 0b110 :
		prescaler = 8 ;
		break ;
	case 0b111 :
		prescaler = 16 ;
		break ;
	}
	Pclk2 = (uint32_t)(MCAL_RCC_Get_HClk_Freq() / prescaler) ;
	return Pclk2 ;
}
