#ifndef CMATH
#define CMATH
#include <cmath>
#endif

#ifndef OPENCV
#define OPENCV
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

int frontMin = 35;
int frontMax = 70;
int backMin = 100;
int backMax = 130;

cv::Point getCentroid(cv::Mat img)
{
	std::vector<cv::Vec4i> hierarchy;
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(img, contours, hierarchy, 
	                 CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
	int maxIndex = 0;
	int maxArea = 0;
	for(int i=0;i<contours.size();++i)
	{
		int ar = cv::contourArea(contours[i]);
		if(maxArea < ar)
		{
			maxArea = ar;
			maxIndex = i;
		}	
	}
	cv::Rect bounds = cv::boundingRect(contours[maxIndex]);
	cv::Point centroid(bounds.x + bounds.width/2,bounds.y + bounds.height/2);
	return centroid; 
}

float getBotOrientation(cv::Mat img)
{
	cv::Point front,back;
	cv::Mat imgCol = isolateColor(img,frontMin,frontMax,50,255,0,255);
	front = getCentroid(imgCol);
	imgCol = isolateColor(img,backMin,backMax,50,255,0,255);
	back = getCentroid(imgCol);
	return std::atan2(front.y - back.y, front.x - back.x);
}
