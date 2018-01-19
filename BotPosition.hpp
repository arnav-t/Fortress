int botMax = 165;
int botMin = 155;

Vector getBotPosition(cv::Mat img)
{
	cv::Mat imgCol(img.rows, img.cols, cv::CV_8UC1, Scalar(0));
	cvtColor(img,img,CV_BGR2HSV);
	
	for(int y=0; y<img.rows, ++y)
	{
		for(int x=0; x<img.cols; ++x)
		{
			
		}
	}
}
