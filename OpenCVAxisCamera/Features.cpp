#include "Features.h"


Features::Features()
{
	
}

Features::Features(Mat *FMap, int numElem){
	Initialize( FMap,  numElem);
}

void Features::Initialize(Mat *FMap, int numElem){
	numElements = numElem;
	ExtractedFeatures = new double*[numElem];
	double GistMeans[NumImgDivisions*NumImgDivisions];
	for (int i = 0; i < numElem; i++){
		ExtractedFeatures[i] = subMeans(FMap[i], GistMeans);
	}
	delete[] GistMeans;
}

double* Features::subMeans(Mat src, double GistMeans[]){
	Size s = src.size();
	int stepSizeRow = s.width / NumImgDivisions;
	int stepSizeColumn = s.height / NumImgDivisions;
	// this loop will take the mean of the 16 subsections of the image and place each into an array
	for (int i = 0; i < NumImgDivisions; i++){
		for (int j = 0; j < NumImgDivisions; j++){
			// check for boundary conditions on the high end, 
			int tc = stepSizeColumn*(i + 1);
			int tr = stepSizeRow*(j + 1);
			if (tr >s.height){
				tr = s.height;
			}
			if (tc >s.width){
				tc = s.width;
			}
			Mat E = src(Range(stepSizeColumn*i, stepSizeColumn*(i + 1)), Range(stepSizeRow*j, stepSizeRow*(j + 1)));
			GistMeans[NumImgDivisions*i + j] = mean(E)[0]; // values are returned in a vector the same length as the number of layers

		}

	}

	return GistMeans;
}

double** Features::getExtractedFeatures(){
	return ExtractedFeatures;
}
void Features::setFeatureMap(Mat *FMap,int numElem){
	Initialize(FMap, numElem);
}

Features::~Features()
{
	for (int i = 0; i < numElements; i++){
		delete[] ExtractedFeatures[i];
	}
	delete[] ExtractedFeatures;
	delete FeatureMap;
}
