#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "Channel.h"
#include "Gabor.h"


using namespace cv;

int main(void)
{
	//VideoCapture videoCapture("http://axis1.student.rit.edu/mjpg/video.mjpg"); //http://axis1.student.rit.edu/mjpg/video.mjpg
	//cvWaitKey(5000);

	//if (!videoCapture.isOpened()){

	//	int temp = 1;
	//}
	//Mat img;
	//Mat hsv;
	//Channel fourier = Channel();
	//namedWindow("RAW", 1);
	//namedWindow("HSV", 1);
	//namedWindow("LayerOther", 1);

	Gabor test = Gabor(1, 0.5, 0, 8, 0); // the last one is theta
	/*while (waitKey(10)!='ESC')
	{
		videoCapture >> img;
		bool temp =  img.empty();
		
		imshow("RAW", img);*/
		/*cvtColor(img, hsv, CV_RGB2HSV);*/
		
		//fourier.setImage(img);
	/*	imshow("RAW", fourier.getPyramid()[1]);
		imshow("HSV", fourier.getPyramid()[2]);*/
	//}



	
}