#pragma once
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
struct SGenome
{
	std::vector <double>  vecWeights;
	double dFitness;
	SGenome() :dFitness(0){}
	SGenome(std::vector <double> w, double f) : vecWeights(w), dFitness(f){}
	//overload '<' used for sorting
	friend bool operator<(const SGenome& lhs, const SGenome& rhs)
	{
		return (lhs.dFitness < rhs.dFitness);
	}
};

struct SNeuron
{

	//the number of inputs into the neuron

	int m_NumInputs;

	//the weights for each input

	std::vector<double> m_vecWeight;

	//constructor

	SNeuron(int NumInputs);

};


struct SNeuronLayer
{

	//the number of neurons in this layer

	int m_NumNeurons;

	//the layer of neurons

	std::vector<SNeuron> m_vecNeurons;

	//constructor
	SNeuronLayer(int NumNeurons, int NumInputsPerNeuron);

};

struct NNInputData
{
	int CorrectDiagnosis;
	std::vector<double> features;
	NNInputData(std::vector<double> f, int c) :CorrectDiagnosis(c), features(f){}
	NNInputData();
};

struct ColorFeature
{
	
	double *ExtractedFeatures;
	ColorFeature(Mat *FMap);
	ColorFeature();
};

struct OrientationFeature
{

	double *ExtractedFeatures;
	OrientationFeature(Mat *FMap);
	OrientationFeature();
};

class Resource
{
public:
	Resource();
	~Resource();
};

