#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

class Features
{
private:
	static const int NumImgDivisions = 4;
	double **ExtractedFeatures;
	int numElements;
	Mat *FeatureMap;
public:
	Features();
	void Initialize(Mat *FMap, int numElem);
	Features(Mat *FeatureMap, int numElem);
	double** getExtractedFeatures();
	void setFeatureMap(Mat *FMap, int numElem);
	double* subMeans(Mat src, double GistMeans[]);
	~Features();
};

