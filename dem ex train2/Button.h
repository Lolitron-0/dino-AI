#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

using namespace std;
using namespace sf;

class Button
{
private: 
	RectangleShape shape;
	
public:
	Text text;

	double getWidth() { return shape.getSize().x; }
	double getHeight() { return shape.getSize().y; }
	Vector2f getPosition() { return shape.getPosition(); }

	bool check(Event event,Vector2f pos)
	{
		if (shape.getGlobalBounds().contains(pos))
		{
			shape.setFillColor(Color(200,200,200,255));
			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				return true;
			}
		}
		else
		{
			shape.setFillColor(Color(255, 255, 255, 255));
		}
		return false;
	}

	void draw(RenderWindow& window)
	{
		window.draw(shape);
	}

	Button()
	{
		shape = RectangleShape(Vector2f(100,50));
		shape.setPosition(SCREEN_WIDTH - getWidth(), SCREEN_HEIGHT - getHeight());
	}
};
