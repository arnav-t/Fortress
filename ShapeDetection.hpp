#include <cmath>

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

int hueMin = 20;
int hueMax = 35;
int satMin = 200;
long int shapeArea = 0;
int dilation = 2;
const int Cols = 4;

enum Color {Red, Yellow, Green, Blue};  
cv::Point ColorList[Cols] = {cv::Point(170,179), cv::Point(20,35), cv::Point(36,70), cv::Point(100,130)}; 
int ColorOrder[Cols] = {Red, Yellow, Green, Blue};

cv::Mat isolateColor(cv::Mat img, int hMin, int hMax, int sMin, int sMax, int vMin, int vMax)
{
	cv::cvtColor(img, img, CV_BGR2HSV);
	cv::Mat imgsep(img.rows, img.cols, CV_8UC1, cv::Scalar(0));
	cv::inRange(img, 
	            cv::Scalar(hMin,sMin,vMin), 
	            cv::Scalar(hMax,sMax,vMax),
	            imgsep);
	cv::cvtColor(img, img, CV_HSV2BGR);
	return imgsep;
} 

cv::Mat makeTemplate(cv::Mat img, cv::Point color)
{
	cv::Mat temp = isolateColor(img, color.x, color.y, 50, 255, 128, 255);
	std::vector<cv::Vec4i> hierarchy;
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(temp, contours, hierarchy, 
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
	std::cout << maxArea << std::endl;
	cv::Rect templateSize = cv::boundingRect(contours[maxIndex]);
	cv::Mat shapeTemplate(templateSize.height,templateSize.width,
	                      CV_8UC1,cv::Scalar(0)); 
	cv::drawContours(shapeTemplate,contours,maxIndex,255,
	                 CV_FILLED,8,cv::noArray(),INT_MAX,
	                 cv::Point(-templateSize.x,-templateSize.y));
	float scale = std::sqrt(shapeArea/(maxArea*1.0));
	resize(shapeTemplate, shapeTemplate, cv::Size(0,0), scale, scale);
	return shapeTemplate;
}

void getShapes(cv::Mat img, cv::Mat imgref, std::vector<cv::Point> &targets)
{
	cv::Mat imgsep = isolateColor(img,hueMin,hueMax,satMin,255,0,255);
	cv::dilate(imgsep,imgsep,cv::Mat(),
	           cv::Point(-1,-1),dilation);
	std::vector<cv::Vec4i> hierarchy;
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(imgsep, contours, hierarchy, 
	                 CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
	for(int i=0;i<contours.size();++i)
	{
		int ar = cv::contourArea(contours[i]);
		if(shapeArea < ar)
			shapeArea = ar;
		if(ar >= 500)
			cv::drawContours(imgsep,contours,i,255,CV_FILLED);	
	}
	cv::imshow("Arena", imgsep);
	cv::waitKey(1);
	for(int k=0;k<Cols;++k)
	{
		cv::Mat imgt = makeTemplate(imgref, ColorList[ColorOrder[k]]);
		cv::imshow("Template", imgt);
		cv::waitKey(0);
	}
}
