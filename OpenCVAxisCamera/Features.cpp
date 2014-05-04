#include "Features.h"



Features::Features()
{
	
}

Features::Features(Mat *FMap, int numElem){
	Initialize( FMap,  numElem);
}

void Features::Initialize(Mat *FMap, int numElem){
	numElements = numElem;
	ExtractedFeatures = new double[NumImgDivisions*NumImgDivisions * 6];
	double ExtractedFeatures[NumImgDivisions*NumImgDivisions*6]; // definate array needs no delete
	Size s = FMap[0].size();
	Mat Image;
	int stepSizeRow = s.width / NumImgDivisions;
	int stepSizeColumn = s.height / NumImgDivisions;
	int counter = 0;
	// this loop will take the mean of the 16 subsections of the image and place each into an array
	for (int k = 0; k < numElements; k++){
		Image = FMap[k];
		s = Image.size();
		stepSizeRow = s.width / NumImgDivisions;
		stepSizeColumn = s.height / NumImgDivisions;
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
				Mat E = FMap[k](Range(stepSizeColumn*i, tc), Range(stepSizeRow*j, tr));
				ExtractedFeatures[counter] = mean(E)[0]; // values are returned in a vector the same length as the number of layers
				counter++; 
				E.release();
			}

		}
		Image.release();
	}

}

double* Features::subMeans(Mat *FMap, double ExtractedFeatures[]){
	

	return ExtractedFeatures;
}

double* Features::getExtractedFeatures(){
	return ExtractedFeatures;
}
void Features::setFeatureMap(Mat *FMap,int numElem){
	Initialize(FMap, numElem);
}

Features::~Features()
{

	delete[] ExtractedFeatures;
	delete FeatureMap;
}
