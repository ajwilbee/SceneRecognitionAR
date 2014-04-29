#include "FFNeuralNetwork.h"






FFNeuralNetwork::FFNeuralNetwork(int NumInputs, int NumOutputs, int NumHiddenLayers, int NeuronsPerHiddenLayer, int Bias, double response)
{
	m_NumInputs = NumInputs;
	m_NumOutputs = NumOutputs;
	m_NumHiddenLayers = NumHiddenLayers;
	m_NeuronsPerHiddenLayer = NeuronsPerHiddenLayer;
	m_Bias = Bias;
	m_Response = response;


}

//calculates the outputs from a set of inputs

std::vector<double> FFNeuralNetwork::Update(std::vector<double> &inputs){
	//stores the resultant outputs from each layer

	std::vector<double> outputs;

	int cWeight = 0;

	//first check that we have the correct amount of inputs

	if (inputs.size() != m_NumInputs)

	{
		//just return an empty vector if incorrect.

		return outputs;
	}




	//For each layer....

	for (int i = 0; i<m_NumHiddenLayers + 1; ++i)

	{
		if (i > 0)
		{
			inputs = outputs;
		}
		outputs.clear();

		cWeight = 0;

		//for each neuron sum the (inputs * corresponding weights).Throw 

		//the total at our sigmoid function to get the output.

		for (int j = 0; j< m_vec_Layers[i].m_NumNeurons; ++j)

		{
			double netinput = 0;

			int NumInputs = m_vec_Layers[i].m_vecNeurons[j].m_NumInputs;

			//for each weight

			for (int k = 0; k<NumInputs - 1; ++k)

			{
				//sum the weights x inputs
				netinput += m_vec_Layers[i].m_vecNeurons[j].m_vecWeight[k] * inputs[cWeight++];
			}

			//add in the bias
			// ignor the bias for now, it is essentially just another weight... will add if needed
			netinput += m_vec_Layers[i].m_vecNeurons[j].m_vecWeight[NumInputs - 1] * m_Bias;
			//we can store the outputs from each layer as we generate them. 

			//The combined activation is first filtered through the sigmoid 

			//function		
			outputs.push_back(Sigmoid(netinput, m_Response));
	//		cWeight = 0;

		}

	}
	hardThreshold(outputs);
	return outputs;

}
void FFNeuralNetwork::hardThreshold(std::vector<double> &doutputs){
	 
	for (int i = 0; i < doutputs.size(); i++){
		if (doutputs[i] < outputThreshold){
			doutputs[i] = 0;

		}
		else{
			doutputs[i] = 1;
		}
	}
}



void FFNeuralNetwork::CreateNet(){
	m_vec_Layers.push_back(SNeuronLayer(m_NeuronsPerHiddenLayer, m_NumInputs+1));//hidden layer, the plus one gives the threshold to be multiplied by the bias
	//more layers if desired would go here
	m_vec_Layers.push_back(SNeuronLayer(m_NumOutputs, m_NeuronsPerHiddenLayer+1));//output layer, again +1 is threshold
	
	/*
		neuron/layer*wieghts/neuron = weights per layer 
		to extend the below to include more hidden layers just add m_NeuronsPerHiddenLayer^2 for each hidden
		layer more than 1.
	*/
	m_totalNumberofWeights = m_NeuronsPerHiddenLayer*m_NumInputs + m_NumOutputs*m_NeuronsPerHiddenLayer + (m_NumHiddenLayers - 1)* m_NeuronsPerHiddenLayer*m_NeuronsPerHiddenLayer;

}

void FFNeuralNetwork::ClearNet(){
	m_vec_Layers.clear();
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
					the activation comes from the sum of all the inputs
					to the neuron
	response = p; this will change the shape of the sigmoid activation 
*/
inline double FFNeuralNetwork::Sigmoid(double activation, double response){
	//check this against biorobo activation
	return 1 / (1 + pow(e, -activation / response));

}
// going to need an activation threshold

FFNeuralNetwork::~FFNeuralNetwork()
{

	m_vec_Layers.clear();
	curweights.clear();
}
