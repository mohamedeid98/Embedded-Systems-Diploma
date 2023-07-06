/*
 * STM32F103C6.h
 *
 *  Created on: Jun 30, 2023
 *      Author: Mohamed Eid
 */

#ifndef INC_STM32F103C6_H_
#define INC_STM32F103C6_H_

// ----------------------------------
// Includes
// ----------------------------------

#include <stdlib.h>
#include <stdint.h>

// ===================================================================

// ----------------------------------
// Base Address for Memories
// ----------------------------------

#define FLASH_MEM_BASE							0x08000000UL
#define SYSTEM_MEM_BASE							0x1FFFF000UL
#define SRAM_MEM_BASE							0x20000000UL

#define Peripherals_Base						ox40000000UL
#define Cortex_M3_Internal_Peripherals_Base		0xE0000000UL

// ===============================================================

// ----------------------------------
// Base Address for Bus Peripherals
// ----------------------------------


// ----------------------------------
// Base Address for AHB Peripherals
// ----------------------------------

#define RCC_BASE								0x40021000UL



// ----------------------------------
// Base Address for APB2 Peripherals
// ----------------------------------

// GPIO
// A, B are fully included in LQFP48 Package
#define GPIOA_BASE									0x40010800UL
#define GPIOB_BASE									0x40010C00UL
// C, D are partially included in LQFP48 Package
#define GPIOC_BASE									0x40011000UL
#define GPIOD_BASE									0x40011400UL
// E is not included in LQFP48 Package
#define GPIOE_BASE									0x40011800UL

//EXIT
#define EXTI_BASE									0x40010400UL

//AFIO
#define AFIO_BASE									0x40010000UL


// ----------------------------------
// Base Address for APB1 Peripherals
// ----------------------------------

// ====================================================================

// ----------------------------------
// Peripheral Registers
// ----------------------------------


// ----------------------------------
// RCC Registers
// ----------------------------------

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;

}RCC_TypeDef;



// ----------------------------------
// GPIO Registers
// ----------------------------------

typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;

}GPIO_TypeDef;


// ----------------------------------
// AFIO Registers
// ----------------------------------


typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t RESERVED0;
	volatile uint32_t MAPR2;

}AFIO_TypeDef;



// ----------------------------------
// EXTI Registers
// ----------------------------------


typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;

}EXTI_TypeDef;

// ===================================================================

// ----------------------------------
// Peripheral Instants
// ----------------------------------


// ----------------------------------
// GPIO Instants
// ----------------------------------

#define GPIOA									((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB									((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC									((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD									((GPIO_TypeDef*)GPIOD_BASE)
#define GPIOE									((GPIO_TypeDef*)GPIOE_BASE)

// ----------------------------------
// RCC Instant
// ----------------------------------

#define RCC 									((RCC_TypeDef*)RCC_BASE)

// ----------------------------------
// EXTI Instant
// ----------------------------------

#define EXTI 									((EXTI_TypeDef*)EXTI_BASE)


// ----------------------------------
// AFIO Instant
// ----------------------------------

#define AFIO 									((AFIO_TypeDef*)AFIO_BASE)


// ===================================================================

// ----------------------------------
// Clock Enable Macros
// ----------------------------------

#define RCC_AFIO_CLK_EN()						(RCC->APB2ENR |= (1 << 0))

#define RCC_GPIOA_CLK_EN()						(RCC->APB2ENR |= (1 << 2))
#define RCC_GPIOB_CLK_EN()						(RCC->APB2ENR |= (1 << 3))
#define RCC_GPIOC_CLK_EN()						(RCC->APB2ENR |= (1 << 4))
#define RCC_GPIOD_CLK_EN()						(RCC->APB2ENR |= (1 << 5))
#define RCC_GPIOE_CLK_EN()						(RCC->APB2ENR |= (1 << 6))


// ===================================================================





#endif /* INC_STM32F103C6_H_ */
