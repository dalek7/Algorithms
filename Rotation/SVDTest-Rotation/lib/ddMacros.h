/* ConstantsAndMacros
2011 Seung-Chan Kim
*/
//#import <math.h>

#ifndef _SMACRO_H_
#define _SMACRO_H_



#undef PI
#define PI	3.1415926535897932f
#define HPI	1.5707963267948966f
#define PI2	6.2831853071795864f

#undef DEG
#define DEG(a)          (180.*a/PI )
#undef RAD
#define RAD(a)          (PI*a/180.)

#ifdef __APPLE__
#define FORMAT(format, ...) [NSString stringWithFormat:(format), ##__VA_ARGS__]
#endif


/****************************************************************************************\
*                             Common macros and inline functions                         *
\****************************************************************************************/


// Macros
//#define DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) / 180.0 * M_PI)
//#define RADIANS_TO_DEGREES(__RADIANS__) ((__RADIANS__)  *180.0 / M_PI)
//#define NULL        (0L)	//Defines the standard NULL pointer.

#define SGN(x) ((x)==0?0:((x)>0?1:-1))
#define SETBIT(x,n) ((x)|=1L<<(n))
#define CLEARBIT(x,n) ((x)&=~(1L<<(n)))
#define GETBIT(x,n) ((x)&1L<<(n))

#define ODD(x) ((x)&1)
#define EVEN(x) (!((x)&1))



#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))


#define ABS(a)	   (((a) < 0) ? -(a) : (a))
#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
//CLAMP(5, 10, 15) is 10


//simple macro that swaps 2 variables
#define SWAP( x, y )			\
({ __typeof__(x) temp  = (x);		\
		x = y; y = temp;		\
})


#endif /* _SMACRO_H_ */