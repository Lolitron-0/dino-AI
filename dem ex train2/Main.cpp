#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include "iostream"
#include "vector"
#include "PLayer.h"
#include "Obstacle.h"
//#include "Spike.h"
//#include "Coin.h"
#include "Button.h"
#include "Globals.h"
#include "Population.h"

using namespace sf;
using namespace std;



void buttonsPressed(Event event,Player &player, map<string, Button> &buttons,Vector2f pos,RenderWindow &window,bool &paused)
{
	for (map<string, Button>::iterator i = buttons.begin(); i != buttons.end(); i++)
	{
		if (i->second.check(event, pos))
		{
			if (i->first == "exit")
			{
				window.close();
			}
			else if (i->first == "pause")
			{
				paused = !paused;
			}
		}
	}
}



int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"",Style::Default);
	window.setFramerateLimit(60);

	Font font;
	font.loadFromFile("C:/Users/ClarVik/source/repos/dem ex train2/Debug/sansation.ttf");
	Text score = Text("",font,20);



	floorShape.setPosition(0, SCREEN_HEIGHT - floorShape.getSize().y);
	floorShape.setFillColor(Color::Black);
	floorShape.setOutlineThickness(5);
	floorShape.setOutlineColor(Color::White);

	vector<Obstacle> obstacles;
	Obstacle o1(obstacles,floorShape);
	obstacles.push_back(o1);
	Obstacle o2(obstacles, floorShape);
	obstacles.push_back(o2);
	Obstacle o3(obstacles, floorShape);
	obstacles.push_back(o3);

	Button pause = Button();
	pause.text = Text("Pause", font, 35);
	pause.text.setPosition(pause.getPosition());
	pause.text.setFillColor(Color::Black);
	map<string, Button> buttons = { {"pause",pause} };
	bool paused=false;
	Text maxScoreText = Text("MaxScore: ",font,50);
	maxScoreText.setFillColor(Color::White);
	maxScoreText.setOutlineThickness(3);
	maxScoreText.setPosition(0, window.getView().getCenter().y);

	Population population(populationSize);

	Vector2f pos;

	Clock clock;
	double time;

	while (window.isOpen())
	{
		time = clock.getElapsedTime().asMicroseconds();
		time /= 800;
		clock.restart();

		pos = window.mapPixelToCoords(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (!paused) {
			obstacle_speed += 0.00001 * time;
			score_glob += 0.01 * time;
		}

		window.clear();

		

		if (!population.done()) {
			population.updateAlive(obstacles, time, window);
			population.getBestOfGen().brain.draw(window);
		}
		else {
			population.naturalSelection();
			for (int i = 0; i < obstacles.size(); i++)
				obstacles[i].randomizePosition(obstacles);
			time = 0;
			clock.restart();
		}

		for (int i = 0; i < obstacles.size(); i++)
		{
			if (!paused)obstacles[i].update(time,obstacles);
			obstacles[i].draw(window);
		}


		window.draw(floorShape);
		score.setPosition(0,50);
		score.setString("Score: "+to_string((int)score_glob));
		window.draw(score );
		if (score_glob >= 2500) paused = true;
		if (paused)
		{
			maxScoreText.setString("WON IN "+to_string(population.gen)+" GENERATIONS!");
			window.draw(maxScoreText);
		}
		for (map<string,Button>::iterator i=buttons.begin(); i != buttons.end(); i++)
		{
			i->second.draw(window);
			window.draw(i->second.text);
		}
		window.display();
	}
	return 0;
}
