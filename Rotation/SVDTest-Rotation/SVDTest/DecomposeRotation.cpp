#include "StdAfx.h"
#include "DecomposeRotation.h"

//////////////////////////////
// Written by Seung-Chan Kim
// dalek@kaist.ac.kr
// September 25th, 2014


#ifndef DEG
#define DEG(a)          (180.*a/PI )
#endif

using namespace cv;
DecomposeRotation::DecomposeRotation(void)
{
}

DecomposeRotation::~DecomposeRotation(void)
{
}

void DecomposeRotation::Calc()
{
	int n = A.GetSize();

	int i;
	dhVector centroid_A, centroid_B;
	centroid_A.Vector(0,0,0);
	centroid_B.Vector(0,0,0);

	for(i=0; i<n; i++)
	{
		centroid_A.x += A.GetAt(i).x;
		centroid_A.y += A.GetAt(i).y;
		centroid_A.z += A.GetAt(i).z;

		centroid_B.x += B.GetAt(i).x;
		centroid_B.y += B.GetAt(i).y;
		centroid_B.z += B.GetAt(i).z;
	}

	centroid_A = centroid_A.Scaling(1.0/(float) n);
	centroid_B = centroid_B.Scaling(1.0/(float) n);	//OK


	Ac.RemoveAll();
	Bc.RemoveAll();


	for(i=0; i<n; i++)
	{
		dhVector a1 = A.GetAt(i) - centroid_A;
		dhVector b1 = B.GetAt(i) - centroid_B;
			
		Ac.Add(a1);
		Bc.Add(b1);

	}

	//% covariance matrix
	// H = Ac' * Bc;

	dhMat m1;
	
	memset( m1.v,0,sizeof(float)*16);
	m1.v[0]	= m1.v[5]	= m1.v[10]	= 0;
	m1.v[15]	= 1;

	for(i=0; i<n; i++)
	{

		dhVector a1 = Ac.GetAt(i);
		dhVector b1 = Bc.GetAt(i);

		m1.v[0] = m1.v[0] + a1.x * b1.x;
		m1.v[4] = m1.v[4] + a1.x * b1.y;
		m1.v[8] = m1.v[8] + a1.x * b1.z;

		m1.v[1] = m1.v[1] + a1.y * b1.x;
		m1.v[5] = m1.v[5] + a1.y * b1.y;
		m1.v[9] = m1.v[9] + a1.y * b1.z;


		m1.v[2] = m1.v[2] + a1.z * b1.x;
		m1.v[6] = m1.v[6] + a1.z * b1.y;
		m1.v[10] = m1.v[10] + a1.z * b1.z;

	}
	
	double m[3][3] = {{m1.v[0], m1.v[4], m1.v[8]}, {m1.v[1], m1.v[5], m1.v[9]}, {m1.v[2], m1.v[6], m1.v[10]}};
	cv::Mat h2 = cv::Mat(3, 3, CV_64F, m);

	CvMat* H2 = cvCreateMat(3,3, CV_32F);
	
	H2->data.fl[0] = m1.v[0];
	H2->data.fl[3] = m1.v[1];
	H2->data.fl[6] = m1.v[2];

	H2->data.fl[1] = m1.v[4];
	H2->data.fl[4] = m1.v[5];
	H2->data.fl[7] = m1.v[6];

	H2->data.fl[2] = m1.v[8];
	H2->data.fl[5] = m1.v[9];
	H2->data.fl[8] = m1.v[10];


	Dbg(" Covariance matrix, H=");
	Print3x3CvMat(H2);


	// Performs Singular Value Decomposition of a matrix 
	CvMat *W = cvCreateMat(3,3, CV_32F);
	CvMat *U = cvCreateMat(3,3, CV_32F);
	CvMat *V = cvCreateMat(3,3, CV_32F);

	CvMat *ret_R = cvCreateMat(3,3, CV_32F);
	
	// W is a diagonal matrix : m-by-n
	// U and V are m-by-m and n-by-n unitary matrices

	cvSVD(H2, W, U, V, CV_SVD_U_T);

	Dbg("");
	Dbg("W=");
	Print3x3CvMat(W);	//S

	Dbg("");
	Dbg("UT=");
	Print3x3CvMat(U);

	Dbg("");
	Dbg("V=");
	Print3x3CvMat(V);

	cvMatMul( V, U, ret_R);

	
	Dbg("");
	Dbg("ret_R=");
	Print3x3CvMat(ret_R);	//OK == checked
	
	// Convert ret_R to ret_R2
	dhMat ret_R2;

	
	SetGLMat(ret_R->data.fl, ret_R2.v);

	

	dhVector rpy = ret_R2.RPY();

	float r = DEG(rpy.x);
	float p = DEG(rpy.y);
	float y = DEG(rpy.z);

	Dbg("RPY DEG: %.2f, %.2f, %.2f", r, p, y);


	//ret_t = -ret_R*centroid_A' + centroid_B';
	
	//dhVector ret_t2 = 

	

	cvReleaseMat(&ret_R);
	

	cvReleaseMat(&W);
	cvReleaseMat(&U);
	cvReleaseMat(&V);
	cvReleaseMat(&H2);


/*
	Mat H2=Mat(3,3,CV_32FC1);
	H2.at(1,1) = m1.v[0];
	H2.at(2,1) = m1.v[1];
	H2.at(3,1) = m1.v[2];


	H2.at(1,2) = m1.v[4];
	H2.at(2,2) = m1.v[5];
	H2.at(3,2) = m1.v[6];

	H2.at(1,3) = m1.v[8];
	H2.at(2,3) = m1.v[9];
	H2.at(3,3) = m1.v[10];

	float nn = 0;

	Dbg(" Covariance matrix, H=");
	Print3x3Mat(H2);


*/

	//[U,S,V] = svd(H);

}

