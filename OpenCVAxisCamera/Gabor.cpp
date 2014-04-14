#include "Gabor.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;

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
	double spacing = abs(endval - sval + 1);
	double temp = 0;
	Mat y(spacing, spacing, CV_64FC1); // creates a row that is linearly spaced
	for (int i = 0; i < y.cols; ++i)
	{
		for (int j = 0; j < y.cols; ++j){
			y.at<double>(j, i) = ceil(sval + j*(endval - sval) / spacing);
			//cout << y.at<double>(j, i);
		}
		//cout << endl; 
	}
	//namedWindow("RAW", 1);
	//imshow("RAW",y);
	return y;
}

Mat Gabor::apply_Theta(Mat x, Mat y,double co1, double co2){

	Size s = x.size();
	Mat theta;
	x.copyTo(theta);
	double temp;
	cout << "this change is in the test branch";
	cout << s.height;
	cout << s.width;
	for (int i = 0; i < s.height; ++i){

		for (int j = 0; j < s.width; ++j){
			cout << x.at<double>(i, j);
			//co1 + y.at<double>(i, j)*co2;
			//theta.at<doubleb>(i,j) = temp;
			cout << j;
			cout << endl;
		}
		cout << "new row";
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
	Mat y = linspace(floor(sz / 2), -floor(sz / 2), 1);
	Mat x_theta = apply_Theta(x, y, cos(theta), sin(theta));
	Mat y_theta = apply_Theta(x, y, -sin(theta), cos(theta));


	/*[x y] = meshgrid(-floor(sz / 2) :floor(sz / 2), floor(sz / 2) : -1 : floor(-sz / 2));*/

	//x_theta = x*cos(theta) + y*sin(theta);
	//y_theta = -x*sin(theta) + y*cos(theta);

	//Mat gb = exp(-0.5*(x_theta. ^ 2 / sigma_x ^ 2 + y_theta. ^ 2 / sigma_y ^ 2)).*cos(2 * pi / lambda*x_theta + psi);

	return Filter;
}
Mat Gabor::makeFilter(){
	Filter = makegb();
	return Filter;
}

Mat Gabor::getFilter(){
	return Filter;
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
