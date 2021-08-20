#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Globals.h"

using namespace std;
using namespace sf;


template<class X> X maxObst(vector<X> v)
{
	X max = v[0];
	for (X el : v)
		if (el > max)
			max = el;
	return max;
}

template<class X> X minObst(vector<X> v)
{
	X min = v[0];
	for (X el : v)
		if (el < max)
			min = el;
	return max;
}

class Obstacle : public Entity<RectangleShape>
{
private:
public:

	void randomizePosition(vector<Obstacle> others)
	{
		shape.setSize(Vector2f(20*(2+rand()%3),shape.getSize().y));
		if(others.size()>0){
			Obstacle maxX = maxObst(others);
			while (true) {
				x = maxX.x + rand() % (SCREEN_WIDTH + 1000);
				if (maxX.x != x)
					if (abs(x - (maxX.x + maxX.shape.getSize().x)) < max(maxX.shape.getSize().x * obstacle_speed*10, shape.getSize().x * obstacle_speed*10) ||
						maxX.shape.getSize().x== shape.getSize().x ||
						x<SCREEN_WIDTH) continue;
				break;
			}
		}
		else { x = SCREEN_WIDTH + rand() % (SCREEN_WIDTH + 3000); }
	}

	void update(double time,vector<Obstacle> others)
	{
		dx = -obstacle_speed*speed;
		x += dx * time;
		shape.setPosition(x, y);

		if (x <= -shape.getSize().x) randomizePosition(others);
	}

	Obstacle(vector<Obstacle> others, RectangleShape floor) : Entity(0.5)
	{
		shape = RectangleShape(Vector2f(40,70));
		shape.setFillColor(Color::Black);
		shape.setOutlineThickness(2);
		shape.setOutlineColor(Color::Red);
		randomizePosition(others);
		y = floor.getPosition().y-shape.getSize().y;
	}

	friend bool operator>(const Obstacle o1, const Obstacle o2);
	friend bool operator<(const Obstacle o1, const Obstacle o2);

};

bool operator>(const Obstacle o1, const Obstacle o2)
{
	return o1.x > o2.x;
}
bool operator<(const Obstacle o1, const Obstacle o2)
{
	return o1.x < o2.x;
}