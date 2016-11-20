#pragma once



#ifdef USE_OPENCV_2_2
#include "CvvImage.h"
#endif

class BaseCV
{
public:
	BaseCV(void);
	~BaseCV(void);

public:
	


public:
	CvvImage	m_CvvImage;
	

	IplImage *img1;
	IplImage *img2;



public:

};
