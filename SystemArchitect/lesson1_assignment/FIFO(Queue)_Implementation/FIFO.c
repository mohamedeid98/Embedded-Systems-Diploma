/*

 FIFO.c
 	@Author Mohamed Eid
 
 */
#include "FIFO.h"


FIFO_init(FIFO *fBuf)
{
	fBuf->front = 0;
	fBuf->rear = -1;
	fBuf->size = 0;
}


void Append(FIFO *fBuf, EntryType item)
{
	fBuf->rear = (fBuf->rear + 1) % MAXFIFO;
	fBuf->entry[fBuf->rear] = item;
	fBuf->size++;
}


void Serve(FIFO *fBuf, EntryType *item)
{
	*item = fBuf->entry[fBuf->front];
	fBuf->front = (fBuf->rear + 1 ) % MAXFIFO;
	fBuf->size--;

}
void FIFO_Clear(FIFO* fBuf)
{
	fBuf->front = 0;
	fBuf->rear = -1;
	fBuf->size = 0;
}
int FIFO_Is_Full(FIFO* fBuf)
{
	return (fBuf->size == MAXFIFO);
}
int FIFO_Is_Empty(FIFO* fBuf)
{
	return !fBuf->size;
}
int FIFO_Size(FIFO* fBuf)
{
	return fBuf->size;
}

void FIFO_Traverse(FIFO* fBuf, void(*pf)(EntryType))
{
	int pos, s;
	for(pos = fBuf->front, s=0 ; s < fBuf->size ; s++)
	{
		(*pf)(fBuf->entry[pos]);
		pos = (pos + 1) % MAXFIFO;
	}
}

