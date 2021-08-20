#pragma once
#include "vector"
#include <SFML/Graphics.hpp>


int tileSize = 50, tileOffset = 2, mapSize = 20;

int populationSize = 10,
choosingInTournament = 30,
crossingoverChance = 90,
nodeCount = 17,
inputCount = 9,
outputCount = 2,
nextConnectionNo = 1000,
stalenessThreshold = 15;
double weightMutationChance = 0.1,
mutationChance=0.8,
mutationAddConnectionChance=0.08,
mutationAddNodeChance=0.02,
disablingGeneChance=0.75,
noCrossoverChance=0.25,
addFullyConnectedChance=0.05;


int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 500;
double obstacle_speed_start = 1.,
obstacle_speed = obstacle_speed_start,
jumpHeight=0.9,
score_glob=1,
gravity=0.0025;

bool paused = false;

RectangleShape floorShape = RectangleShape(Vector2f(SCREEN_WIDTH, 100));

template<class X> bool contains(vector<X> v, X val)
{
	for (X el : v)
		if (el == val)
			return true;
	return false;
}