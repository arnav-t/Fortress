#include <iostream>
#include <fstream>
#include <sys/ioctl.h>
#include <queue>

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

#include "ShapeDetection.hpp"
#include "BotPosition.hpp"

#define REF "final.png"

int everyNth = 5;
int skip = 10;

using namespace cv;
using namespace std;

int main()
{
	VideoCapture vid(VIDEO);
	Mat frame;
	for(int i=0;i<skip;++i)
	{
		vid >> frame;
	}
	Mat imgref = imread(REF,1);
	vector<Point> targets;
	getShapes(frame, imgref, targets);
	init_arduino();
	flashLED(4);
	int k = 1;
	while(1)
	{
		if(k%everyNth == 0)
		{
			
		}
	}
	return 0;
}

