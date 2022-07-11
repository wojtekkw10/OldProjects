#include <iostream>
#include "GeneticAlgorithm.h"
#include <time.h>

int main()
{
	srand((unsigned int)time(NULL));
	GeneticAlgorithm alg(200,0,500);
	alg.crossoverRate = 0.9;
	double desiredNumber = 250;

	bool stop = false;
	for (int i = 0; i < 200; i++)
	{
		//calculating fitness
		for (unsigned int i = 0; i < alg.Population.size(); i++)
		{
			int sum = 0;
			for (int j = 0; j < 5; j++)
			{
				sum += alg.Population[i].Chromosome[j];
			}
			if (desiredNumber == sum) alg.Population[i].fitness = 1000;
			else alg.Population[i].fitness =  -abs(desiredNumber - sum)+1000;
		}
		//fitness should be as high as possible


		int avg = alg.CalculateAverageFitness();
		alg.Evolve();

		if (avg == 1000)
		{
			int sum = 0;
			for (int i = 0; i < 5; i++)
			{
				sum += alg.Population[0].Chromosome[i];
				std::cout << alg.Population[0].Chromosome[i] << " ";
			}
			std::cout << sum << " ";
			stop = true;
		}
		if (stop) break;
	}

	//wypisz najlepszego
	std::cout << std::endl << std::endl;
	int sum = 0;
	std::cout << "The best: ";
	for (int i = 0; i < 5; i++)
	{
		sum += alg.Population[0].Chromosome[i];
		std::cout << alg.Population[0].Chromosome[i] << " ";
	}
	std::cout << "Sum: " << sum << " ";
	std::cout << std::endl << std::endl;

	system("pause");
}