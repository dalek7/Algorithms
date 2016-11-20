/*
 *  ddCVMacro.h
 *  MLTest
 *
 *  Created by Darcy1214 on 10/19/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _DD_CVMACRO_H_
#define _DD_CVMACRO_H_

#include "3d/dhVector.h"

#ifndef PI
#define PI	3.1415926535897932f
#endif

#define CPointf CvPoint2D32f


//CvScalar color = CV_RGB( 0, 255, 255 );
//CV_RGB( 0, 255, 255 )

static CvScalar colors[] = 
 {
 {{0,0,255}},
 {{0,128,255}},
 {{0,255,255}},
 {{0,255,0}},
 {{255,128,0}},
 {{255,255,0}},
 {{255,0,0}},
 {{255,0,255}},
 {{255,255,255}}
 };



#define cvLine2simple(img,  pt1,  pt2, color) \
	cvLine(img,  cvPoint(pt1.x, pt1.y),  cvPoint(pt2.x, pt2.y),  color,  1,  8,  0);


#define cvLine2(img,  pt1,  pt2, color,  thickness,  lineType, shift) \
	cvLine(img,  cvPoint(pt1.x, pt1.y),  cvPoint(pt2.x, pt2.y),  color,  thickness,  lineType,  shift);

#define cvCircle2( img, pt1, r, width ) \
		cvCircle( img, cvPoint(pt1.x, pt1.y), r, CV_RGB( 0, 255, 255 ), width );

#define draw_cross( img, center, color, d,t )                                 \
					cvLine( img,	cvPoint( center.x - d, center.y - d ),                \
									cvPoint( center.x + d, center.y + d ), color, t, 0 ); \
					cvLine( img,	cvPoint( center.x + d, center.y - d ),                \
									cvPoint( center.x - d, center.y + d ), color, t, 0 )



#define draw_cross2( img, center, d,t )                                 \
					cvLine( img,	cvPoint( center.x - d, center.y - d ),                \
									cvPoint( center.x + d, center.y + d ), CV_RGB( 0, 255, 255 ), t, 0 ); \
					cvLine( img,	cvPoint( center.x + d, center.y - d ),                \
									cvPoint( center.x - d, center.y + d ), CV_RGB( 0, 255, 255 ), t, 0 )

#define Conv2D(p1, p2)	\
		p2.x = p1.x; \
		p2.y = p1.y; \


inline void cvText(IplImage *src, char* str, CPoint pt, CvScalar color = cvScalar(255,255,255))
{
	CvFont font;
	double hScale=0.5;
	double vScale=0.5;
	int    lineWidth=1;
	cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);
	
	cvPutText (src,str,cvPoint(pt.x,pt.y), &font, color);
}



inline void cvText2(IplImage *src, CString str_, CPoint pt, CvScalar color = cvScalar(255,255,255))
{
	char* str = str_.GetBuffer(str_.GetLength());
	CvFont font;
	double hScale=0.5;
	double vScale=0.5;
	int    lineWidth=1;
	cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);
	
	cvPutText (src,str,cvPoint(pt.x,pt.y), &font, color);
}



inline void cvDoubleMatPrint( const CvMat* mat )
{
    int i, j;
    for( i = 0; i < mat->rows; i++ )
    {
        for( j = 0; j < mat->cols; j++ )
        {
            Dbg( "%f ",cvmGet( mat, i, j ) );
        }
        Dbg( "\n" );
    }
}



inline void DrawArrow(IplImage* img, dhVector stPt, dhVector endPt, float scale_arrow,  CvScalar clr = CV_RGB(255,0,255), float startCircleSz=2)
{

	cvCircle(img, cvPoint( stPt.x , stPt.y ),startCircleSz ,clr , -1);
	cvLine( img,	cvPoint( stPt.x , stPt.y ), cvPoint( endPt.x, endPt.y), clr, 1, 0 );


	double angle; 

	angle		= atan2( (double) stPt.y - endPt.y, (double) stPt.x - endPt.x );

	double hypotenuse; 
	hypotenuse = sqrt( (stPt.y - endPt.y)*(stPt.y - endPt.y)  + (stPt.x - endPt.x)*(stPt.x - endPt.x) );

	dhVector ptArrow1, ptArrow2;

	ptArrow1.x = (endPt.x + scale_arrow *hypotenuse* cos(angle + PI / 4.0));
	ptArrow1.y = (endPt.y + scale_arrow *hypotenuse* sin(angle + PI / 4.0));

	ptArrow2.x = (endPt.x + scale_arrow *hypotenuse* cos(angle - PI / 4.0));
	ptArrow2.y = (endPt.y + scale_arrow *hypotenuse* sin(angle - PI / 4.0));

	
	cvLine( img,	cvPoint( endPt.x , endPt.y ),                
						cvPoint( ptArrow1.x , ptArrow1.y ), clr, 1, 0 );

	cvLine( img,	cvPoint( endPt.x , endPt.y ),                
						cvPoint( ptArrow2.x , ptArrow2.y ), clr, 1, 0 );
	

}  


inline float calcFoV(float f, float c)
{
	float v = 2* atan (c / f);	//half of FoV
	v = v * 180.0/PI;
	return v;
}


inline float calcF(float fov, float c)
{
return c / tan(fov / 2.0 * PI / 180.0);

}
/*
inline float calcF(float fov_half_deg, float c)
{
	return c / tan(fov_half_deg / 2.0 * PI / 180.0);
	
}
*/

