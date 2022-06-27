


#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

#include <stdbool.h>

#ifndef _bool
#define _bool unsigned char
#endif

// boolean
#ifndef FALSE
#define FALSE                         (boolean)false
#endif

#ifndef TRUE
#define TRUE                          (boolean)true
#endif

#define NULL                          ((void*)0)


typedef _bool                         boolean  ;

// integer types

typedef unsigned char                  uint8   ;
typedef signed char                    sint8   ;
typedef short                          sint16  ;
typedef unsigned short                 uint16  ;
typedef int                            sint32  ;
typedef unsigned int                   uint32  ;
typedef long int                       sint64  ;
typedef unsigned long int              uint64  ;

typedef volatile uint8                 vuint8  ;
typedef volatile sint8                 vsint8  ;

typedef volatile sint16                vsint16 ;
typedef volatile uint16                vuint16 ;

typedef volatile sint32                vsint32 ;
typedef volatile uint32                vuint32 ;

typedef volatile sint64                vsint64 ;
typedef volatile uint64                vuint64 ;

// float types

typedef float                         float32  ;
typedef double                        float64  ;
typedef long double                   float96  ;




#endif /* PLATFORM_TYPES_H_ */
