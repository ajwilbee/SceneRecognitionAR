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
Resource::Resource()
{
}


Resource::~Resource()
{
}
