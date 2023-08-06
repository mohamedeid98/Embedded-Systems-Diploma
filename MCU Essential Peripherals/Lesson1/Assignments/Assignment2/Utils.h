/*
 * Utils.h
 *
 *  Author: Mohamed Eid
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define SetBit(reg, bit)		reg |= (1 << bit)
#define ClearBit(reg, bit)		reg &= ~(1 << bit)
#define ReadBit(reg, bit)		((reg >> bit) & 1)
#define ToggleBit(reg, bit)		reg ^= (1 << bit)


#endif /* UTILS_H_ */