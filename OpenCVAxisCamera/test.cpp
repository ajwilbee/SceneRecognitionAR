#include "opencv/cv.h"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "opencv/highgui.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "Gabor.h"
#include "CvGabor.h"
#include "Color_Channel.h"
#include "Orienation_Channel.h"
#include "Resource.h"
#include "GenAlg.h"
#include "dataanalysis.h"

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
void CreateGistVector(Mat I, double *Allfeatures);
void TrainNN();
void InitializeNN();
void LiveProcessing();
std::vector<NNInputData> readExcelCSV();
const double pi = 3.14159;
Mat d45 = Mat(3, 3, CV_64FC1);
Mat d135 = Mat(3, 3, CV_64FC1);
Mat vert = Mat(3, 3, CV_64FC1);
Mat horz = Mat(3, 3, CV_64FC1);
int NumNeurons = 10;
std::vector <double>  vecWeights;
std::vector <double>  ZeroMean;
int iArrayWidth;
int jTop;
int sigmoidShape = 2;
Mat WPCA;
double normalizationFactor;
Mat img;
FFNeuralNetwork* myNN;
ofstream fileout;
VideoCapture videoCapture;


int main(void)
{
	TrainNN();
	//InitializeNN();
	


	//this will go into 
	
	/*while (waitKey(10) != 'ESC')
	{
		LiveProcessing();*/

		////videoCapture >> img;
		//img = imread("opencv-logo-white.png", CV_LOAD_IMAGE_COLOR);
		//double *p = new double[544];
		//CreateGistVector(img, p);
		////make it zero mean
		//for (int i = 0; i < 544; i++)
		//{
		//	p[i] = p[i] - ZeroMean[i];
		//}
		////make a mat for matrix multiplication
		//Mat SourceData = Mat::zeros(1, 544, CV_32F);
		//for (int j = 0; j < 544; j++)
		//{
		//	SourceData.at<float>(0, j) = p[j];
		//}

		//Mat FinalFeaturesMatrix = SourceData*WPCA;
		//// prep data to be put directly through NN
		//int CV = 0;
		//std::vector<double> holder;
		//for (int j = 0; j < jTop; j++){
		//	holder.push_back(FinalFeaturesMatrix.at<float>(0, j) / normalizationFactor);
		//}

		//NNInputData t(holder, CV);

		////output result
		//vector<double> classification = myNN->Update(t.features);
		//fileout.open("Classification.csv", std::ios::app);
		//fileout << classification[0] << ",";
		//fileout.close();
		//classification.empty();

		//// set up NN
		//imshow("RAW", img);
		//waitKey(0);

	/*}*/


	delete myNN;
	return 0;
}
void InitializeNN(){

	// get the NN best weights
	ifstream file("BestNNWeights.csv");
	string value;

	//wrong number of values are being read in ... find and fix
	double tempdouble = 0.0;
	while (file.good())
	{
		getline(file, value, ','); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
		tempdouble = strtod(value.c_str(), NULL);
		vecWeights.push_back(tempdouble);
		//cout << string(value, 1, value.length() - 2); // display value removing the first and the last character from it
	}
	vecWeights.pop_back();
	file.close();

	//make the zero means vector
	file.open("ZeroMeanValues.csv");

	tempdouble = 0.0;
	while (file.good())
	{
		getline(file, value, ','); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
		tempdouble = strtod(value.c_str(), NULL);
		ZeroMean.push_back(tempdouble);
		//cout << string(value, 1, value.length() - 2); // display value removing the first and the last character from it
	}
	ZeroMean.pop_back();
	file.close();

	// make WPCA width and height

	file.open("WPCARowandColumn.csv");
	tempdouble = 0.0;
	getline(file, value, ','); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
	iArrayWidth = atoi(value.c_str());
	getline(file, value, ','); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
	jTop = atoi(value.c_str());
	file.close();

	//make WPCA
	WPCA = Mat::zeros(iArrayWidth, jTop, CV_32F);
	file.open("WPCAVals.csv");
	for (int i = 0; i < iArrayWidth; i++)
	{

		for (int j = 0; j < jTop; j++)
		{
			getline(file, value, ',');
			tempdouble = strtod(value.c_str(), NULL);
			WPCA.at<float>(i, j) = tempdouble;

		}

		//each element in WPCA is a row of the WPCA Matrix
	}
	file.close();

	// get normalization constant
	file.open("NormalizationConstant.csv");
	getline(file, value, ',');
	normalizationFactor = strtod(value.c_str(), NULL);;
	file.close();
	// now make the NN and process a single image

	videoCapture.open("http://axis2.student.rit.edu/mjpg/video.mjpg"); //http://axis1.student.rit.edu/mjpg/video.mjpg
	cvWaitKey(5000);
	if (!videoCapture.isOpened()){

		int temp = 1;
	}
	// set up NN
	//JTop is the number of inputs, should make the rest of initial values constants somewhere
	myNN = new FFNeuralNetwork((int)(jTop), 1, 1, NumNeurons, -1, sigmoidShape);
	myNN->PutWeights(vecWeights);
}

