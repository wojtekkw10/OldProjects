#include "GeneticAlgorithm.h"
#include <iostream>
double GeneticAlgorithm::CalculateAverageFitness()
{
	double sum = 0;
	for (int i = 0; i < Population.size(); i++)
	{
		sum += Population[i].fitness;
	}
	double average = sum / Population.size();
	avgFitness = average;
	return average;
}

void GeneticAlgorithm::Evolve()
{
	epoch++;
	//sort the population by fitness
	std::vector <Individual> Sorted;
	std::vector <int> Checked; //Individuals ktore zostaly juz posortowane

	for (int k = 0; k < Population.size(); k++)
	{
		double theBestFitness = 99999999;
		int numberOfTheBest = 0;

		for (int i = 0; i < Population.size(); i++)
		{
			if (Population[i].fitness < theBestFitness)
			{
				bool isChecked = false;
				for (int j = 0; j < Checked.size(); j++)
				{
					if (Checked[j] == i) isChecked = true;
				}
				if (isChecked == false)
				{
					theBestFitness = Population[i].fitness;
					numberOfTheBest = i;
				}
			}

		}
		Checked.push_back(numberOfTheBest);
		Sorted.push_back(Population[numberOfTheBest]);
	}
	//Invert
	int j = 0;
	std::vector <Individual> QSorted;
	QSorted.resize(Sorted.size());
	for (int i = Sorted.size() - 1; i >= 0; i--)
	{
		QSorted[j] = Sorted[i];
		j++;
	}
	for (int i = 0; i < Sorted.size(); i++)
	{
		Sorted[i] = QSorted[i];
	}
	//Sorted


	double FitnessSum = 0;
	for (int i = 0; i < Population.size(); i++)
	{
		FitnessSum += Population[i].fitness;
	}
	
	std::vector <Individual> Roulette;
	for (int i = 0; i < Population.size(); i++)
	{
		int r = rand() % (int)FitnessSum;
		int j = 0;
		double sum = 0;
		for (j=0;j<Population.size();j++)
		{
			sum += Sorted[j].fitness;
			if (sum > r) break;
		}
		Roulette.push_back(Sorted[j]);
	}

	//random mutation
	for (int i = 0; i < Roulette.size(); i++)
	{
		if (rand() % 1000 < mutationRate * 1000) {
			//zamiana miejsc danych w obrebie chromosomu
			int random1 = rand() % Roulette[0].Chromosome.size();
			int random2 = rand() % Roulette[0].Chromosome.size();
			double temp = Roulette[i].Chromosome[random1];
			Roulette[i].Chromosome[random1] = Roulette[i].Chromosome[random2];
			Roulette[i].Chromosome[random2] = temp;

			//zmiana wartosci
			int random3 = rand() % Roulette[0].Chromosome.size();
			Roulette[i].Chromosome[random3] -= 120;
		}
	}

	std::vector <Individual> Crossover;
	//Dla kazdych dwoch
	for (int i = 0; i < Roulette.size()/2; i++)
	{
		bool isCrossed = 0; 
		if (rand() % 1000 < crossoverRate * 1000) isCrossed = true;
		else isCrossed = false;

		if (isCrossed)
		{
			for (int j = 0; j < 2; j++)
			{
				int crossing = rand() % Roulette[i].Chromosome.size(); //wylosuj punkt przeciecia chromosomu
				Individual temp;
				for (int k = 0; k < crossing; k++)
				{
					temp.Chromosome.push_back(Roulette[2 * i].Chromosome[k]);
				} //kopiuj geny do punktu crossing

				for (int k = crossing; k < Roulette[i].Chromosome.size(); k++)
				{
					temp.Chromosome.push_back(Roulette[2 * i + 1].Chromosome[k]);
				} //kopiuj geny od punktu crossing z kolejnego osobnika

				Crossover.push_back(temp);

			}
		}
		else
		{
			Crossover.push_back(Roulette[2 * i]);
			Crossover.push_back(Roulette[2 * i + 1]);
		}
		//Wygeneruj dwa nowe


	}
	this->Population = Crossover;


	std::cout << "Epoch: " << epoch << " ";
	std::cout << "The best fitness: " << Sorted[0].fitness << std::endl;
	std::cout << "Average Fitness: " << avgFitness << std::endl << std::endl;


}

GeneticAlgorithm::GeneticAlgorithm(int sizeOfPopulation, int randomBottom, int randomUp)
{
	Population.resize(sizeOfPopulation);
	crossoverRate = 0.7;
	epoch = 0;
	avgFitness = 0;
	mutationRate = 0.02;

	for (unsigned int i = 0; i < Population.size(); i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Population[i].Chromosome.push_back((rand() % (randomUp-randomBottom)) + randomBottom);
		}
	}
}
GeneticAlgorithm::~GeneticAlgorithm()
{
}


Individual::Individual()
{
	fitness = 0;
}
Individual::~Individual()
{
}
