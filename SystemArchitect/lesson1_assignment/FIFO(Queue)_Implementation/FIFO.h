/*

 FIFO.h
 	@Author Mohamed Eid
 
 */
#ifndef FIFO_H_
#define FIFO_H_

#include <stdint.h>
#include <stdlib.h>

#define EntryType uint8_t
#define MAXFIFO 5

typedef struct queue
{
	int front;
	int rear;
	uint32_t size;
	EntryType entry[MAXFIFO];
}FIFO;



void FIFO_init(FIFO *);
void Append(FIFO *, EntryType);
void Serve(FIFO *, EntryType*);
void FIFO_Clear(FIFO*);
int FIFO_Is_Full(FIFO*);
int FIFO_Is_Empty(FIFO*);
int FIFO_Size(FIFO*);

void FIFO_Traverse(FIFO*, void(*pf)(EntryType));

#endif /* FIFO_H_ */
