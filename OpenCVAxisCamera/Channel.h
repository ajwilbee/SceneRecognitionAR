#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class Channel
{
private:
	static const int depth = 8;
	Mat OriginalImage;
	Mat FilteredFeatures[depth];
public:
	Channel();
	Channel(Mat I);
	Mat* MakePyramid(Mat I); // will make an spatial pyramid of indicated depth using buildPyramid or somthing like it
	Mat getImage();
	Mat* getPyramid();
	void setImage(Mat I);
	~Channel();
};