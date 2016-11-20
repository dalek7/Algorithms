#if !defined( __DH_VECTOR__)
#define __DH_VECTOR__

//#define _DLL_	// for dll use.

#include <math.h>
#include <stdio.h>
	
#ifdef DH3D_DX
#include "dx\dh3ddirectx.h"
#endif

#define REAL	float
//#define REAL	double
//#define dbl     REAL

#define COORD_CARTESIAN		0
#define COORD_CYLRINDRICAL	1

//#ifndef vString
//#include "vString.h"
//#endif

#ifdef _DLL_
class AFX_EXT_CLASS dhVector
#else
class dhVector 
#endif
{
public:

        dhVector();     
        dhVector( REAL xi,REAL yi,REAL zi);
		dhVector( REAL xi,REAL yi);
		dhVector( CPoint);
        //~dhVector();
		
		BOOL		operator==(dhVector);
		void		operator+=(dhVector);
		void		operator-=(dhVector);
        dhVector	operator+(dhVector);
		dhVector	operator+(REAL);
        dhVector	operator-(dhVector);
        dhVector	operator*(dhVector);	// cross
		dhVector	operator*(REAL);		// cross
		dhVector	operator/(REAL);		// cross
		operator	CPoint();

#ifdef DH3D_DX
		operator	D3DVECTOR();
#endif		
#ifdef __xRGB__
		operator	xRGB()
		{
			xRGB	ret;
			ret.r	= x; ret.g = y; ret.b =z; return ret;
		}
#endif
        dhVector	Unit();
        void		UnitInt();      // internally unit
        REAL		Abs();
		REAL		Distance();
		REAL		Dot( dhVector );	// dot product
		dhVector	Mul( dhVector );
		dhVector	Div( dhVector );

		REAL		Distance(const dhVector& v1);


#ifdef __AFXWIN_H__
		void		Print( CDC *pDC,int xi,int yi);
#endif
		CString		Print(CString st=CString(""));
		dhVector	Cyl();
		dhVector	Car();
		
		REAL 		Norm();
        dhVector    Scaling( REAL );
		dhVector	Scaling( REAL,REAL,REAL);
		dhVector	Scaling(dhVector);
		dhVector    Trans( dhVector );
        dhVector    Trans( REAL xi,REAL yi,REAL zi);
		void		SwapXZ();
		void		SwapXY();
		void		SwapYZ();
        void        Vector( REAL,REAL,REAL);
		void        Vector( REAL,REAL);
		REAL		Angle( dhVector ,dhVector );	//  a  ^   b 
													//    this

		void		Deg180();
		void		Deg360();
		REAL*		GetData();

        // data
        REAL			x,y,z;

protected:
		BOOL		bCoord;
	
};


#endif


