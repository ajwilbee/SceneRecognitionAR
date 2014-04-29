#pragma once
#define e 2.71828183
#include<vector>

/*
code used and modified from
http://www.ai-junkie.com/ann/evolved/nnt6.html
*/

struct SNeuron
{

	//the number of inputs into the neuron

	int m_NumInputs;

	//the weights for each input

	std::vector<double> m_vecWeight;

	//constructor

	SNeuron(int NumInputs);

};
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

struct SNeuronLayer
{

	//the number of neurons in this layer

	int m_NumNeurons;

	//the layer of neurons

	std::vector<SNeuron> m_vecNeurons;

	//constructor
	SNeuronLayer(int NumNeurons, int NumInputsPerNeuron);

};

SNeuronLayer::SNeuronLayer(int NumNeurons, int NumInputsPerNeuron) : m_NumNeurons(NumNeurons)
{
	for (int i = 0; i<NumNeurons + 1; ++i)

	{

		//set up Layer with all neurons with random weighting

		m_vecNeurons.push_back(SNeuron(NumInputsPerNeuron));

	}

}



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

	inline double Sigmoid(double activation, double response);

	~FFNeuralNetwork();
};

