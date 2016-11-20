#include "stdafx.h"
#include "dhMat.h"

#define PI              3.14159265358979323   /* 180 deg */
#define DEG(a)          (180.*a/PI )
#define RAD(a)          (PI*a/180.)

dhMat::dhMat()
{
	I();	
}

dhMat::dhMat(float x,float y,float z)
{
	I();	
	v[12] = x;
	v[13] = y;
	v[14] = z;
}

dhMat::dhMat(dhVector p)
{
	I();
	v[12] = p.x;
	v[13] = p.y;
	v[14] = p.z;
}

void dhMat::I()
{
	memset( v,0,sizeof(float)*16);
	v[0]	= 1;
	v[5]	= 1;
	v[10]	= 1;
	v[15]	= 1;
}

dhMat dhMat::RotX( float f)
{
	dhMat ret;
	ret.v[5]	= cos(f);
	ret.v[9]	= -sin(f);
	ret.v[6]	= sin(f);
	ret.v[10]	= cos(f);
	return ret;
}

dhMat dhMat::RotY( float f)
{
	dhMat ret;
	ret.v[0]	= cos(f);
	ret.v[8]	= sin(f);
	ret.v[2]	= -sin(f);
	ret.v[10]	= cos(f);
	return ret;
}

dhMat dhMat::RotZ( float f)
{
	dhMat ret;
	ret.v[0]	= cos(f);
	ret.v[4]	= -sin(f);
	ret.v[1]	= sin(f);
	ret.v[5]	= cos(f);
	return ret;
}

dhMat dhMat::Trans(float x,float y,float z)
{
	dhMat ret;
	ret.v[12]	= x;
	ret.v[13]	= y;
	ret.v[14]	= z;
	return ret;
}

dhMat dhMat::Trans( dhVector v)
{
	dhMat ret;
	ret.v[12]	= v.x;
	ret.v[13]	= v.y;
	ret.v[14]	= v.z;
	return ret;
}

dhMat dhMat::operator+(dhVector& v)
{
	dhMat ret	= *this;
	ret.v[12]	=	this->v[12]+v.x;
	ret.v[13]	=	this->v[13]+v.y;
	ret.v[14]	=	this->v[14]+v.z;
	return ret;
}

dhMat dhMat::operator+(dhMat& m)
{
	dhMat ret;
	for (int i=0;i<16;i++)
	ret.v[i] = v[i]+m.v[i];
	return ret;
}

dhMat dhMat::operator-(dhMat& m)
{
	dhMat ret;
	for (int i=0;i<16;i++)
	ret.v[i] = v[i]-m.v[i];
	return ret;
}

dhMat dhMat::operator *(dhMat& m)
{
	dhMat ret;
	for ( int i=0;i<4;i++)
	for ( int j=0;j<4;j++)
	{
		float sum = 0;

		for( int k=0;k<4;k++)
		sum+=( v[k*4+i]*m.v[j*4+k] );
			
		ret.v[j*4+i]	= sum;
	}

	return ret;
}

dhMat dhMat::operator *(float f)
{
	dhMat ret;
	for ( int i=0;i<4;i++)
	for ( int j=0;j<4;j++)
		ret.v[j*4+i]	= v[j*4+i]*f;

	ret.v[15] = 1;

	return ret;
}

dhVector dhMat::O()
{
	dhVector ret( v[12],v[13],v[14]);
	return ret;
}

dhMat dhMat::R()
{
	dhMat ret;
	memmove( ret.v,v,sizeof(float)*12);
	return ret;
}

dhMat dhMat::T()
{
	dhMat ret;
	ret.v[0]	= v[0];
	ret.v[1]	= v[4];
	ret.v[2]	= v[8];
	ret.v[3]	= v[12];

	ret.v[4]	= v[1];
	ret.v[5]	= v[5];
	ret.v[6]	= v[9];
	ret.v[7]	= v[13];

	ret.v[8]	= v[2];
	ret.v[9]	= v[6];
	ret.v[10]	= v[10];
	ret.v[11]	= v[14];

	ret.v[12]	= v[3];
	ret.v[13]	= v[7];
	ret.v[14]	= v[11];
	ret.v[15]	= v[15];

	return ret;
}

dhMat dhMat::H( float rx,float ry,float rz,dhVector p)
{
	dhMat ret;
	ret = ret.Trans(p)*ret.RotZ(RAD(rz))*ret.RotY(RAD(ry))*ret.RotX(RAD(rx));
	return ret;
}

dhVector dhMat::operator *(dhVector &h)
{
	dhVector ret;
	ret.x	= v[0]*h.x+ v[4]*h.y+v[8]*h.z+ v[12];
	ret.y	= v[1]*h.x+ v[5]*h.y+v[9]*h.z+ v[13];
	ret.z	= v[2]*h.x+ v[6]*h.y+v[10]*h.z+v[14];
	return ret;
}

void dhMat::operator =(dhVector &p)
{
	v[12]	= p.x;
	v[13]	= p.y;
	v[14]	= p.z;
}

