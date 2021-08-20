#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

using namespace std;
using namespace sf;

class Coin : public Entity<CircleShape>
{
private:
public:

	void randomizePosition()
	{
		x = 900 + rand() % 2000;
	}

	void update(double time)
	{
		dx = -speed;
		x += dx * time;
		shape.setPosition(x, y);

		if (x <= -100) randomizePosition();
	}

	Coin() : Entity(obstacle_speed)
	{
		shape = CircleShape(20, 100);
		shape.setFillColor(Color::Yellow);
		x = 900;
		y = 500;
	}
};
