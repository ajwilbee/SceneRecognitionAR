#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
/*
this filter uses sine waves of different orientations to create an orientation map of an image
http://www.mathworks.com/matlabcentral/fileexchange/23253-gabor-filter
http://en.wikipedia.org/wiki/Gabor_filter
*/
class Gabor
{
private:
	const double pi = 3.14159;
	int bw; // Bandwidth, typically 1
	double gamma; // aspect ratio typically .5
	double psi; // phase shift, typically 0
	double lambda; // wavelength must be >= 2
	double theta; // orientaion angle between 0 and pi
	double params[5];
	Mat Filter;
public:
	Gabor();
	Gabor(int b, double gamm, double ps, double lambd, double thet);
	Mat makegb();
	Mat makeFilter();
	Mat getFilter();
	void setParams(int b, double gamm, double ps, double lambd, double thet);
	Mat linspace(double sval, double endval, int interval);
	Mat apply_Theta(Mat x, Mat y,double co1,double co2); // takes two coefficients and multiplies and sums them for each element
	Mat flip_Mat(Mat x);
	double* getParams();

	~Gabor();
};

