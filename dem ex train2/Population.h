#pragma once
#include <iostream>
#include "vector"
#include "cmath"
#include "ctime"
#include "numeric"
#include <fstream>
#include <algorithm>
#include "Globals.h"
#include "Species.h"

using namespace std;


class Population
{
public:
	vector<Player> pop;
	Player bestPlayer;
	int bestScore;
	int gen;
	vector<ConnectionHistory> innovationHistory;
	vector<Player> genPlayers;
	vector<Species> species;

	bool massExtinctionEvent = false;
	bool newStage = false;
	int populationLife = 0;

	Population(int size)
	{
		for (int i = 0; i < size; i++)
		{
			pop.push_back(Player());
			pop[i].brain.generateNetwork();
			pop[i].brain.mutate(innovationHistory);
			if (double(rand()) / RAND_MAX < addFullyConnectedChance)
			{
				while (!pop[i].brain.fullyConnected())
					pop[i].brain.addConnection(innovationHistory);
			}
		}
	}

	void updateAlive(vector<Obstacle> obstacles, double time,RenderWindow &window)
	{
		for (int i = 0; i < pop.size(); i++)
		{
			if (pop[i].alive)
			{
				pop[i].look(obstacles);
				pop[i].think();
				pop[i].update(time,obstacles);
				pop[i].draw(window);
			}
		}
	}

	bool done()
	{
		for (int i = 0; i < pop.size(); i++)
		{
			if (pop[i].alive)
				return false;
		}
		return true;
	}

	void setBestPlayer()
	{
		Player tempBest = *species[0].players[0];
		tempBest.gen = gen;

		if (tempBest.score > bestScore)	
		{
			bestScore = tempBest.score;
			bestPlayer = tempBest.clone();
		}
	}

	Player getBestOfGen()
	{
		Player tBestScore=pop[0];
		for (int i = 0; i < pop.size(); i++)
		{
			if (pop[i].score > tBestScore.score)
				tBestScore = pop[i];
		}
		return tBestScore;
	}

	void naturalSelection()
	{
		speciate();
		calculateFitness();
		sortSpecies();
		if (massExtinctionEvent)
		{
			massExtinction();
			massExtinctionEvent = false;
		}
		cullSpecies();
		setBestPlayer();
		killStaleSpecies();
		killBadSpecies();

		cout << "gen: " << gen << "\n mutations: " << innovationHistory.size() << "\n species: " << species.size()<<"\n---------------------------\n";

		float averageSum = getAverageFitnessSum();
		vector<Player> children;
		for (int i = 0; i < species.size(); i++)
		{
			children.push_back(species[i].champ->clone());

			int numOfChildren = floor(species[i].averageFitness / averageSum * pop.size()) - 1;
			for (int j = 0; j < numOfChildren; j++)
				children.push_back(*species[i].giveMeBaby(innovationHistory));
		}

		while (children.size() < pop.size())
			children.push_back(*species[0].giveMeBaby(innovationHistory));

		pop = vector<Player>(children);
		gen++;
		for (int i = 0; i < pop.size(); i++)
			pop[i].brain.generateNetwork();
		populationLife = 0;
		score_glob = 0;
		obstacle_speed = obstacle_speed_start;
	}

	void speciate()
	{
		for (int i = 0; i < species.size(); i++)
		{
			species[i].players.clear();
			species[i].players.shrink_to_fit();
		}

		for (int i = 0; i < pop.size(); i++)
		{
			bool speciesFound = false;
			for (int j = 0; j < species.size(); j++)
			{
				if (species[j].sameSpecies(pop[i].brain)) {
					species[j].addToSpecies(&pop[i]);
					speciesFound = true;
					break;
				}
			}

			if (!speciesFound)
				species.push_back(Species(&pop[i]));
		}
	}

	void calculateFitness()
	{
		for (int i = 0; i < pop.size(); i++)
		{
			pop[i].fitFunc();
		}
	}

	void sortSpecies()
	{
		for (int i = 0; i < species.size(); i++)
			species[i].sortSpecies();

		Species temp;
		for (int i = 0; i < species.size() - 1; i++)
		{
			for (int j = 0; j < species.size() - i - 1; j++)
			{
				if (species[j].bestFitness > species[j + 1].bestFitness)
				{
					temp = species[j];
					species[j] = species[j + 1];
					species[j + 1] = temp;
				}
			}
		}
	}

	void cullSpecies()
	{
		for (int i = 0; i < species.size(); i++)
		{
			species[i].cull();
			species[i].fitnessSharing();
			species[i].setAverage();
		}
	}

	void killBadSpecies()
	{
		float averageSum = getAverageFitnessSum();
		for (int i = 1; i < species.size(); i++)
		{
			if (species[i].averageFitness / averageSum * pop.size()<1)
			{
				species.erase(species.begin() + i, species.begin() + i + 1);
				i--;
			}
		}
	}

	float getAverageFitnessSum()
	{
		float averageSum = 0.;
		for (int i = 0; i < species.size(); i++)
			averageSum += species[i].averageFitness;
		return averageSum;
	}
	
	void killStaleSpecies()
	{
		for (int i = 2; i < species.size(); i++)
		{
			if (species[i].staleness > stalenessThreshold)
			{
				species.erase(species.begin() + i, species.begin() + i + 1);
				i--;
			}
		}
	}

	void massExtinction()
	{
		for (int i = 5; i < species.size(); i++)
		{
			species.erase(species.begin() + i, species.begin() + i + 1);
			i--;
		}
		species.shrink_to_fit();
	}
};