void LiveProcessing(){
	
	//swap these to swithc between live and not
	//videoCapture >> img;
	img = imread("opencv-logo-white.png", CV_LOAD_IMAGE_COLOR);


	double *p = new double[544];
	CreateGistVector(img, p);
	//make it zero mean
	for (int i = 0; i < 544; i++)
	{
		p[i] = p[i] - ZeroMean[i];
	}
	//make a mat for matrix multiplication
	Mat SourceData = Mat::zeros(1, 544, CV_32F);
	for (int j = 0; j < 544; j++)
	{
		SourceData.at<float>(0, j) = p[j];
	}

	Mat FinalFeaturesMatrix = SourceData*WPCA;
	// prep data to be put directly through NN
	int CV = 0;
	std::vector<double> holder;
	for (int j = 0; j < jTop; j++){
		holder.push_back(FinalFeaturesMatrix.at<float>(0, j) / normalizationFactor);
	}

	NNInputData t(holder, CV);

	//output result
	vector<double> classification = myNN->Update(t.features);
	fileout.open("Live_Classification.csv", std::ios::app);
	fileout << classification[0] << ",";
	fileout.close();
	classification.empty();

	// set up NN
	imshow("RAW", img);
	waitKey(0);
}

void TrainNN(){

	// can make this a function if sure that can pass the vector around without it breaking, try tommorrow if you want
	// could also make it a loop if the directories are put into a string array.
	vector<double*> AllImageFeatures;
	double numberOfImagesInDirectory[2];

	WIN32_FIND_DATA FindFileData;

	HANDLE hFind;
	ofstream featurewrite;
	featurewrite.open("p.csv", ios::app);
	int counter = 0;

	string path1 = "C:\\Users\\Aaron\\Documents\\AdvancedRoboticsFP\\Images\\corridor_indoor_set2_256x256_static\\";//\Aaron\Documents\Visual Studio 2013\Projects\OpenCVAxisCamera\OpenCVAxisCamera
	string path2 = "C:\\Users\\Aaron\\Documents\\AdvancedRoboticsFP\\Images\\corridor_indoor_set2_256x256_static\\";
	hFind = FindFirstFile(path1.append("*.jpg").c_str(), &FindFileData);
	while (hFind != INVALID_HANDLE_VALUE){
		path2 = "C:\\Users\\Aaron\\Documents\\AdvancedRoboticsFP\\Images\\corridor_indoor_set2_256x256_static\\";
		cout << FindFileData.cFileName;
		Mat inputIm = imread(path2.append(FindFileData.cFileName), CV_LOAD_IMAGE_COLOR);
		double *p = new double[544];
		CreateGistVector(inputIm, p);

		featurewrite << "\n";
		for (int i = 0; i < 544; i++){
			featurewrite << p[i];
			featurewrite << ",";
		}



		//double x = p[10];
		AllImageFeatures.push_back(p);
		counter++;
		if (!FindNextFile(hFind, &FindFileData))
		{
			FindClose(hFind);
			hFind = INVALID_HANDLE_VALUE;
		}
	}
	featurewrite.close();

	numberOfImagesInDirectory[0] = counter;
	counter = 0;
	cout << "\n";
	//
	path1 = "C:\\Users\\Aaron\\Documents\\AdvancedRoboticsFP\\Images\\bathroom_indoor_256x256_static\\";//\Aaron\Documents\Visual Studio 2013\Projects\OpenCVAxisCamera\OpenCVAxisCamera
	path2 = "C:\\Users\\Aaron\\Documents\\AdvancedRoboticsFP\\Images\\bathroom_indoor_256x256_static\\";
	hFind = FindFirstFile(path1.append("*.jpg").c_str(), &FindFileData);

	while (hFind != INVALID_HANDLE_VALUE){
		path2 = "C:\\Users\\Aaron\\Documents\\AdvancedRoboticsFP\\Images\\bathroom_indoor_256x256_static\\";
		cout << FindFileData.cFileName;
		Mat inputIm = imread(path2.append(FindFileData.cFileName), CV_LOAD_IMAGE_COLOR);
		double *p = new double[544];
		CreateGistVector(inputIm, p);



		AllImageFeatures.push_back(p);
		counter++;
		if (!FindNextFile(hFind, &FindFileData))
		{
			FindClose(hFind);
			hFind = INVALID_HANDLE_VALUE;
		}
	}


	numberOfImagesInDirectory[1] = counter;
	counter = 0;

	real_2d_array PCAarray; http://forum.alglib.net/viewtopic.php?f=2&t=60

	int iArrayHeight = AllImageFeatures.size();
	int iArrayWidth = (64) * 4 + (96) * 3;
	double createZeroMean[(64) * 4 + (96) * 3] = { 0.0 };
	//p = AllImageFeatures[0];
	PCAarray.setlength(iArrayHeight, iArrayWidth);//height is the number of points, width is the number of variables per point
	ofstream myfile;
	myfile.open("example.csv");
	for (int i = 0; i < iArrayHeight; i++)
	{
		for (int j = 0; j < iArrayWidth; j++)
		{
			PCAarray(i, j) = AllImageFeatures[i][j];
			myfile << AllImageFeatures[i][j];
			myfile << ",";
			createZeroMean[j] = createZeroMean[j] + AllImageFeatures[i][j];
		}
		myfile << "\n";
	}
	myfile.close();
	//find the offset to make it zero mean
	myfile.open("ZeroMeanValues.csv");

	for (int j = 0; j < iArrayWidth; j++){

		createZeroMean[j] = createZeroMean[j] / iArrayHeight;
		myfile << createZeroMean[j];
		myfile << ",";
	}
	// make the array zero mean
	for (int i = 0; i < iArrayHeight; i++)
	{
		for (int j = 0; j < iArrayWidth; j++)
		{
			PCAarray(i, j) = PCAarray(i, j) - createZeroMean[j];
		}
	}

	ae_int_t npoints = iArrayHeight;
	ae_int_t nvars = iArrayWidth;
	ae_int_t info;
	double* tester;
	double value = 0;
	double percentInfo = 0;
	double AcceptablePercent = 0.95;
	real_1d_array s2;//array[0..NVars-1]. variance values corresponding to basis vectors. sigmas (eigne values)
	real_2d_array v;// array[0..NVars - 1, 0..NVars - 1] matrix, whose columns store basis vectors. Wcpa, must keep only top 90percent based on sum of sigmas

	pcabuildbasis(PCAarray, npoints, nvars, info, s2, v);
	double sum = s2[0];
	tester = s2.getcontent();
	for (int i = 0; i < s2.length(); i++){
		value = value + tester[i];
	}
	int iTop = 0;
	while ((percentInfo / value) < AcceptablePercent){
		percentInfo = percentInfo + tester[iTop];
		iTop++;
	}

	int jTop = 0;
	double Val = 2;
	while (tester[jTop] > 1){
		Val = tester[jTop];
		jTop++;
	}
	//convert to matrix to do the multiplication to achieve the final feature set
	ofstream WPCAVals;
	WPCAVals.open("WPCARowandColumn.csv");
	WPCAVals << iArrayWidth;
	WPCAVals << ",";
	WPCAVals << jTop;
	WPCAVals.close();

	WPCAVals.open("WPCAVals.csv");


	Mat WPCA = Mat::zeros(iArrayWidth, jTop, CV_32F);
	for (int i = 0; i < iArrayWidth; i++)
	{

		for (int j = 0; j < jTop; j++)
		{
			WPCA.at<float>(i, j) = (v(i, j));
			WPCAVals << (v(i, j));
			WPCAVals << ",";
		}
		WPCAVals << "\n";
		//each element in WPCA is a row of the WPCA Matrix
	}
	WPCAVals.close();
	Mat SourceData = Mat::zeros(iArrayHeight, iArrayWidth, CV_32F);
	for (int i = 0; i < iArrayHeight; i++)
	{
		for (int j = 0; j < iArrayWidth; j++)
		{
			SourceData.at<float>(i, j) = AllImageFeatures[i][j] - createZeroMean[j];

		}
	}
	ofstream fileWriter;
	fileWriter.open("NNInput.csv", ios::app);
	Mat FinalFeaturesMatrix = SourceData*WPCA;

	double minVal;
	double maxVal;
	Point minLoc;
	Point maxLoc;
	minMaxLoc(FinalFeaturesMatrix, &minVal, &maxVal, &minLoc, &maxLoc);
	WPCAVals.open("NormalizationConstant");
	cout << "min val : " << minVal << endl;
	cout << "max val: " << maxVal << endl;
	double normalizationFactor;
	if (abs(minVal) > abs(maxVal)){
		normalizationFactor = abs(minVal);

	}
	else{
		normalizationFactor = abs(minVal);

	}

	WPCAVals.open("NormalizationConstant.csv");
	WPCAVals << normalizationFactor;
	WPCAVals.close();

	vector<NNInputData> ReadyForNN;
	int CV = 0;
	int startingIndex = 0;
	int endingIndex = 0;
	for (int z = 0; z < 2; z++){
		startingIndex = endingIndex;
		endingIndex = endingIndex + numberOfImagesInDirectory[z];
		for (int i = startingIndex; i < endingIndex; i++){
			std::vector<double> holder;
			CV = z;
			for (int j = 0; j < jTop; j++){
				holder.push_back(FinalFeaturesMatrix.at<float>(i, j) / normalizationFactor);
				fileWriter << FinalFeaturesMatrix.at<float>(i, j) / normalizationFactor;
				fileWriter << ",";
			}
			fileWriter << CV;
			NNInputData t(holder, CV);
			fileWriter << "\n";
			ReadyForNN.push_back(t);
			
		}
	}
	fileWriter.close();
	int numIter = 10;
	double inputsize = ReadyForNN[0].features.size();
	//may want to make the NN values constants defined somewhere eventually
	FFNeuralNetwork* myNN = new FFNeuralNetwork((int)(inputsize), 1, 1, NumNeurons, -1, sigmoidShape);
	GenAlg* MyEarth = new GenAlg(100, .05, .5, myNN, ReadyForNN);
	std::vector<SGenome> currentpopulation = MyEarth->GetChromos();
	for (int i = 0; i < numIter; i++){
		if (i < numIter / 5){
			MyEarth->Epoch(currentpopulation,0);
		}
		else{
			MyEarth->Epoch(currentpopulation,1);
		}
		std::vector<SGenome> temp = MyEarth->GetChromos();
		std::vector<SGenome> currentpopulation = MyEarth->GetChromos();
		cout << "\n" <<MyEarth->BestFitness();
		cout << "\n";
		fileWriter.open("Classifications.csv");
		fileWriter << "";
	}
	MyEarth->writeBestWeights();

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


void CreateGistVector(Mat I, double *AllFeatures){
	Mat copyI;
	I.copyTo(copyI);
	/*real_2d_array PCAarray; http://forum.alglib.net/viewtopic.php?f=2&t=60
	PCAarray;
	pcabuildbasis(const real_2d_array &x, const ae_int_t npoints, const ae_int_t nvars, ae_int_t &info, real_1d_array &s2, real_2d_array &v);*/
	Orienation_Channel OC = Orienation_Channel(I);
	Color_Channel CC = Color_Channel(copyI);
	
	//double AllFeatures[(64) * 4 + (96) * 3];
	int counter = 0;
	for (int i = 0; i < 64; i++){
		AllFeatures[counter] = OC.F0.ExtractedFeatures[i];
		counter++;
	}
	for (int i = 0; i < 64; i++){
		AllFeatures[counter] = OC.F45.ExtractedFeatures[i];
		counter++;
	}
	for (int i = 0; i < 64; i++){
		AllFeatures[counter] = OC.F90.ExtractedFeatures[i];
		counter++;
	}
	for (int i = 0; i < 64; i++){
		AllFeatures[counter] = OC.F135.ExtractedFeatures[i];
		counter++;
	}
	for (int i = 0; i < 96; i++){
		AllFeatures[counter] = CC.BY.ExtractedFeatures[i];
		counter++;
	}
	for (int i = 0; i < 96; i++){
		AllFeatures[counter] = CC.RG.ExtractedFeatures[i];
		counter++;
	}
	for (int i = 0; i < 96; i++){
		AllFeatures[counter] = CC.Intensity.ExtractedFeatures[i];
		counter++;
	}

	ofstream featurewrite;
	featurewrite.open("AllFeatures.csv", ios::app);
		featurewrite << "\n";
	for (int i = 0; i < 544; i++){
		featurewrite << AllFeatures[i];
		featurewrite << ",";
	}

	featurewrite.close();
	//return AllFeatures;
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


//Mat output;//CV_32FC1
//cvtColor(img, img, CV_RGB2GRAY);
//img.copyTo(output);
//Gabor test = Gabor(1, 0.5, 0, 8, 0); // the last one is theta
//Mat AllOnes = Mat::ones(3, 3, img.type());
//Mat onemore = Mat(img.size(), test.getFilter().type());
//img.copyTo(onemore);
//Mat gbfilter = test.getFilter();
//pyrDown(gbfilter, gbfilter);
//pyrDown(gbfilter, gbfilter);
//
//filter2D(onemore / 255, output, img.depth(), gbfilter);
//Mat looking = test.getFilter();
//double t = looking.at<double>(35, 35);
////normalize(output, output);
//output = output / 30;
//output = output * 255;
//
//Mat done = Mat(img.size(), img.type());
//output.copyTo(done);






//if (!inputIm.data)                              // Check for invalid input
//{
//	cout << "Could not open or find the image" << std::endl;
//	return -1;
//}
/*namedWindow("RAW", 1);
imshow("RAW", inputIm);*/

/*createSobels();
Mat output;

filter2D(inputIm, output, inputIm.depth(), d45);
imshow("filtered", output);
waitKey(0);*/




//	cout << "\n";
//	//
//	path1 = "C:\\Users\\Aaron\\Documents\\AdvancedRoboticsFP\\Images\\corridor_indoor_set2_256x256_static\\";//\Aaron\Documents\Visual Studio 2013\Projects\OpenCVAxisCamera\OpenCVAxisCamera
//	path2 = "C:\\Users\\Aaron\\Documents\\AdvancedRoboticsFP\\Images\\corridor_indoor_set2_256x256_static\\";
//	hFind = FindFirstFile(path1.append("*.jpg").c_str(), &FindFileData);
//	while (hFind != INVALID_HANDLE_VALUE){
//		path2 = "C:\\Users\\Aaron\\Documents\\AdvancedRoboticsFP\\Images\\corridor_indoor_set2_256x256_static\\";
//		cout << FindFileData.cFileName;
//		Mat inputIm = imread(path2.append(FindFileData.cFileName), CV_LOAD_IMAGE_COLOR);
//
//		double *p = new double[544];
//		CreateGistVector(inputIm, p);
//		AllImageFeatures.push_back(p);
//
//		if (!FindNextFile(hFind, &FindFileData))
//		{
//			FindClose(hFind);
//			hFind = INVALID_HANDLE_VALUE;
//		}
//	}
//	numberOfImagesInDirectory[2] = counter;
//	counter = 0;
//	cout << "\n";
////
//	path1 = "C:\\Users\\Aaron\\Documents\\AdvancedRoboticsFP\\Images\\livingroom_indoor_256x256_static\\";//\Aaron\Documents\Visual Studio 2013\Projects\OpenCVAxisCamera\OpenCVAxisCamera
//	path2 = "C:\\Users\\Aaron\\Documents\\AdvancedRoboticsFP\\Images\\livingroom_indoor_256x256_static\\";
//	hFind = FindFirstFile(path1.append("*.jpg").c_str(), &FindFileData);
//	while (hFind != INVALID_HANDLE_VALUE){
//		path2 = "C:\\Users\\Aaron\\Documents\\AdvancedRoboticsFP\\Images\\livingroom_indoor_256x256_static\\";
//		cout << FindFileData.cFileName;
//		Mat inputIm = imread(path2.append(FindFileData.cFileName), CV_LOAD_IMAGE_COLOR);
//		//imshow("filtered", inputIm);
//		//waitKey(0);
//		double *p = new double[544];
//		CreateGistVector(inputIm, p);
//		AllImageFeatures.push_back(p);
//
//		if (!FindNextFile(hFind, &FindFileData))
//		{
//			FindClose(hFind);
//			hFind = INVALID_HANDLE_VALUE;
//		}
//	}
//	numberOfImagesInDirectory[3] = counter;
//	counter = 0;



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
