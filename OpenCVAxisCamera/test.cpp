#include "opencv/cv.h"
#include <opencv2/core/core.hpp>
#include "opencv/highgui.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "Channel.h"
#include "Gabor.h"
#include "CvGabor.h"
#include <iostream>
using namespace std;

// change to make sure
using namespace cv;

int main(void)
{
	VideoCapture videoCapture("http://axis2.student.rit.edu/mjpg/video.mjpg"); //http://axis1.student.rit.edu/mjpg/video.mjpg
	cvWaitKey(5000);

	if (!videoCapture.isOpened()){

		int temp = 1;
	}
	Mat img;
	Mat hsv;
	Channel fourier = Channel();
	namedWindow("RAW", 1);
	namedWindow("HSV", 1);
	namedWindow("LayerOther", 1);

	
	while (waitKey(10)!='ESC')
	{
		videoCapture >> img;
		bool temp =  img.empty();
		
		
		cvtColor(img, hsv, CV_RGB2HSV);
		

		imshow("RAW", img);
		imshow("HSV", hsv);
	}

	//const char* filename = "opencv-logo-white.png";
	//Mat I = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
	//Gabor test = Gabor(1, 0.5, 0, 8, 0); // the last one is theta

	//imshow("test", I);
	//cout << "end";
	//CvGabor temp = CvGabor(1, .5, 1);

	
}