dhMat dhMat::RotAxis( dhVector& o,dhVector& d,float f)
{
	dhMat unit;
	return RotAxis(o,d,f,unit);
}

dhMat dhMat::RotAxis( dhVector& o,dhVector& d,float f,dhMat prev)
{
	float a,b,c,s;
	
	// alpha angle between projected vector on xy plane and x axis
	dhVector pv	= d;
	pv.z	= 0;
	pv		= pv.Unit();
	
	c		= pv.x;
	c		= acos(c);
	s		= asin(pv.y);

	if ( c>0)	
	{
		dhVector v = dhVector(1,0,0)*pv;
		if ( v.z<0)	c*=-1;
	}
	else
		if ( s<0)	c	= 2*PI-c;

	a	= c;

	// beta angle between z axis and d-o;
	c	= d.Unit().z;
	b	= acos(c);
	if ( b==0)	a	= 0;
	
	dhMat rot;
	rot	= rot.RotZ(a)*rot.RotY(b)*rot.RotZ(f)*rot.RotY(-b)*rot.RotZ(-a);
	rot	= rot.Trans(prev.O())*rot.Trans(o*-1)*rot*rot.Trans(o)*rot.Trans(prev.O()*-1);
	//rot	= prev*rot.Trans(o*-1)*rot*rot.Trans(o)*prev.Inv();
	
	return rot;
}

dhMat dhMat::RotAxis( dhVector& d)
{
	float a,b,c,s;
	
	// alpha angle between projected vector on xy plane and x axis
	dhVector pv	= d;
	pv.z	= 0;
	pv		= pv.Unit();
	
	c		= pv.x;
	c		= acos(c);
	s		= asin(pv.y);

	if ( c>0)	
	{
		dhVector v = dhVector(1,0,0)*pv;
		if ( v.z<0)	c*=-1;
	}
	else
		if ( s<0)	c	= 2*PI-c;

	a	= c;

	// beta angle between z axis and d-o;
	c	= d.Unit().z;
	b	= acos(c);
	if ( b==0)	a	= 0;
	
	dhMat rot;
	rot	= rot.RotZ(a)*rot.RotY(b);
	return rot;
}

dhMat dhMat::Inv()
{
	dhMat ret;
	ret.v[0]	= v[0];
	ret.v[1]	= v[4];
	ret.v[2]	= v[8];
	ret.v[4]	= v[1];
	ret.v[5]	= v[5];
	ret.v[6]	= v[9];
	ret.v[8]	= v[2];
	ret.v[9]	= v[6];
	ret.v[10]	= v[10];

	dhVector pos = O();
	pos	= ret*(pos*-1);

	ret.v[12]	= pos.x;
	ret.v[13]	= pos.y;
	ret.v[14]	= pos.z;
	return ret;
}

dhVector dhMat::RPY()
{
	//RPY( a,b,c )	= Rot(z,a)Rot(y,b)Rot(x,c)
	/*
		[Cos(a)*Cos(b), -(Cos(c)*Sin(a)) + Cos(a)*Sin(b)*Sin(c), Cos(a)*Cos(c)*Sin(b) + Sin(a)*Sin(c)), 
		[Cos(b)*Sin(a), Cos(a)*Cos(c) + Sin(a)*Sin(b)*Sin(c)   , Cos(c)*Sin(a)*Sin(b) - Cos(a)*Sin(c)), 
		[-Sin(b)      , Cos(b)*Sin(c)                          , Cos(b)*Cos(c)
	*/

	float a,b,r,cb;	// from P.47 of J.Craig.
	b	= atan2( -v[2],sqrt( v[0]*v[0] + v[1]*v[1]) );
	cb	= cos(b);
	a	= atan2( v[1]/cb,v[0]/cb);
	r	= atan2( v[6]/cb,v[10]/cb);

	return dhVector(a,b,r);
}

dhMat dhMat::Scale(float x,float y,float z)
{
	dhMat ret;
	/*
	ret.v[3]	= x;
	ret.v[7]	= y;
	ret.v[11]	= z;
	*/

	return ret;
}

dhMat dhMat::Scale(float r)
{
	return Scale(r,r,r);
}

dhMat dhMat::DeScale()
{
	dhVector s;
	s.x	= sqrt(v[0]*v[0]+ v[4]*v[4]+ v[8]*v[8]);
	s.y	= sqrt(v[1]*v[1]+ v[5]*v[5]+ v[9]*v[9]);
	s.z	= sqrt(v[2]*v[2]+ v[6]*v[6]+ v[10]*v[10]);

	dhMat ret;
	memmove( ret.v,this->v,sizeof(float)*16);
	ret.v[0]/=s.x;
	ret.v[4]/=s.x;
	ret.v[8]/=s.x;
	ret.v[1]/=s.y;
	ret.v[5]/=s.y;
	ret.v[9]/=s.y;
	ret.v[2]/=s.z;
	ret.v[6]/=s.z;
	ret.v[10]/=s.z;
	
	return ret;
}