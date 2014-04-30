#pragma once
#define e 2.71828183
#include "Resource.h"

/*
code used and modified from
http://www.ai-junkie.com/ann/evolved/nnt6.html
*/





// the neural network must output a single value corrisponding to the class
// that means the regardless of the number of output nodes the network must have
// an overloaded method to translate the truth table into its proper class
// the GA will only be able to handle a vector of doubles
class FFNeuralNetwork
{
	

	

private:

	int m_NumInputs;
	int m_NumOutputs;
	int m_NumHiddenLayers;
	int m_NeuronsPerHiddenLayer;
	int m_totalNumberofWeights;
	int m_Bias;
	const double outputThreshold = .5;
	double m_Response;
	// storage for each layer of neurons including the output layer
	std::vector<double> curweights;
	std::vector<SNeuronLayer> m_vec_Layers;
public:
	FFNeuralNetwork(int NumInputs, int NumOutputs, int NumHiddenLayers, int NeuronsPerHiddenLayer, int Bias, double response);

	//generates a brand new network with random weights
	void CreateNet();
	//clears the network
	void ClearNet();
	//gets the weights for the NN
	std::vector<double> GetWeights()const;
	//returns the total number of weights in the net
	int GetNumberOfWeights()const;
	//replaces the weights with new ones

	void PutWeights(std::vector<double> &weights);

	//calculates the outputs from a set of inputs

	std::vector<double> Update(std::vector<double> &inputs);
	void hardThreshold(std::vector<double> &doutputs);
	//sigmoid response curve

	double Sigmoid(double activation, double response);

	~FFNeuralNetwork();
};

