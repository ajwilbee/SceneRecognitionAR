#include "opencv/cv.h"
#include <opencv2/core/core.hpp>
#include "opencv/highgui.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "Gabor.h"
#include "CvGabor.h"
#include "Color_Channel.h"
#include "Orienation_Channel.h"
#include "Resource.h"
#include "GenAlg.h"
#include "dataanalysis.h"
#include <iostream>
#include <fstream>
#include "ap.h"
#include "alglibinternal.h"
#include "linalg.h"
#include "statistics.h"
#include "alglibmisc.h"
#include "specialfunctions.h"
#include "solvers.h"
#include "optimization.h"
#include "ap.h"
#include "alglibinternal.h"
#include "linalg.h"
#include "statistics.h"
#include "alglibmisc.h"
#include "specialfunctions.h"
#include "solvers.h"
#include "optimization.h"
using namespace std;
using namespace alglib;
using namespace cv;



void createSobels();
void CreateGistVector(Mat I);
std::vector<NNInputData> readExcelCSV();
const double pi = 3.14159;
Mat d45 = Mat(3, 3, CV_64FC1);
Mat d135 = Mat(3, 3, CV_64FC1);
Mat vert = Mat(3, 3, CV_64FC1);
Mat horz = Mat(3, 3, CV_64FC1);



int main(void)
{
	Mat inputIm = imread("opencv-logo-white.png", CV_LOAD_IMAGE_COLOR);
	CreateGistVector(inputIm);

	int numIter = 100;
	//this is the input data from the cancer study
	/*std::vector<NNInputData> inData = readExcelCSV();
	double inputsize = inData[0].features.size();
	FFNeuralNetwork* myNN = new FFNeuralNetwork((int)(inputsize), 1, 1, 10, -1, 1);
	GenAlg* MyEarth = new GenAlg(10, .05,.5, myNN, inData);
	std::vector<SGenome> currentpopulation = MyEarth->GetChromos();
	for (int i = 0; i < numIter; i++){
		MyEarth->Epoch(currentpopulation);
		std::vector<SGenome> temp = MyEarth->GetChromos();
		std::vector<SGenome> currentpopulation = MyEarth->GetChromos();
		cout << MyEarth->BestFitness()/inData.size();
		cout << "\n";
	}*/


	// image processing testing

	//VideoCapture videoCapture("http://axis2.student.rit.edu/mjpg/video.mjpg"); //http://axis1.student.rit.edu/mjpg/video.mjpg
	//cvWaitKey(5000);

	//if (!videoCapture.isOpened()){

	//	int temp = 1;
	//}
	//Mat img;
	//Mat hsv;
	
	//if (!inputIm.data)                              // Check for invalid input
	//{
	//	cout << "Could not open or find the image" << std::endl;
	//	return -1;
	//}
	//namedWindow("RAW", 1);
	//imshow("RAW", inputIm);
	//
	//createSobels();
	//Mat output;
	//
	//filter2D(inputIm, output, inputIm.depth(), d45);
	//imshow("filtered", output);
	//waitKey(0);

	//while (waitKey(10)!='ESC')
	//{
	//	videoCapture >> img;
	//	
	//	bool temp =  img.empty();
	//	Mat output;//CV_32FC1
	//	cvtColor(img, img, CV_RGB2GRAY);
	//	img.copyTo(output);
	//	Gabor test = Gabor(1, 0.5, 0, 8, 0); // the last one is theta
	//	Mat AllOnes = Mat::ones(3, 3, img.type());
	//	Mat onemore = Mat(img.size(), test.getFilter().type());
	//	img.copyTo(onemore);
	//	Mat gbfilter = test.getFilter();
	//	pyrDown(gbfilter, gbfilter);
	//	pyrDown(gbfilter, gbfilter);

	//	filter2D(onemore / 255, output, img.depth(), gbfilter);
	//	Mat looking = test.getFilter();
	//	double t = looking.at<double>(35, 35);
	//	//normalize(output, output);
	//	output = output/30;
	//	output = output *255;
	//	
	//	Mat done = Mat(img.size(), img.type());
	//	output.copyTo(done);
	//	imshow("RAW", img);
	//	imshow("Filter", gbfilter);
	//	imshow("output", done);


	//garbor testing
		//CvGabor temp1 = CvGabor(0, .25, 2);
		//IplImage ipl_img = img.operator IplImage();
		//IplImage *filtered = &filter.operator IplImage();
		//temp1.conv_img(&ipl_img, filtered, 2);
		//Mat cvmat(filtered);

	
		//imshow("HSV", cvmat);
	//}

	

	
}

//imput data from an excell csv file, currently reading a CSV file
std::vector<NNInputData> readExcelCSV(){
	std::vector<NNInputData> temp;
	std::ifstream test("Hw2CancerData.csv"); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
	string value;
	int entry = 0;
	while (test.good())
	{

		getline(test, value, '\n'); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
		cout << entry;
		cout << "\n";
		std::istringstream ss(value);
		string token;
		std::vector<double> holder;
		int counter = 0;
		while (std::getline(ss, token, ','))
		{
			if (counter >= 1){
				holder.push_back(atof(token.c_str()));
			}
			counter++;
		}
		if (entry == 683){
			int q = 1;
		}
		int p = holder.size();
		if (p != 0){
			int CV = holder[p - 1];
			if (CV == 4){
				CV = 1;
			}
			else{
				CV = 0;
			}
			holder.pop_back();
			NNInputData t(holder, CV);
			temp.push_back(t);
		}
		entry++;
	}


	test.close();
	return temp;
}


void CreateGistVector(Mat I){
	Mat copyI;
	I.copyTo(copyI);
	/*real_2d_array PCAarray;
	PCAarray;
	pcabuildbasis(const real_2d_array &x, const ae_int_t npoints, const ae_int_t nvars, ae_int_t &info, real_1d_array &s2, real_2d_array &v);*/
	Orienation_Channel OC = Orienation_Channel(I);
	Color_Channel CC = Color_Channel(copyI);
	
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

	d45.at<double>(0, 0) = 0;
	d45.at<double>(0, 1) = -1;
	d45.at<double>(0, 2) = -2;
	d45.at<double>(1, 0) = 1;
	d45.at<double>(1, 1) = 0;
	d45.at<double>(1, 2) = -1;
	d45.at<double>(2, 0) = 2;
	d45.at<double>(2, 1) = 1;
	d45.at<double>(2, 2) = 0;

	//d45.at<double>(0, 0) = 1;
	//d45.at<double>(0, 1) = 1;
	//d45.at<double>(0, 2) = 1;
	//d45.at<double>(1, 0) = 1;
	//d45.at<double>(1, 1) = 1;
	//d45.at<double>(1, 2) = 1;
	//d45.at<double>(2, 0) = 1;
	//d45.at<double>(2, 1) = 1;
	//d45.at<double>(2, 2) = 1;



}