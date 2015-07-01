// Canny2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>

char wndname[] = "Edge";
char tbarname[] = "Threshold";
int edge_thresh = 1;
IplImage *img = 0, *cedge = 0, *edge = 0, *gray = 0;

void on_trackbar(int h)
{
	cvSmooth(gray, edge, CV_BLUR, 3, 3, 0, 0);
	cvNot(gray, edge);

	//canny
	cvCanny(gray, edge, (float)edge_thresh, (float)edge_thresh * 3, 3);

	cvZero(cedge);
	cvCopy(img, cedge, edge);
	cvShowImage(wndname, cedge);
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	const char *img_name = "F:\\图片\\001.jpg";
	if ((img = cvLoadImage(img_name, 1)) == 0)
	{
		return -1;
	}

	//create the output image
	cedge = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 3);
	//convert to gray scale
	gray = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
	edge = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
	cvCvtColor(img, gray, CV_BGR2GRAY);
	//create window
	cvNamedWindow(wndname, 1);
	//create toolbar
	cvCreateTrackbar(tbarname,wndname,&edge_thresh,100,on_trackbar);

	//show the image
	on_trackbar(0);

	cvWaitKey(0);
	cvReleaseImage(&img);
	cvReleaseImage(&cedge);
	cvReleaseImage(&edge);

	cvDestroyWindow(wndname);

	return 0;
}

