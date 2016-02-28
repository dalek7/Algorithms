#pragma once

// for testing Kalman Filter implemented in OpenCV
// Seung-Chan Kim
// 2014/7/23

// CVWnd
#include "opencv2/opencv.hpp"
//#pragma comment (lib, "cv.lib")
#pragma comment (lib, "opencv_core2410.lib")
#pragma comment (lib, "opencv_flann2410.lib")
#pragma comment (lib, "opencv_highgui2410.lib")
#pragma comment (lib, "opencv_video2410.lib")

using namespace std;
using namespace cv;

#include "../lib/CvvImage.h"



class CVWnd : public CWnd
{
	DECLARE_DYNAMIC(CVWnd)

public:
	CVWnd();
	virtual ~CVWnd();


public:
	
	virtual void Create( CWnd *, CRect rc=CRect(0,0,640,480));
	BOOL bRun;
	void ToggleRun()
	{
		bRun^=1;

	}
	CPoint pt;

	void InitKF(BOOL bForceResetData=TRUE,float vc_ = 1);
	void Init();
	
	Mat img;
	CvvImage cimg;


	int gcnt;
	float vc;
	//KALMAN
public:
	
	

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};


