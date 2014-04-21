#include "Gabor.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
int params[5];
Mat Filter;

Gabor::Gabor()
{
}

Gabor::Gabor(int b, double gamm, double ps, double lambd, double thet)
{

	
	setParams(b, gamm, ps, lambd, thet);
	makeFilter();
}

Mat Gabor::linspace(double sval, double endval, int interval)
{
	double spacing = abs(endval - sval) +1;
	double temp = 0;
	Mat y(spacing, spacing, CV_64FC1); // creates a row that is linearly spaced
	for (int i = 0; i < y.cols; ++i)
	{
		for (int j = 0; j < y.cols; ++j){
			double temp  = sval + j*(endval - sval) / spacing;
			y.at<double>(j, i) = ceil(sval + j*(endval - sval) / spacing);
			

		}
		//cout << endl; 
	}
	//namedWindow("RAW", 1);
	//imshow("RAW",y);
	return y;
}

Mat Gabor::apply_Theta(Mat x, Mat y,double co1, double co2){

	Size s = x.size();
	Size sy = y.size();
	Mat theta;
	x.copyTo(theta);
	double temp;
	for (int i = 0; i < s.height; ++i){

		for (int j = 0; j < s.width; ++j){
			theta.at<double>(i, j) = x.at<double>(j, i)*co1 + y.at<double>(i, j)*co2;
		}

	}
	return theta;
}

Mat Gabor::makegb(){
	double sigma = lambda / pi*sqrt(log(2) / 2)*(pow(2, bw) + 1) / (pow(2 , bw) - 1);
	double sigma_x = sigma;
	double sigma_y = sigma / gamma;
	int sz = floor(8 * max(sigma_y, sigma_x));
	if ((sz % 2) == 0){
		sz = sz + 1;
	}
	Mat x = linspace(-floor(sz / 2), floor(sz / 2), 1);
	Mat y = flip_Mat(x);
	
	
	Mat x_theta = apply_Theta(x, y, cos(theta), sin(theta));
	Mat y_theta = apply_Theta(x, y, -sin(theta), cos(theta));

	Size s = x_theta.size();
	Mat gaborMask(s, CV_64FC1);
	double sx2 = pow(sigma_x, 2);
	double sy2 = pow(sigma_y, 2);
	double pi = 3.14159;
	for (int i = 0; i < s.height; i++)
	{
		for (int j = 0; j < s.height; j++){
			double tx = pow(x_theta.at<double>(j, i), 2);
			double ty = pow(y_theta.at<double>(j, i), 2);
			double arg = -0.5*(tx / sx2 + ty / sy2)*cos((2 * pi / (lambda*x_theta.at<double>(j, i)+.00000001) + psi));
			
			gaborMask.at<double>(j, i) = exp(arg);
			if (exp(arg) > 1){
				gaborMask.at<double>(j, i) = 1;

			}
			if (j == 35 && i == 35){
				int x = 0;
			}
		}

	}
	//Mat gb = exp(-0.5*(x_theta. ^ 2 / sigma_x ^ 2 + y_theta. ^ 2 / sigma_y ^ 2)).*cos(2 * pi / lambda*x_theta + psi);

	return gaborMask;
}
Mat Gabor::makeFilter(){
	Filter = makegb();

	return Filter;
}

Mat Gabor::getFilter(){
	return Filter;
}

Mat Gabor::flip_Mat(Mat x){
	Size s = x.size();
	Mat y(s.width, s.width, CV_64FC1);

	for (int i = 0; i < s.height; i++)
	{
		for (int j = 0; j < s.height; j++){
			y.at<double>(j, i) = 0 - x.at<double>(j, i);
		}
	}
	return y;
}

void Gabor::setParams(int b, double gamm, double ps, double lambd, double thet){
	bw = b; // Bandwidth, typically 1
	gamma = gamm; // aspect ratio typically .5
	psi = ps; // phase shift, typically 0
	lambda = lambd; // wavelength must be >= 2
	theta = thet; // orientaion angle between 0 and pi
	
	params[0] = bw ;
	params[1] = gamma;
	params[2] = psi;
	params[3] = lambda;
	params[4] = theta;
}
double* Gabor::getParams(){
	return params;
}


Gabor::~Gabor()
{
}
