/*

 main.c
 	@Author Mohamed Eid
 
 */

#include "FIFO.h"
#include <stdio.h>

void FIFO_print(uint8_t item)
{
	printf("\t %X \n", item);
}

void main(void)
{
	FIFO uart_buf;
	unsigned char i;
	FIFO_init(&uart_buf);

	for(i = 0 ; i < 7 ; i++)
	{
		if(!FIFO_Is_Full(&uart_buf))
		{
			Append(&uart_buf, i);
			printf("FIOF Enqueue (%x) --- DONE \n", i);
		}
		else
			printf("FIFO Enqueue (%x) --- Failed \n", i);
	}
	printf("\n ========buffer items===========\n");
	FIFO_Traverse(&uart_buf, &FIFO_print);

}
