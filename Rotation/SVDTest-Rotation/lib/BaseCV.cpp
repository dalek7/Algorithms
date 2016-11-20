#include "StdAfx.h"
#include "BaseCV.h"

BaseCV::BaseCV(void)
{
	img1 = NULL;
	img2 = NULL;
}

BaseCV::~BaseCV(void)
{
	if(img1)
		cvReleaseImage(&img1);

	if(img2)
		cvReleaseImage(&img2);

}


