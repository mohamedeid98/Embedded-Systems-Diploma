

#include "uart.h"

unsigned char  str_buff[100] = "learn-in-depth:<MOHAM3D>";


void main(void)
{
	uart_send_str(str_buff);
}