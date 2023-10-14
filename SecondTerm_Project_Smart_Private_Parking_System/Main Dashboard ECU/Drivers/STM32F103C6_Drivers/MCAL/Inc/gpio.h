/*
 * gpio.h
 *
 *      Author: Mohamed Eid
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_


// ----------------------------------
// Includes
// ----------------------------------

#include "../../Device_Header/STM32F103C6.h"

// ==============================================================


// ----------------------------------
// User Type Definitions
// ----------------------------------

typedef struct
{
	uint16_t GPIO_PinNumber; 	/* Specifies the GPIO pins to be configured.
							       This parameter can be a value of @ref GPIO_PINS_DEFINE */

	uint8_t GPIO_PinMode; 		/* Specifies the operating mode for the selected pins
							 	   This parameter can be a value of @ref GPIO_MODE_DEFINE */

	uint8_t GPIO_OutputSpeed;	/* Specifies the speed of the output pins
								   The parameter can be a value of @ref GPIO_SPEED_DEFINE */
}GPIO_PinConfig_t;

// ============================
// @ref GPIO_PINS_DEFINE
// ============================

#define GPIO_PIN0										((uint16_t)0x0001) /* Pin 0 is selected 	*/
#define GPIO_PIN1										((uint16_t)0x0002) /* Pin 1 is selected 	*/
#define GPIO_PIN2										((uint16_t)0x0004) /* Pin 2 is selected 	*/
#define GPIO_PIN3										((uint16_t)0x0008) /* Pin 3 is selected 	*/
#define GPIO_PIN4										((uint16_t)0x0010) /* Pin 4 is selected 	*/
#define GPIO_PIN5										((uint16_t)0x0020) /* Pin 5 is selected 	*/
#define GPIO_PIN6										((uint16_t)0x0040) /* Pin 6 is selected 	*/
#define GPIO_PIN7										((uint16_t)0x0080) /* Pin 7 is selected 	*/
#define GPIO_PIN8										((uint16_t)0x0100) /* Pin 8 is selected 	*/
#define GPIO_PIN9										((uint16_t)0x0200) /* Pin 9 is selected 	*/
#define GPIO_PIN10										((uint16_t)0x0400) /* Pin 10 is selected 	*/
#define GPIO_PIN11										((uint16_t)0x0800) /* Pin 11 is selected 	*/
#define GPIO_PIN12										((uint16_t)0x1000) /* Pin 12 is selected 	*/
#define GPIO_PIN13										((uint16_t)0x2000) /* Pin 13 is selected 	*/
#define GPIO_PIN14										((uint16_t)0x4000) /* Pin 14 is selected 	*/
#define GPIO_PIN15										((uint16_t)0x8000) /* Pin 15 is selected 	*/
#define GPIO_PIN_ALL									((uint16_t)0xFFFF) /* All pins are selected */



// ============================
// @ref GPIO_MODE_DEFINE
// ============================

#define GPIO_MODE_ANALOG								0x00000000u			/* Analog mode			   			 */
#define GPIO_MODE_INPUT_FLO								0x00000001u			/* Input floating mode 	   			 */
#define GPIO_MODE_INPUT_PU								0x00000002u			/* Input pull-up mode      			 */
#define GPIO_MODE_INPUT_PD								0x00000003u			/* Input pull-down mode    			 */
#define GPIO_MODE_OUTPUT_PP								0x00000004u			/* Output push-pull mode    		 */
#define GPIO_MODE_OUTPUT_OD								0x00000005u			/* Output open-drain mode   		 */
#define GPIO_MODE_OUTPUT_AF_PP							0x00000006u			/* Alternate function push-pull		 */
#define GPIO_MODE_OUTPUT_AF_OD							0x00000007u			/* Alternate function open-drain     */
#define GPIO_MODE_AF_INPUT								0x00000008u			/* Alternate function input   		 */


// ============================
// @ref GPIO_SPEED_DEFINE
// ============================

/*

01: Output mode, max speed 10 MHz.
10: Output mode, max speed 2 MHz.
11: Output mode, max speed 50 MHz.
*/

#define GPIO_SPEED_10M									0x00000001u
#define GPIO_SPEED_2M									0x00000002u
#define GPIO_SPEED_50M									0x00000003u

// ==============================================================================================
#define GPIO_PIN_SET 									1
#define GPIO_PIN_RESET									0
#define GPIO_RETURN_LOCK_ENABLED						1
#define GPIO_RETURN_LOCK_ERROR							0

/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

// Initialization and de-initialization APIs
void MCAL_GPIO_Init (GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig);
void MCAL_GPIO_DeInit (GPIO_TypeDef *GPIOx);

// Read APIs

uint8_t MCAL_GPIO_ReadPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort (GPIO_TypeDef *GPIOx);

// Write APIs

void MCAL_GPIO_WritePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t value);
void MCAL_GPIO_WritePort (GPIO_TypeDef *GPIOx, uint16_t value);

void MCAL_GPIO_TogglePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber);

uint8_t MCAL_GPIO_LockPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber);








#endif /* INC_GPIO_H_ */