void DecomposeRotation::LoadData(char* fn_A,char* fn_B, char* fn_R, char* fn_t)
{
	A.RemoveAll();
	B.RemoveAll();

	{
		vToken tok1;
		tok1.Load(fn_A);
		tok1.SetSeparator("\n");
		int i;
		int n = tok1.GetSize();
		for(i=0; i<n; i++)
		{
			vToken tok2(tok1.GetAt(i));
			tok2.SetSeparator(",");
			dhVector v1;
			v1.Vector(tok2.f(0),tok2.f(1),tok2.f(2));
			
			A.Add(v1);
			Dbg(" %.2f,%.2f,%.2f", v1.x, v1.y, v1.z); 
			

		}
	}
	{
		vToken tok1;
		tok1.Load(fn_B);
		tok1.SetSeparator("\n");
		int i;
		int n = tok1.GetSize();
		for(i=0; i<n; i++)
		{
			vToken tok2(tok1.GetAt(i));
			tok2.SetSeparator(",");
			dhVector v1;
			v1.Vector(tok2.f(0),tok2.f(1),tok2.f(2));
			
			B.Add(v1);
			Dbg(" %.2f,%.2f,%.2f", v1.x, v1.y, v1.z); 
			
		}
	}

	{
		vToken tok1;
		tok1.Load(fn_R);
		tok1.SetSeparator("\n");

		R.I();

		vToken tokR0(tok1[0]);
		vToken tokR1(tok1[1]);
		vToken tokR2(tok1[2]);

		tokR0.SetSeparator(",");
		tokR1.SetSeparator(",");
		tokR2.SetSeparator(",");


		R.v[0] = tokR0.f(0);
		R.v[4] = tokR0.f(1);
		R.v[8] = tokR0.f(2);

		R.v[1] = tokR1.f(0);
		R.v[5] = tokR1.f(1);
		R.v[9] = tokR1.f(2);

		R.v[2] = tokR2.f(0);
		R.v[6] = tokR2.f(1);
		R.v[10] = tokR2.f(2);


	}

	{
		vToken tok1;
		tok1.Load(fn_t);
		tok1.SetSeparator("\n");

		t.Vector(tok1.f(0),tok1.f(1),tok1.f(2));


	}



}