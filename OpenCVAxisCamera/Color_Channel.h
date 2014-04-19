#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "Features.h"
using namespace cv;
/*
This class contains the color features for the gist model.
first the object takes in an image
then it seperates the image into its color planes and creates the 5 normalized color components
 that are to be worked with, R G B Y I.
 for each of the color components a spatial pyramid is created, and a DoG is performed to create center surrounded features for
 each color of interrest, the colors are chosen using opponancy.
The DoG is done by taking the finner (higher pixel count or larger image size) and subtracting from it the interpolated courser image, this is
what created the LoG look using a DoG. 

c = finner
s = courser

the formula to use is (R(c)-G(c)) - interpolated (R(s)-G(s))
					  (B(c)-Y(c)) - interpolated (B(s)-y(s))
					  (I(c)-I(c)) - interpolated (I(s)-I(s))
*/
class Color_Channel
{
private:
	static const int depth = 8;
	static const int NumFeatureMaps = 6;
	static const int ColorOpponents = 5;
	Mat OriginalImage;
	Mat ColorPlanes[ColorOpponents];
	Mat FeatureMapsRG[depth];
	Mat FeatureMapsBY[depth];
	Mat FeatureMapsI[depth];
	
	
public:

	Features RG;
	Features BY;
	Features Intensity;

	Color_Channel();
	Color_Channel(Mat I);
	void Initialize(Mat I);
	void Make_FeatureMap(Mat *p1, Mat *p2, Mat *fMap, Features x);
	void CreateColorPlanes(); // uses the original image
	Mat* MakePyramid(Mat I, Mat* dst); // will make an spatial pyramid of indicated depth using buildPyramid or somthing like it
	Mat getImage();
	Mat Interpolate(Mat src, Mat dst);
	void setImage(Mat I);
	~Color_Channel();
};

