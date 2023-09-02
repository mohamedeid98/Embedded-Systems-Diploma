
#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "STM32F103C6.h"


// ==================================================

//---------------------------------------------------------------------------------------------------
// Clock Sources
#define HSI_CLK 								((uint32_t)8000000)
#define HSE_CLK 								((uint32_t)16000000)
#define PLL_CLK									((uint32_t)16000000)
// ==================================================

//---------------------------------------------------------------------------------------------------
// APIs
uint32_t MCAL_RCC_Get_SysClk_Freq (void) ;
uint32_t MCAL_RCC_Get_HClk_Freq (void) ;
uint32_t MCAL_RCC_Get_PClk1_Freq (void) ;
uint32_t MCAL_RCC_Get_PClk2_Freq (void) ;


#endif /* INC_RCC_H_ */
