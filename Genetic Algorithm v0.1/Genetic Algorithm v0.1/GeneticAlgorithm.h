#include <vector>
#pragma once
class Individual
{
private:

public:
	std::vector <float> Chromosome;
	double fitness;

	Individual();
	~Individual();
};

class GeneticAlgorithm
{
private:
	
public:
	std::vector <Individual> Population;
	double crossoverRate;
	double mutationRate;
	int epoch;
	double avgFitness;

	void Evolve();
	double CalculateAverageFitness();
	GeneticAlgorithm(int sizeOfPopulation, int randomBottom, int randomUp);
	~GeneticAlgorithm();
};

