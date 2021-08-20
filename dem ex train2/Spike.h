#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

using namespace std;
using namespace sf;

class Spike : public Entity<CircleShape>
{
private:
public:

	void randomizePosition()
	{
		y = 450 + rand() % 50;
		x = 900 + rand() % 3000;
	}

	void update(double time)
	{
		dx = -speed;
		x += dx * time;
		shape.setPosition(x, y);

		if (x <= -100) randomizePosition();
	}

	Spike(double speed) : Entity(speed)
	{
		shape = CircleShape(20,3);
		shape.setFillColor(Color::Magenta);
		x = 900;
		y = 450;
	}
};
