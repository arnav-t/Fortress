#include <iostream>
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

using namespace cv;
using namespace std;

int main()
{
	Mat imgtest = imread("arena.png",1);
	Mat imgref = imread(REF,1);
	vector<Point> targets;
	getShapes(imgtest, imgref, targets);
	/*VideoCapture vid(VIDEO);
	while(img.empty())
	{
		
	}*/
	return 0;
}

