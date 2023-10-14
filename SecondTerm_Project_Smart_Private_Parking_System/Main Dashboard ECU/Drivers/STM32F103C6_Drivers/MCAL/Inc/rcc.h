/*
 * rcc.h
 *
 *      Author: Mohamed Eid
 */

#ifndef MCAL_INC_RCC_H_TXT_
#define MCAL_INC_RCC_H_TXT_

/****************************************************************************************
									Includes
*****************************************************************************************/

#include "../../Device_Header/STM32F103C6.h"


#define HSE					16000000UL     /* High Speed External Clock */
#define HSI					8000000UL	   /* High Speed Internal Clock */

/****************************************************************************************
									Structures
*****************************************************************************************/

typedef struct
{
	uint32_t PLL_Source;			/*!< Specifies the input clock source to PLL.
										 This parameter can be a value of @ref PLL_CLK_SRC_define */

	uint32_t PLL_Multiplier;		/*!< Specifies the multiplication factor of PLL.
										 This parameter can be a value of @ref PLL_MUL_define */
}RCC_PLLInitTypedef_t;

typedef struct
{
	uint32_t ClockSource;			/*!< Specifies the clock source used by the system.
								 	 	 This parameter can be a value of @ref RCC_SYSCLKSRC_define */

	uint32_t AHB_Prescaler;			/*!< Specifies the divider factor for AHB bus.
										 This parameter can be a value of @ref AHB_PRESCALER_define */

	uint32_t APB1_Prescaler;		/*!< Specifies the divider factor for APB1 bus.
										 This parameter can be a value of @ref APB1_PRESCALER_define */

	uint32_t APB2_Prescaler;		/*!< Specifies the divider factor for APB2 bus.
										 This parameter can be a value of @ref APB2_PRESCALER_define */

	RCC_PLLInitTypedef_t PLL_Config;
}RCC_ClkInitTypedef_t;


/****************************************************************************************
								Reference Macros
*****************************************************************************************/

/*---------------------------------------------------------------------------------------
 * @ref RCC_SYSCLKSRC_define
 */
// Clock configuration register (RCC_CFGR)
//Bits 1:0 SW: System clock switch
//Set and cleared by software to select SYSCLK source.
//Set by hardware to force HSI selection when leaving Stop and Standby mode or in case of
//failure of the HSE oscillator used directly or indirectly as system clock (if the Clock Security
//System is enabled).
//00: HSI selected as system clock
//01: HSE selected as system clock
//10: PLL selected as system clock
//11: not allowed
#define RCC_SYSCLKSRC_HSI				 (0x00000000U)
#define RCC_SYSCLKSRC_HSE				 (0x00000001U)
#define RCC_SYSCLKSRC_PLL				 (0x00000002U)


/*---------------------------------------------------------------------------------------
 * @ref AHB_PRESCALER_define
 */

//Bits 7:4 HPRE: AHB pre-scaler
//Set and cleared by software to control the division factor of the AHB clock.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512

#define AHB_PRESCALER_DIV1					(0x00000000U)
#define AHB_PRESCALER_DIV2					(0x8U << 4)
#define AHB_PRESCALER_DIV4					(0x9U << 4)
#define AHB_PRESCALER_DIV8					(0xAU << 4)
#define AHB_PRESCALER_DIV16					(0xBU << 4)
#define AHB_PRESCALER_DIV64					(0xCU << 4)
#define AHB_PRESCALER_DIV128				(0xDU << 4)
#define AHB_PRESCALER_DIV256				(0xEU << 4)
#define AHB_PRESCALER_DIV512				(0xFU << 4)


/*---------------------------------------------------------------------------------------
 * @ref APB1_PRESCALER_define
 */

//	Bits 10:8 PPRE1: APB low-speed pre-scaler (APB1)
//	Set and cleared by software to control the division factor of the APB low-speed clock
//	(PCLK1).
//	Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
//	0xx: HCLK not divided
//	100: HCLK divided by 2
//	101: HCLK divided by 4
//	110: HCLK divided by 8
//	111: HCLK divided by 16

#define APB1_PRESCALER_DIV1					(0x00000000U)
#define APB1_PRESCALER_DIV2					(0x4U << 8)
#define APB1_PRESCALER_DIV4					(0x5U << 8)
#define APB1_PRESCALER_DIV8					(0x6U << 8)
#define APB1_PRESCALER_DIV16				(0x7U << 8)


/*---------------------------------------------------------------------------------------
 * @ref APB2_PRESCALER_define
 */

//	Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
//	Set and cleared by software to control the division factor of the APB high-speed clock
//	(PCLK2).
//	0xx: HCLK not divided
//	100: HCLK divided by 2
//	101: HCLK divided by 4
//	110: HCLK divided by 8
//	111: HCLK divided by 16

#define APB2_PRESCALER_DIV1					(0x00000000U)
#define APB2_PRESCALER_DIV2					(0x4U << 11)
#define APB2_PRESCALER_DIV4					(0x5U << 11)
#define APB2_PRESCALER_DIV8					(0x6U << 11)
#define APB2_PRESCALER_DIV16				(0x7U << 11)



/*---------------------------------------------------------------------------------------
 * @ref PLL_CLK_SRC_define
 */

//	Bit 16 PLLSRC: PLL entry clock source
//	Set and cleared by software to select PLL clock source. This bit can be written only when
//	PLL is disabled.
//	0: HSI oscillator clock / 2 selected as PLL input clock
//	1: HSE oscillator clock selected as PLL input clock

#define PLL_CLK_SRC_HSI						(0x00000000U)
#define PLL_CLK_SRC_HSE						(0x01U << 16)

/*---------------------------------------------------------------------------------------
 * @ref PLL_MUL_define
 */
/*     Caution: The PLL output frequency must not exceed 72 MHz.      */
#define PLL_MUL2							(0x0U << 18)
#define PLL_MUL3							(0x1U << 18)
#define PLL_MUL4							(0x2U << 18)
#define PLL_MUL5							(0x3U << 18)
#define PLL_MUL6							(0x4U << 18)
#define PLL_MUL7							(0x5U << 18)
#define PLL_MUL8							(0x6U << 18)
#define PLL_MUL9							(0x7U << 18)
#define PLL_MUL10							(0x8U << 18)
#define PLL_MUL11							(0x9U << 18)
#define PLL_MUL12							(0xAU << 18)
#define PLL_MUL13							(0xBU << 18)
#define PLL_MUL14							(0xCU << 18)
#define PLL_MUL15							(0xDU << 18)
#define PLL_MUL16							(0xEU << 18)






/****************************************************************************************
										APIs
*****************************************************************************************/


void MCAL_RCC_Init(RCC_ClkInitTypedef_t* RCC_Config);
void MCAL_RCC_DeInit(void);

uint32_t MCAL_RCC_GetSysClockFreq(void);
uint32_t MCAL_RCC_GetHCLKFreq(void);
uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);






#endif /* MCAL_INC_RCC_H_TXT_ */
