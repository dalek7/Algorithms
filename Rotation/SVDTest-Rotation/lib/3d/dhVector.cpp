#include "stdafx.h"
#include "dhvector.h"
#include <math.h>

dhVector::dhVector()     //dummy
{
	bCoord	= COORD_CARTESIAN;
}

dhVector::dhVector( CPoint pt )
{
	x	= pt.x;
	y	= pt.y;
	z	= 0;
}

dhVector::dhVector( REAL xi,REAL yi,REAL zi) {	x = xi;    y = yi;    z = zi;	bCoord	= COORD_CARTESIAN;}
dhVector::dhVector( REAL xi,REAL yi)		 {	x = xi;    y = yi;    z = 0;	bCoord	= COORD_CARTESIAN;}

void dhVector::Vector( REAL x1,REAL y1,REAL z1)
{
    x = x1;
    y = y1;
    z = z1;
}

void dhVector::Vector( REAL x1,REAL y1)
{
    x = x1;
    y = y1;
    z = 0;
}

BOOL dhVector::operator==(dhVector vec)
{
	if ( vec.x==x && vec.y==y && vec.z==z)
	return TRUE;
	return FALSE;
}

void dhVector::operator +=( dhVector v)
{
	x+=v.x;
	y+=v.y;
	z+=v.z;
}

void dhVector::operator -=( dhVector v)
{
	x-=v.x;
	y-=v.y;
	z-=v.z;
}

dhVector dhVector::operator+(dhVector vec)
{
dhVector temp;

     temp.x = x+vec.x;
     temp.y = y+vec.y;
     temp.z = z+vec.z;

     return temp;

}

dhVector dhVector::operator-(dhVector vec)
{
dhVector temp;

     temp.x = x-vec.x;
     temp.y = y-vec.y;
     temp.z = z-vec.z;

     return temp;
}



dhVector dhVector::operator*(dhVector vec)        // cross operator
{
dhVector temp;

     //   i  j  k
     //   a  b  c
     //   d  e  f
     //   bf-ec   cd-af     ae-db

     temp.x = y*vec.z-z*vec.y;
     temp.y = z*vec.x-x*vec.z;
     temp.z = x*vec.y-y*vec.x;

     return temp;
}



dhVector dhVector::operator*(REAL r)        // cross operator
{
dhVector temp;
	temp	= Scaling(r);
	return temp;
}

dhVector dhVector::operator+(REAL r)        // shift
{
dhVector temp;
	temp.x	= x+r;
	temp.y	= y+r;
	temp.z	= z+r;
	return temp;
}

dhVector dhVector::operator/(REAL r)        
{
dhVector temp;
	temp.x	= x/r;
	temp.y	= y/r;
	temp.z	= z/r;
	return temp;
}

#ifdef DH3D_DX
dhVector::operator D3DVECTOR()
{
	D3DVECTOR ret = { x,y,z };
	return ret;
}
#endif

dhVector::operator CPoint()
{
	CPoint ret(x,y);
	return ret;
}
dhVector dhVector::Mul( dhVector vec )
{
	dhVector temp;
	temp.x	= x*vec.x;
	temp.y	= y*vec.y;
	temp.z	= z*vec.z;

	return temp;
}

dhVector dhVector::Div( dhVector vec )
{
	dhVector temp;
	temp.x	= x/vec.x;
	temp.y	= y/vec.y;
	temp.z	= z/vec.z;

	return temp;
}

REAL dhVector::Dot(dhVector vec)		// dot product
{
dhVector temp;

     temp.x = x*vec.x;
     temp.y = y*vec.y;
     temp.z = z*vec.z;
	
	 REAL ret = temp.x+temp.y+temp.z;
     return (REAL) ( ret );
}


dhVector dhVector::Unit()
{
REAL l;
dhVector a(0,0,0);

    l = Abs();
    if ( l!=0.0 )
    {
      a.x = x/l;
      a.y = y/l;
      a.z = z/l;
    }
    return a;
}

REAL dhVector::Abs()
{
    REAL ret = x*x+y*y+z*z;
    ret = sqrt(ret);

    return ret;
}

REAL dhVector::Norm()
{
	return Abs();

}
REAL dhVector::Distance()
{
	return Abs();
}

REAL dhVector::Distance(const dhVector& v1)
{
	dhVector v = *this -v1 ;

	return v.Abs();
}


#ifdef __AFXWIN_H__
void dhVector::Print(CDC *pDC,int xi,int yi)
{
    CString buf;
    buf.Format( "[%3.1f][%3.1f][%3.1f] = ABS %3.1f",x,y,z,Abs() );
    
    //pDC->TextOut( xi,yi,buf,buf.GetLength() );
	pDC->DrawText( buf,CRect(CPoint(xi,yi),pDC->GetTextExtent(buf)),DT_INTERNAL);
}
#endif

dhVector dhVector::Scaling( REAL r)
{
dhVector temp;

        temp.x = x*r;
        temp.y = y*r;
        temp.z = z*r;

        return temp;
}

dhVector dhVector::Scaling( dhVector s)
{
	return Scaling( s.x,s.y,s.z );
}

dhVector dhVector::Scaling( REAL sx,REAL sy,REAL sz)
{
dhVector temp;

		temp.x	= x*sx;
		temp.y	= y*sy;
		temp.z	= z*sz;

		return temp;
}

dhVector dhVector::Trans( dhVector t)
{
dhVector temp;

        temp.x = x+t.x;
        temp.y = y+t.y;
        temp.z = z+t.z;

        return temp;
}

dhVector dhVector::Trans( REAL xi,REAL yi,REAL zi)
{
dhVector temp;

        temp.x = x+xi;
        temp.y = y+yi;
        temp.z = z+zi;

        return temp;
}


dhVector dhVector::Car()
{
dhVector temp;
dhVector ret;	
	temp.Vector( x,y,z);
	ret.x	= temp.x*cos(temp.y);
	ret.y	= temp.x*sin(temp.y);
	ret.z	= temp.z;

	return ret;
}

dhVector dhVector::Cyl()
{
dhVector temp;
	
	temp.Vector( x,y,z);
	return temp;
}


REAL dhVector::Angle( dhVector f,dhVector s)
{
	REAL ret = acos( (*this*f).Dot(*this*s) );
	dhVector a,b;
	
	ret	= ret*( a.Unit()*b.Unit() ).Dot(this->Unit() );
	return ret;
}

CString dhVector::Print(CString st)
{
	CString ret;
	ret.Format( CString("%s =  %4.2f,%4.2f,%4.2f"),st,x,y,z);
	return ret;
}	

void dhVector::SwapXZ()
{
	REAL tmp	= z;
	z	= x;
	x	= tmp;
}

void dhVector::Deg180()
{
	if ( x>180)	x-=360.;
	if ( y>180)	y-=360.;
	if ( z>180)	z-=360.;
}

void dhVector::Deg360()
{
	if ( x<0)	x+=360.;
	if ( y<0)	y+=360.;
	if ( z<0)	z+=360.;
}

REAL* dhVector::GetData()
{
	REAL f[3];
	f[0]	= x;
	f[1]	= y;
	f[2]	= z;
	return f;
}