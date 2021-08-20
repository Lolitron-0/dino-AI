#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include "Spike.h"
#include "Coin.h"
#include "Brain.h"

using namespace std;
using namespace sf;

class Player
{
public:
	Brain brain;
	float fitness=0;
	int inputs = 5;
	int outputs = 1;
	vector<float> vision;
	vector<float> decision;

	int gen = 0;

	RectangleShape shape;

	double x=100, y=0;
	double dx=0, dy=0;
	int onGround = 0;

	bool alive = true;
	double score = 1;
	double bestScore;



	bool isOnGround() { return onGround>0; }
	double getWidth() { return shape.getGlobalBounds().width; }
	double getHeight() { return shape.getGlobalBounds().height; }
	double getScore() { return score; }


	void fitFunc()
	{
		fitness = score*score;
	}

	void jump()
	{
		dy = -jumpHeight;
		onGround--;
	}

	void look(vector<Obstacle> obstacles)
	{
		float min = 1000000;
		int minIndex=-1;

		for (int i = 0; i < obstacles.size(); i++)
		{
			if (obstacles[i].getX() > x + getWidth() && abs((x + getWidth()) - obstacles[i].getX()) < min && obstacles[i].getX() < SCREEN_WIDTH)
			{
				min = abs((x + getWidth()) - obstacles[i].getX()) ;
				minIndex = i;
			}
		}

		if (minIndex == -1)
			vision[0] = 0;
		else
			vision[0] = 1/min;

		float between, nextMin=1000000;
		int min2Index = -1;

		for (int i = 0; i < obstacles.size(); i++)
		{
			if (obstacles[i].getX() > x + getWidth() && abs((x + getWidth()) - obstacles[i].getX()) < min && i!=minIndex && obstacles[i].getX()<SCREEN_WIDTH)
			{
				nextMin = abs((x + getWidth()) - obstacles[i].getX());
				between = abs(nextMin-min);
				min2Index = i;
			}
		}

		if (min2Index == -1)
			vision[1] = 0;
		else
			vision[1] = 1/between;

		vision[2] = 1/obstacle_speed;

		vision[3] = 1 / y;

		vision[4] = (onGround==0?0:1./ (double)onGround);

	}

	void think()
	{
		decision = brain.feedForward(vision);

		if (decision[0]>0.5 && onGround > 0) {
			jump();
		}
	}

	Player* crossover(Player parent2)
	{
		Player* child = new Player();
		child->brain = *brain.crossover(parent2.brain);
		child->brain.generateNetwork();
		return child;
	}

	void update(double time,vector<Obstacle> obstacles)
	{

		dy += gravity * time;
		if (shape.getGlobalBounds().intersects(floorShape.getGlobalBounds()))
		{
			y = floorShape.getPosition().y-shape.getSize().y;
		}

		y += dy * time;

		shape.setPosition(x,y);
		if (y >= floorShape.getPosition().y-shape.getSize().y)
		{
			onGround = 2;
			dy = 0;
		}
		dx = 0;

		collision(obstacles);

		score = score_glob;
	}

	void collision(vector<Obstacle> obstacles)
	{
		for (int i = 0; i < obstacles.size(); i++)
		{
			if (shape.getGlobalBounds().intersects(obstacles[i].getGlobalBounds()))
				alive = false;
		}
	}

	void draw(RenderWindow& window) { window.draw(shape); }

	Player()
	{
		shape = RectangleShape(Vector2f(50,100));
		shape.setPosition(100,100);
		shape.setFillColor(Color::Black);
		shape.setOutlineThickness(2);
		shape.setOutlineColor(Color::Green);
		vision = vector<float>(inputs);
		decision = vector<float>(outputs);
		brain = Brain(inputs,outputs);
	}

	Player clone()
	{
		Player clone = Player();
		clone.brain = brain.clone();
		clone.fitness = fitness;
		clone.brain.generateNetwork();
		clone.gen = gen;
		clone.bestScore = score;
		return clone;
	}

	Player* clonePointer()
	{
		Player* clone = new Player();
		clone->brain = brain.clone();
		clone->fitness = fitness;
		clone->brain.generateNetwork();
		clone->gen = gen;
		clone->bestScore = score;
		return clone;
	}
};
