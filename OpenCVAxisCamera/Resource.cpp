#include "Resource.h"

// constructors go here if a variable is created, otehrwise compilation issues
SNeuron::SNeuron(int NumInputs) : m_NumInputs(NumInputs + 1)

{

	//we need an additional weight for the bias hence the +1

	for (int i = 0; i<NumInputs + 1; ++i)

	{

		//set up the weights with an initial random value
		double temp = (rand() % 100) / 100;
		m_vecWeight.push_back(temp);

	}

}
SNeuronLayer::SNeuronLayer(int NumNeurons, int NumInputsPerNeuron) : m_NumNeurons(NumNeurons)
{
	for (int i = 0; i<NumNeurons; ++i)

	{

		//set up Layer with all neurons with random weighting

		m_vecNeurons.push_back(SNeuron(NumInputsPerNeuron));

	}

}

ColorFeature::ColorFeature(Mat *FMap){
	static const int NumImgDivisions = 4;
	static const int numElem = 6;
	ExtractedFeatures = new double[NumImgDivisions*NumImgDivisions * numElem];
	double ExtractedFeatures[NumImgDivisions*NumImgDivisions * numElem]; // definate array needs no delete
	Size s = FMap[0].size();
	Mat Image;
	int stepSizeRow = s.width / NumImgDivisions;
	int stepSizeColumn = s.height / NumImgDivisions;
	int counter = 0;
	// this loop will take the mean of the 16 subsections of the image and place each into an array
	for (int k = 0; k < numElem; k++){
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

ColorFeature::ColorFeature(){}

OrientationFeature::OrientationFeature(Mat *FMap){
	static const int NumImgDivisions = 4;
	static const int numElem = 4;
	ExtractedFeatures = new double[NumImgDivisions*NumImgDivisions * numElem];
	double ExtractedFeatures[NumImgDivisions*NumImgDivisions * numElem]; // definate array needs no delete
	Size s = FMap[0].size();
	Mat Image;
	int stepSizeRow = s.width / NumImgDivisions;
	int stepSizeColumn = s.height / NumImgDivisions;
	int counter = 0;
	// this loop will take the mean of the 16 subsections of the image and place each into an array
	for (int k = 0; k < numElem; k++){
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
OrientationFeature::OrientationFeature(){

}

Resource::Resource()
{
}


Resource::~Resource()
{
}
