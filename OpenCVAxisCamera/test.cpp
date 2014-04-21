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

void createSobels();
Mat* CreateGistVector(Mat I);
const double pi = 3.14159;
Mat d45 = Mat(3, 3, CV_64FC1);
Mat d135 = Mat(3, 3, CV_64FC1);
Mat vert = Mat(3, 3, CV_64FC1);
Mat horz = Mat(3, 3, CV_64FC1);

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
	createSobels();
	Mat inputIm = imread("opencv-logo-white.png", CV_LOAD_IMAGE_COLOR);
	imshow("RAW", inputIm);
	while (waitKey(10)!='ESC')
	{
		videoCapture >> img;
		
		bool temp =  img.empty();
		Mat output;//CV_32FC1
		cvtColor(img, img, CV_RGB2GRAY);
		img.copyTo(output);
		Gabor test = Gabor(1, 0.5, 0, 8, 0); // the last one is theta
		Mat AllOnes = Mat::ones(3, 3, img.type());
		Mat onemore = Mat(img.size(), test.getFilter().type());
		img.copyTo(onemore);
		Mat gbfilter = test.getFilter();
		pyrDown(gbfilter, gbfilter);
		pyrDown(gbfilter, gbfilter);

		filter2D(onemore / 255, output, img.depth(), gbfilter);
		Mat looking = test.getFilter();
		double t = looking.at<double>(35, 35);
		//normalize(output, output);
		output = output/30;
		output = output *255;
		
		Mat done = Mat(img.size(), img.type());
		output.copyTo(done);
		imshow("RAW", img);
		imshow("Filter", gbfilter);
		imshow("output", done);
		//CvGabor temp1 = CvGabor(0, .25, 2);
		//IplImage ipl_img = img.operator IplImage();
		//IplImage *filtered = &filter.operator IplImage();
		//temp1.conv_img(&ipl_img, filtered, 2);
		//Mat cvmat(filtered);

	
		//imshow("HSV", cvmat);
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

void createSobels(){

	horz.at<double>(0, 0) = 1;
	horz.at<double>(0, 1) = 2;
	horz.at<double>(0, 2) = 1;
	horz.at<double>(1, 0) = 0;
	horz.at<double>(1, 1) = 0;
	horz.at<double>(1, 2) = 0;
	horz.at<double>(2, 0) = -1;
	horz.at<double>(2, 1) = -2;
	horz.at<double>(2, 2) = -1;

	vert.at<double>(0, 0) = 1;
	vert.at<double>(0, 1) = 0;
	vert.at<double>(0, 2) = -1;
	vert.at<double>(1, 0) = 2;
	vert.at<double>(1, 1) = 0;
	vert.at<double>(1, 2) = -2;
	vert.at<double>(2, 0) = 1;
	vert.at<double>(2, 1) = 0;
	vert.at<double>(2, 2) = -1;

	
	d135.at<double>(0, 0) = 2;
	d135.at<double>(0, 1) = 1;
	d135.at<double>(0, 2) = 0;
	d135.at<double>(1, 0) = 1;
	d135.at<double>(1, 1) = 0;
	d135.at<double>(1, 2) = -1;
	d135.at<double>(2, 0) = 0;
	d135.at<double>(2, 1) = -1;
	d135.at<double>(2, 2) = -2;

	//d45.at<double>(0, 0) = 0;
	//d45.at<double>(0, 1) = -1;
	//d45.at<double>(0, 2) = -2;
	//d45.at<double>(1, 0) = 1;
	//d45.at<double>(1, 1) = 0;
	//d45.at<double>(1, 2) = -1;
	//d45.at<double>(2, 0) = 2;
	//d45.at<double>(2, 1) = 1;
	//d45.at<double>(2, 2) = 0;

	d45.at<double>(0, 0) = 1;
	d45.at<double>(0, 1) = 1;
	d45.at<double>(0, 2) = 1;
	d45.at<double>(1, 0) = 1;
	d45.at<double>(1, 1) = 1;
	d45.at<double>(1, 2) = 1;
	d45.at<double>(2, 0) = 1;
	d45.at<double>(2, 1) = 1;
	d45.at<double>(2, 2) = 1;



}