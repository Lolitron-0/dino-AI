#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

template <class X> class Entity
{
protected:
	X shape;
	double x, y;
	double dx = 0, dy = 0;
	double speed;
public:

	FloatRect getGlobalBounds() { return shape.getGlobalBounds(); }
	double getX() { return x; }
	double getY() { return y; }

	void setDy(double d) { this->dy = d; }
	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }

		

	void draw(RenderWindow& window) { window.draw(shape); }

	Entity(double speed)
	{
		this->speed = speed;
	}
};
#pragma once
