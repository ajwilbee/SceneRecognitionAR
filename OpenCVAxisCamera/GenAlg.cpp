#include "GenAlg.h"

#include <algorithm>




GenAlg::GenAlg(int    popsize,
			   double MutRat,
			   double CrossRat,
			   FFNeuralNetwork* NN,
			   std::vector<NNInputData> Inputs)
{
	m_iPopSize = popsize;
	m_dMutationRate = MutRat;
	m_dCrossoverRate = CrossRat;
	m_iChromoLength = NN->GetNumberOfWeights();
	m_NN = NN;
	m_Inputs = Inputs;
	
	m_iFittestGenome = -1;
	
	

	Reset();
}

void  GenAlg::Crossover(const std::vector<double> &mum,
						const std::vector<double> &dad,
							  std::vector<double> &baby1,
							  std::vector<double> &baby2)
{
	int modValue = 100;
	double temp;
	for (int i = 0; i < mum.size(); i++){
		temp = fRand(0,1);
		if (temp < modValue *m_dCrossoverRate){
			baby1.push_back(mum[i]);
			baby2.push_back(dad[i]);

		}
		else{
			baby1.push_back(dad[i]);
			baby2.push_back(mum[i]);

		}
	}

}
double  GenAlg::fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

void  GenAlg::Mutate(std::vector<double> &chromo)
{
	//randomly reasign everything...
	int length = chromo.size();
	int modValue = 100;
	double temp;
	for (int i = 0; i < length; i++){
		temp = fRand(0, 1);
		double thresh = 1;
		//will mutate the genes at a rate dictated by mutation, looks at every gene and decides
		if (temp < thresh*m_dMutationRate){
			chromo[i] = fRand(0, 1)-.5;
		}

	}
}

// returns a random gene, may wish to make it more intelligent in the future
SGenome  GenAlg::GetChromoRoulette()
{
	int Roulette = rand() % m_iPopSize;
	return m_vecPop[Roulette];
}

// sorts the genes based on their fitness then copies numcopies worth of each NBest genes
void  GenAlg::GrabNBest(int  NBest,
				  const int  NumCopies,
		std::vector<SGenome> &vecPop)
{
	// sorts using the overloaded < operator which compares the fitness
	std::sort(m_vecPop.begin(), m_vecPop.end());

	if (NBest*NumCopies > m_iPopSize){
		NBest = m_iPopSize / NumCopies;
	}
	for (int i = 0; i < NBest; i++){
		for (int j = 0; j < NumCopies; j++){
			vecPop.push_back(m_vecPop[i]);
		}

	}

}

void GenAlg::CalculateBestWorstAvTot()
{

}

// eliminates the whole population and recreates it except for the best gene, also initializes
void  GenAlg::Reset()
{
	SGenome BestGenome;
	
	if (m_iFittestGenome != -1){
		BestGenome = m_vecPop[m_iFittestGenome];
	}
	m_vecPop.clear();
	std::vector<double> weightHolder;
	double temp;
	for (int i = 0; i < m_iPopSize; i++){
		for (int j = 0; j < m_iChromoLength; j++){
			double temp = fRand(0, 1)-.5;
			weightHolder.push_back(temp);

		}
		m_vecPop.push_back(SGenome(weightHolder, 0));
		weightHolder.clear();
	}
	if (m_iFittestGenome != -1){
		m_vecPop[0] = BestGenome;
		m_iFittestGenome = 0;
	}
	m_cGeneration = 0;
	m_dTotalFitness = 0;
	m_dBestFitness = 0;
	m_dAverageFitness = 0;
	m_dWorstFitness = 0;
}

int GenAlg::interpertOutput(std::vector<double> output){
	int intoutput = 0;
	if (output.size() == 1){
		intoutput = output[0];
	}

	return intoutput;

}

//calls the NN recieves the output and determines the fitness of the gene
// may wish to abstract out the NN call
int GenAlg::Fitness(SGenome gene, int index){
	//set the neural network with proper weights
	m_NN->PutWeights(gene.vecWeights);
	int fitnesscount = 0;
	// run through all of the inputs and checking the output to judge fitness
	fitnessC.open("Classifications.csv",std::ios::app);
	for (int i = 0; i < m_Inputs.size(); i++){
		m_NN_Classification = interpertOutput(m_NN->Update(m_Inputs[i].features));
		if (m_NN_Classification == m_Inputs[i].CorrectDiagnosis){
			fitnesscount++;
		}
		
		fitnessC << m_NN_Classification;
		fitnessC << ",";

	}
	fitnessC << "\n";
	fitnessC.close();

	gene.dFitness = fitnesscount;
	if (fitnesscount >= m_dBestFitness){
		m_iFittestGenome = index;
		m_dBestFitness = fitnesscount;
	}

	if (fitnesscount <= m_dWorstFitness){
		m_iWorstGenome = index;
		m_dWorstFitness = fitnesscount;
	}
	
	fitnessC.open("Fitness.csv", std::ios::app);
	fitnessC << fitnesscount;
	fitnessC << ",";
	fitnessC.close();
	return fitnesscount;
}

