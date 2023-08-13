

#ifndef LCD_H_
#define LCD_H_


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#include "../../MCAL/GPIO/gpio.h"
#include <stdio.h>


//LCD HW Pins
#define RS								PIN_2
#define RW								PIN_1
#define E								PIN_0
#define LCD_CTRL_PORT					B		 //PORTB
#define LCD_DATA_PORT					A		 //PORTA

//LCD Commands
#define FOUR_BITS_DATA_MODE             0x02
#define LCD_2LINE_4BIT_MODE             0x28
#define LCD_2LINE_8BIT_MODE             0x38
#define LCD_BEGIN_AT_FIRST_RAW          0x80
#define LCD_BEGIN_AT_SECOND_RAW         0xC0
#define LCD_DISP_ON_CURSOR_ON		    0x0E
#define LCD_DISP_ON_CURSOR_BLINK	    0x0F
#define LCD_DISP_ON_BLINK	            0x0D
#define LCD_DISP_ON_CURSOR_OFF          0x0C
#define LCD_DISP_OFF_CURSOR_OFF         0x08
#define LCD_MOVE_DISP_RIGHT             0x1C
#define LCD_MOVE_DISP_LEFT              0x18
#define LCD_MOVE_CURSOR_RIGHT           0x14
#define LCD_MOVE_CURSOR_LEFT            0x10
#define LCD_ENTRY_MODE      		    0x06
#define CLEAR_COMMAND			    	0x01



// LCD Data bits mode configuration
#define DATA_BITS_MODE 4

// Use higher 4 bits in the data port
#if (DATA_BITS_MODE == 4)
#define  UPPER_PORT_PINS
#endif

/*******************************************************************************
                           Functions Prototypes                                   
 *******************************************************************************/
void LCD_INIT();
void LCD_Clear_Screen();
void LCD_Send_Command( uint8 command );  
void LCD_Display_Character( char data );
void LCD_display_String( char* Str );
void LCD_Intger_Number( uint32 Intger_Number );
void LCD_Real_Number( double Intger_Number );
extern void _delay_ms(uint32 time);
#endif /* LCD_H_ */