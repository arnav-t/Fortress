#define ARDUINO "/dev/ttyACM0"

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
int distThres = 50;

std::ofstream arduino;

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

void sendCommand(char c)
{
	//arduino.seekp(0);
	arduino.put(c);
}

void init_arduino() 
{
    arduino.open(ARDUINO, std::ios::out);
}

void flashLED(int n)
{
	sendCommand((char)(n+48));
}

float getBotOrientation(cv::Mat img, std::vector<cv::Point> &targets)
{
	cv::Point front,back;
	cv::Mat imgCol = isolateColor(img,frontMin,frontMax,50,255,0,255);
	front = getCentroid(imgCol);
	imgCol = isolateColor(img,backMin,backMax,50,255,0,255);
	back = getCentroid(imgCol);
	if(std::abs(targets.front().y - front.y) + std::abs(targets.front().x - front.x) <= distThres)
	{
		flashLED(5-targets.size());
		targets.erase(targets.begin());
	}
	float botAngle = std::atan2(front.y - back.y, front.x - back.x);
	float pathAngle = std::atan2(targets.front().y - front.y, targets.front().x - front.x);
	return pathAngle - botAngle;
}

