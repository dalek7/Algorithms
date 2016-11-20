#ifndef __dhMat__
#define __dhMat__

#include "dhVector.h"
/*
     0 4  8  12
	 1 5  9  13
	 2 6 10  14
	 3 7 11  15 
*/

class dhMat
{
public:
		dhMat();
		dhMat(float x,float y,float z);
		dhMat(dhVector);
public:
		dhMat	H(float rx,float ry,float rz,dhVector);
		dhMat	RotX(float);
		dhMat	RotY(float);
		dhMat	RotZ(float);
		dhMat	Trans(float,float,float);
		dhMat	Trans(dhVector);
		dhMat	Scale(float,float,float);
		dhMat	Scale(float);
		dhMat	DeScale();	// remove scale
		void	I();
		dhMat	T();	// transpose
		dhMat	operator+(dhVector&);
		dhMat	operator+(dhMat&);
		dhMat	operator-(dhMat&);
		dhMat	operator*(dhMat&);
		dhMat	operator*(float);
		dhVector operator*(dhVector&);
		void	operator=(dhVector&);
		dhVector O();
		dhMat	Inv();
		dhMat	R();
		dhMat	RotAxis( dhVector& o,dhVector& d,float);	// rotation when prevous coordinate is world coordinate.
		dhMat	RotAxis( dhVector& o,dhVector& d,float,dhMat prev);	// rotation about an arbitrary axis on previous coordinate
		dhMat	RotAxis(dhVector& d);
		dhVector	RPY();

public:
		float	v[16];
};

#endif