int GenAlg::FitnessDiversity(SGenome gene, int index){
	//set the neural network with proper weights
	m_NN->PutWeights(gene.vecWeights);
	int fitnesscount = 0;
	// run through all of the inputs and checking the output to judge fitness
	fitnessC.open("Classifications.csv", std::ios::app);
	for (int i = 0; i < m_Inputs.size(); i++){
		m_NN_Classification = interpertOutput(m_NN->Update(m_Inputs[i].features));
		if (m_NN_Classification == m_Inputs[i].CorrectDiagnosis){
			fitnesscount++;
		}

		fitnessC << m_NN_Classification;
		fitnessC << ",";

	}
	fitnessC << "\n";
	fitnessC.close();

	gene.dFitness = fitnesscount;
	if (fitnesscount >= m_dBestFitness){
		m_iFittestGenome = index;
		m_dBestFitness = fitnesscount;
	}

	if (fitnesscount <= m_dWorstFitness){
		m_iWorstGenome = index;
		m_dWorstFitness = fitnesscount;
	}

	fitnessC.open("Fitness.csv", std::ios::app);
	fitnessC << fitnesscount;
	fitnessC << ",";
	fitnessC.close();
	return fitnesscount;

}

std::vector<SGenome> GenAlg::Epoch(std::vector<SGenome> &old_pop)
{
	int tempTotalFitness = 0;
	for (int i = 0; i < old_pop.size(); i++){
		tempTotalFitness += Fitness(m_vecPop[i], i);
	}
	fitnessC.open("Fitness.csv", std::ios::app);
	fitnessC << "\n";
	fitnessC.close();
	m_dTotalFitness = tempTotalFitness;
	m_dAverageFitness = m_dTotalFitness / m_iPopSize;
	m_cGeneration++;
	// current thought keep the best one in the population of course and make 5
	// take the top 10, and make a copy of each, keep the bottom one only make one
	// get the rest randomly
	// do the same thing with the mom, then use std::random_shuffle ( myvector.begin(), myvector.end() );
	// to mix them up so that real mating happens

	std::vector <SGenome> mom;
	std::vector <SGenome> dad;
	int numBest = 10;
	int numBestCopies = 2;
	int Bestcount = 5;
	for (int i = 0; i < Bestcount; i++){
		mom.push_back(m_vecPop[m_iFittestGenome]);
		dad.push_back(m_vecPop[m_iFittestGenome]);
	}
	GrabNBest(10,2,mom);
	GrabNBest(10,2,dad);
	mom.push_back(m_vecPop[m_iWorstGenome]);
	dad.push_back(m_vecPop[m_iWorstGenome]);
	
	int filler = m_iPopSize/2 - Bestcount - numBest*numBestCopies-1; // the -1 accounts for the worst one that is kept in the population

	for (int i = 0; i < filler; i++){

		mom.push_back(GetChromoRoulette());
		dad.push_back(GetChromoRoulette());
	}
	std::random_shuffle(mom.begin(), mom.end());
	std::random_shuffle(dad.begin(), dad.end());

	//empty vectors to be filled
	std::vector <double> baby1;
	std::vector <double> baby2;
	SGenome BestGene = m_vecPop[m_iFittestGenome];
	m_vecPop.clear();
	//save the best gene
	m_vecPop.push_back(BestGene);
	for (int i = 0; i < mom.size(); i++){
		Crossover(mom[i].vecWeights, dad[i].vecWeights, baby1, baby2);
		Mutate(baby1);
		Mutate(baby2);
		m_vecPop.push_back(SGenome(baby1, 0));
		m_vecPop.push_back(SGenome(baby2, 0));
		baby1.clear();
		baby2.clear();
	}
	// keep the pop the same size
	m_vecPop.pop_back();
	mom.clear();
	dad.clear();

	
	return m_vecPop;
}

GenAlg::~GenAlg()
{
	// this is the correct and known classification against which the fitness of the gene is measured
	m_correct_Classification.clear();
	//the test inputs that contain the input data, and seperatly the correct output to the system
	m_Inputs.clear();
	//this holds the entire population of chromosomes
	m_vecPop.clear();

}
