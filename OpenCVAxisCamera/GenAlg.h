#pragma once
#include "FFNeuralNetwork.h"
#include <iostream>
#include <fstream>
#include "Resource.h"







class GenAlg
{
private:

	// this is the correct and known classification against which the fitness of the gene is measured
	std::vector<double> m_correct_Classification;
	//the current classification from the NN with the given weights
	int m_NN_Classification;
	//the test inputs that contain the input data, and seperatly the correct output to the system
	std::vector<NNInputData> m_Inputs;
	//this holds the entire population of chromosomes
	std::vector <SGenome> m_vecPop;
	//this holds the entire RouletteWheel population distribution
	std::vector <SGenome> RouletteWheel;
	//size of population
	int  m_iPopSize;
	//amount of weights per chromo
	int  m_iChromoLength;
	//total fitness of population
	double  m_dTotalFitness;
	//best fitness this population
	double  m_dBestFitness;
	//average fitness
	double  m_dAverageFitness;
	//worst
	double  m_dWorstFitness;
	//keeps track of the best genome
	int  m_iFittestGenome;
	//keeps track of the worst genome
	int m_iWorstGenome;
	//probability that a chromosomes bits will mutate.
	//Try figures around 0.05 to 0.3 ish
	double  m_dMutationRate;
	//probability of chromosomes crossing over bits
	//0.7 is pretty good
	double  m_dCrossoverRate;
	//generation counter
	int  m_cGeneration;
	//pointer to the NN to be operated on
	FFNeuralNetwork* m_NN;
	int epochCounter;

	double expected0;
	double expected1;
	double BestTotalCorrect;
	double TotalInputs;
	double TotalCorrect;

	double Bestcorrect0;
	double Bestcorrect1;

	LARGE_INTEGER Frequency;
	LARGE_INTEGER t1, t2;
	double TimeElapsed;

	std::ofstream fitnessC;
	void  Crossover(const std::vector<double> &mum,
					const std::vector<double> &dad,
					std::vector<double>       &baby1,
					std::vector<double>       &baby2);

	void  Mutate(std::vector<double> &chromo);
	SGenome  GetChromoRoulette();
	void CreateRouletteWheel();
	void  GrabNBest(int  NBest,
			  const int  NumCopies,
	std::vector<SGenome> &vecPop);

	void CalculateBestWorstAvTot();
	int Fitness(SGenome &gene, int index ); 
	int Fitness2(SGenome &gene, int index);
	int Fitness3(SGenome &gene, int index);
	void  Reset();
	void getExpectedoutputcount();
	int interpertOutput(std::vector<double> output);
	SGenome  GetChromoRandom();

public:
	
	

	GenAlg(int    popsize,
		   double MutRat,
		   double CrossRat,
		   FFNeuralNetwork* NN,
		   std::vector<NNInputData> Inputs);

	//this runs the GA for one generation.

	std::vector<SGenome> Epoch(std::vector<SGenome> &old_pop, int FitnessFunctionToUse);

	//-------------------accessor methods

	std::vector<SGenome> GetChromos()const{ return m_vecPop; }

	double  AverageFitness()const{ return m_dTotalFitness / m_iPopSize; }
	double  fRand(double fMin, double fMax);
	double  BestFitness()const{ return m_dBestFitness; }
	void writeBestWeights();
	void geneFitnessOutputToFile();

	~GenAlg();
};

