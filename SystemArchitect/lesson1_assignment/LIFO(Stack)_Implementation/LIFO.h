/*
 * LIFO.h
 *
 *  Created on: Nov 29, 2022
 *      Author: mohamed
 */

#ifndef LIFO_H_
#define LIFO_H_

#include <stdint.h>

#define EntryType uint8_t

typedef struct
{
	uint32_t length;
	EntryType *top;
	EntryType *base;
	uint32_t size;
}LIFO;

typedef enum
{
	LIFO_NO_ERROR,
	LIFO_FULL,
	LIFO_EMPTY,
	LIFO_NULL
}LIFO_Status;

LIFO_Status init(LIFO *, EntryType *, uint32_t);
LIFO_Status push(LIFO *, EntryType);
LIFO_Status pop(LIFO *, EntryType *);


#endif /* LIFO_H_ */