inline void UpdateDistortions4( CvMat* distortion, const float* d)
{
    
	distortion->data.fl[0*distortion->cols+0] = d[0];
	distortion->data.fl[1] = d[1];
	distortion->data.fl[2] = d[2];
	distortion->data.fl[3] = d[3];
	//distortion->data.fl[4] = d[4];
    
    
}


inline void UpdateDistortions5( CvMat* distortion, const float* d)
{
    
	distortion->data.fl[0*distortion->cols+0] = d[0];
	distortion->data.fl[1] = d[1];
	distortion->data.fl[2] = d[2];
	distortion->data.fl[3] = d[3];
	distortion->data.fl[4] = d[4];
    
    
}




inline void MakeCameraMatrix(float fov_x, float fov_y, CvPoint2D32f canvas_sz, float* vout)
{

	float fx,fy, cx,cy;
	//
	//CvSize sz = [self GetImgSz];

	cx = canvas_sz.x/2;
	cy = canvas_sz.y/2;

	fx = calcF( fov_x, cx);
	fy = calcF( fov_y, cy);//fx;

	float v[9]={0,};
	v[0] = fx;
	v[1] = 0;
	v[2] = cx;

	v[3] = 0;
	v[4] = fy;
	v[5] = cy;

	v[6] = 0;
	v[7] = 0;
	v[8] = 1;

	for(int i=0; i<9; i++)
	{
		vout[i] = v[i];
    
	}


}
// row to col vectors
inline void SetGLMat(const float *R_, const float *T_, float *H_)//gl_4x4
{
	H_[0] = R_[0];
	H_[1] = R_[3];
	H_[2] = R_[6];
	H_[3] = 0; 

	H_[4] = R_[1];
	H_[5] = R_[4];
	H_[6] = R_[7];
	H_[7] = 0;

	H_[8] = R_[2];
	H_[9] = R_[5];
	H_[10] = R_[8];
	H_[11] = 0;

	H_[12] = T_[0];
	H_[13] = T_[1];
	H_[14] = T_[2];
	H_[15] = 1;

}

inline void SetGLMat(const float *R_, float *H_)//gl_4x4
{

	H_[0] = R_[0];
	H_[1] = R_[3];
	H_[2] = R_[6];
	H_[3] = 0; 

	H_[4] = R_[1];
	H_[5] = R_[4];
	H_[6] = R_[7];
	H_[7] = 0;

	H_[8] = R_[2];
	H_[9] = R_[5];
	H_[10] = R_[8];
	H_[11] = 0;

	H_[12] = 0;//T_[0];
	H_[13] = 0;//T_[1];
	H_[14] = 0;//T_[2];
	H_[15] = 1;

	

}
inline void Print3x3CvMat(CvMat *M)
{
	for(int i = 0; i < M->rows; i++)
	{
		Dbg("%.4f %.4f %.4f", M->data.fl[3*i+ 0], M->data.fl[3*i+ 1], M->data.fl[3*i+ 2]);
		
	}
}


inline void Print3x3Mat(const cv::Mat& mat)
{

	
	for(int i = 0; i <mat.rows; i++)
	{
		Dbg("%.4f %.4f %.4f", mat.at<double>(3*i,1),mat.at<double>(3*i,2),mat.at<double>(3*i,3));
		
	}

}


//fx = cx / tan(fov_x_deg / 2.0 * PI / 180.0);
#endif /* _DD_CVMACRO_H_ */