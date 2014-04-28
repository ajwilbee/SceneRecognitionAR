#include "FFNeuralNetwork.h"



FFNeuralNetwork::FFNeuralNetwork(int NumInputs, int NumOutputs, int NumHiddenLayers, int NeuronsPerHiddenLayer)
{
	m_NumInputs = NumInputs;
	m_NumOutputs = NumOutputs;
	m_NumHiddenLayers = NumHiddenLayers;
	m_NeuronsPerHiddenLayer = NeuronsPerHiddenLayer;


}

//calculates the outputs from a set of inputs

std::vector<double> FFNeuralNetwork::Update(std::vector<double> &inputs){
	std::vector<double> temp;
	return temp;
}

void FFNeuralNetwork::CreateNet(){
	m_vec_Layers.push_back(SNeuronLayer(m_NeuronsPerHiddenLayer, m_NumInputs));//hidden layer
	//more layers if desired would go here
	m_vec_Layers.push_back(SNeuronLayer(m_NumOutputs, m_NeuronsPerHiddenLayer));//output layer
	
	/*
		neuron/layer*wieghts/neuron = weights per layer 
		to extend the below to include more hidden layers just add m_NeuronsPerHiddenLayer^2 for each hidden
		layer more than 1.
	*/
	m_totalNumberofWeights = m_NeuronsPerHiddenLayer*m_NumInputs + m_NumOutputs*m_NeuronsPerHiddenLayer + (m_NumHiddenLayers - 1)* m_NeuronsPerHiddenLayer*m_NeuronsPerHiddenLayer;

}
//gets the weights for the NN can never alter any member variables
std::vector<double> FFNeuralNetwork::GetWeights()const{
	std::vector<double> curweights;
	//iterate through everylayer, through every node, through every weight and copy into 
	// a weight vector for the Genetic Algorithm, make an iterrator to improve when have time 
	for (int i = 0; i < m_vec_Layers.size(); i++){
		for (int j = 0; j < m_vec_Layers.at(i).m_vecNeurons.size(); j++){
			for (int k = 0; k < m_vec_Layers.at(i).m_vecNeurons.at(j).m_vecWeight.size(); k++){
				curweights.push_back(m_vec_Layers.at(i).m_vecNeurons.at(j).m_vecWeight.at(k));
			}
		}

	}
	
	return curweights;

}
//returns the total number of weights in the net, can never alter any memeber variables
int FFNeuralNetwork::GetNumberOfWeights()const{
	return m_totalNumberofWeights;

}
//replaces the weights with new ones

void FFNeuralNetwork::PutWeights(std::vector<double> &weights){
	int counter = 0;
	// takes the wieghts from the learning function and puts them back into the proper place
	// in the neural network may want to fix the addressing so the counter is not neccessary
	// but it is good enough for now.
	for (int i = 0; i < m_vec_Layers.size(); i++){
		for (int j = 0; j < m_vec_Layers.at(i).m_vecNeurons.size(); j++){
			for (int k = 0; k < m_vec_Layers.at(i).m_vecNeurons.at(j).m_vecWeight.size(); k++){
				m_vec_Layers.at(i).m_vecNeurons.at(j).m_vecWeight.at(k) = weights.at(counter);
				counter++;
			}
		}

	}
}



//sigmoid response curve
/* 1/(1+e^(-a/p))

	activation = a; this is the activeation, or the place on the x
					axis of the function, higher means closer to one.
	response = p; this will change the shape of the sigmoid activation 
*/
inline double Sigmoid(double activation, double response){
	//check this against biorobo activation
	return 1 / (1 + pow(e, -activation / response));

}


FFNeuralNetwork::~FFNeuralNetwork()
{
}
