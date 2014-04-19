#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "Features.h"
#include "CvGabor.h"
using namespace cv;
/*
This class contains the orientation features for the gist model.
first the object takes in an image
then it down samples it for 4 layers of resolution
each layer is put through 4 different orientation filters '0 45 90 135' degrees
this is done using either a sobel or Garbor filter
each image then has its features extracted
*/
class Orienation_Channel
{
private:
	static const int depth = 4;
	// these are the filtered images from which features will be extracted
	Mat FeatureMaps0[depth];
	Mat FeatureMaps45[depth];
	Mat FeatureMaps90[depth];
	Mat FeatureMaps135[depth];
	CvGabor filter;
	Mat OriginalImage;
public:
	Features F0;
	Features F45;
	Features F90;
	Features F135;

	Orienation_Channel(); 
	Orienation_Channel(Mat I);
	void Initialize(Mat I);
	Mat* MakePyramid(Mat I, Mat* dst);
	void Make_FeatureMap(Mat *p1, Mat *fMap, Features x);
	void setImage(Mat I);
	Mat* getImage();

	~Orienation_Channel();
};

