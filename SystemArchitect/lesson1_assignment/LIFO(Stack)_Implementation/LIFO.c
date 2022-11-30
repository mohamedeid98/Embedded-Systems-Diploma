/*
 * LIFO.c
 *
 *  Created on: Nov 29, 2022
 *      Author: mohamed
 */

#include "LIFO.h"
#include <stdlib.h>
LIFO_Status init(LIFO *lBuf, EntryType *buffer, uint32_t length)
{
	lBuf->length = length;
	lBuf->size = 0;
	lBuf->base = buffer;
	lBuf->top = buffer;
	return LIFO_NO_ERROR;
}

LIFO_Status push(LIFO *lBuf, EntryType item)
{
	if(lBuf == NULL)
		return LIFO_NULL;
	if(lBuf->size == lBuf->length)
		return LIFO_FULL;
	*(lBuf->top) = item;
	lBuf->top++;
	lBuf->size++;
	return LIFO_NO_ERROR;
}



LIFO_Status pop(LIFO *lBuf, EntryType *item)
{
	if(lBuf == NULL)
			return LIFO_NULL;
	if(lBuf->size == 0)
			return LIFO_EMPTY;
	lBuf->top--;
	*item = *(lBuf->top);
	lBuf->size--;
	return LIFO_NO_ERROR;
}










