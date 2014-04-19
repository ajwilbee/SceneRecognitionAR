#include "opencv/cv.h"
#include <opencv2/core/core.hpp>
#include "opencv/highgui.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "Gabor.h"
#include "CvGabor.h"
#include "Color_Channel.h"
#include "Orienation_Channel.h"
#include <iostream>
using namespace std;

using namespace cv;

Mat* CreateGistVector(Mat I);

int main(void)
{
	VideoCapture videoCapture("http://axis2.student.rit.edu/mjpg/video.mjpg"); //http://axis1.student.rit.edu/mjpg/video.mjpg
	cvWaitKey(5000);

	if (!videoCapture.isOpened()){

		int temp = 1;
	}
	Mat img;
	Mat hsv;
	namedWindow("RAW", 1);
	namedWindow("HSV", 1);
	namedWindow("LayerOther", 1);

	
	while (waitKey(10)!='ESC')
	{
		videoCapture >> img;
		bool temp =  img.empty();
		Mat filter = Mat(img.size(), img.type() );//CV_32FC1
		cvtColor(img, hsv, CV_RGB2HSV);

		//Gabor test = Gabor(1, 0.5, 0, 8, 0); // the last one is theta

		CvGabor temp1 = CvGabor(0, .25, 2);
		IplImage ipl_img = img.operator IplImage();
		IplImage *filtered = &filter.operator IplImage();
		temp1.conv_img(&ipl_img, filtered, 2);
		Mat cvmat(filtered);

		int t1 = img.type();
		int t2 = cvmat.type();
		imshow("RAW", img);
		imshow("HSV", cvmat);
	}

	

	
}

Mat* CreateGistVector(Mat I){
	
	//Color_Channel CC = Color_Channel(I);
	//Orienation_Channel OC = Orienation_Channel(I);
	////make one solid GistVector
	//double** GistVector = ;
	//int range = 4;
	//for (int i = 0; i < range; i++){
	//	GistVector[i] = *OC.F0.getExtractedFeatures;
	//}

	////int offset = range;
	////for (int i = 0; i < range; i++){
	////	GistVector[offset + i] = &OC.F45.getExtractedFeatures[i];
	////}
	////
	////offset = offset + range;
	////for (int i = 0; i < range; i++){
	////	GistVector[offset + i] = &OC.F90.getExtractedFeatures[i];
	////}
	////offset = offset + range;
	////for (int i = 0; i < range; i++){
	////	GistVector[offset + i] = &OC.F135.getExtractedFeatures[i];
	////}
	////offset = offset + range;
	////int range = 6;
	////for (int i = 0; i < range; i++){
	////	GistVector[offset + i] = &CC.RG.getExtractedFeatures[i];
	////}
	////offset = offset + range;
	////for (int i = 0; i < range; i++){
	////	GistVector[offset + i] = &CC.BY.getExtractedFeatures[i];
	////}
	////offset = offset + range;
	////for (int i = 0; i < range; i++){
	////	GistVector[offset + i] = &CC.Intensity.getExtractedFeatures[i];
	////}

	return &Mat();
}
