// CVWnd.cpp : implementation file
//

#include "stdafx.h"
#include "KFTest.h"
#include "CVWnd.h"

#include "KFTestDoc.h"
#include "KFTestView.h"
extern CKFTestView *pv;

// CVWnd

// plot points
#define drawCross( center, color, d )                                 \
line( img, Point( center.x - d, center.y - d ),                \
Point( center.x + d, center.y + d ), color, 2, CV_AA, 0); \
line( img, Point( center.x + d, center.y - d ),                \
Point( center.x - d, center.y + d ), color, 2, CV_AA, 0 )




struct mouse_info_struct { int x,y; };
struct mouse_info_struct mouse_info = {-1,-1}, last_mouse;
vector<Point> mousev,kalmanv;

KalmanFilter KF(4, 2, 0);
Mat_<float> measurement(2,1); 
//vector<Point> mousev,kalmanv;

IMPLEMENT_DYNAMIC(CVWnd, CWnd)

CVWnd::CVWnd()
{
	bRun = FALSE;
	gcnt = 0;

	vc=1 ;
}

CVWnd::~CVWnd()
{
}


BEGIN_MESSAGE_MAP(CVWnd, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


void CVWnd::Create( CWnd *p, CRect rc)
{
	
	CWnd::Create( NULL,"",WS_CHILD|WS_VISIBLE,CRect(rc.TopLeft().x,rc.TopLeft().y,rc.Width(),rc.Height()),p,0);
	
	RedirectIOToConsole();

	Init();

	SetTimer(0,10,NULL);

}

void CVWnd::InitKF(BOOL bForceResetData, float vc_)
{
	img.setTo(cv::Scalar(0,0,0));

	//float v1 = pv->m_sld_vel.GetPos() * 0.1;

	vc = vc_;
	KF.transitionMatrix = *(Mat_<float>(4, 4) << 1,0,vc,0,   0,1,0,vc,  0,0,1,0,  0,0,0,1);

	//KF.transitionMatrix = *(Mat_<float>(4, 4) << 1,0,0,0,   0,1,0,0,  0,0,1,0,  0,0,0,1);	//Roy


	measurement.setTo(Scalar(0));

	KF.statePre.at<float>(0) = pt.x;
	KF.statePre.at<float>(1) = pt.y;
	KF.statePre.at<float>(2) = 0;
	KF.statePre.at<float>(3) = 0;
	setIdentity(KF.measurementMatrix);
	setIdentity(KF.processNoiseCov, Scalar::all(1e-4));
	setIdentity(KF.measurementNoiseCov, Scalar::all(10));
	setIdentity(KF.errorCovPost, Scalar::all(.1));
	// Image to show mouse tracking
	Mat img(480, 640, CV_8UC3);
				
	if(bForceResetData)
	{
		mousev.clear();
		kalmanv.clear();
	}

	gcnt = 0;

}

void CVWnd::Init()
{

	string str;
	
	

	img = Mat::zeros(480,640, CV_8UC3);

	if ( img.empty() ) 
    { 
	        cout << "Error loading the image" << endl;

        return;
    }
	else
	{
		printf("loaded an image %dx%d\n", img.rows, img.cols);

	}


	


}
// CVWnd message handlers




BOOL CVWnd::OnEraseBkgnd(CDC* pDC)
{
	CString buf;
	buf.Format("%d %d", pt.x, pt.y);

	/*
	pDC->Rectangle(CRect(0,0,640,480));
	pDC->TextOutA(10,10,buf);
	*/
	if ( img.empty() )  return 1;

	IplImage copy = img;
	cimg.CopyOf(&copy);
	cimg.DrawToHDC(pDC->GetSafeHdc(), CRect(0,0,640,480));


	return 1;
	//return CWnd::OnEraseBkgnd(pDC);
}


void CVWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default


	//if(bRun)
	if(pv->m_chk_run.GetCheck())
	if(nIDEvent==0)
	{

		GetCursorPos(&pt);
		ScreenToClient(&pt);


		mouse_info.x = pt.x;
		mouse_info.y = pt.y;


		if(pt.x>=0 && pt.x<640 && pt.y >=0 && pt.y<480)
		{

			if(gcnt==0)
			{
				InitKF();


			}
			else
			{
				float v1 = pv->m_sld_vel.GetPos() * 0.1;
				if(v1 != vc)
				{
					CString buf1; 
					buf1.Format("%.2f", v1);
					pv->m_info1.SetWindowTextA(buf1);
					InitKF(FALSE, v1);
				}

				img.setTo(cv::Scalar(0,0,0));

				 // First predict, to update the internal statePre variable
				 Mat prediction = KF.predict();
				 Point predictPt(prediction.at<float>(0),prediction.at<float>(1));
              
				 // Get mouse point
				 measurement(0) = pt.x;
				 measurement(1) = pt.y; 

				 // The update phase 
				Mat estimated = KF.correct(measurement);

				Point statePt(estimated.at<float>(0),estimated.at<float>(1));
				Point measPt(measurement(0),measurement(1));


				mousev.push_back(measPt);
				kalmanv.push_back(statePt);
				drawCross( statePt, Scalar(255,255,255), 5 );
				drawCross( measPt, Scalar(0,0,255), 5 );

				int i;
				for ( i = 0; i < mousev.size()-1; i++) 
					line(img, mousev[i], mousev[i+1], Scalar(255,255,0), 1);
     
				for (i = 0; i < kalmanv.size()-1; i++) 
					line(img, kalmanv[i], kalmanv[i+1], Scalar(0,255,255), 1);


			}
			

			gcnt++;
		}

		
		Invalidate();

	}

	CWnd::OnTimer(nIDEvent);
}


void CVWnd::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
}
