#ifndef INSECT_H
#define INSECT_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "vectorMath.h"
#include <iostream>

class Insect {
private:
	// Window reference
	sf::RenderWindow* window;

	// physics
	float radius;
	float speed;
	sf::Vector2f direction;
	sf::Vector2f position;

	// shape object
	sf::CircleShape shape;

	//private functions
	void initInsect(float x, float y);
	void clipWalls();

public:
	// construct / destruct
	Insect(sf::RenderWindow* window);
	Insect(sf::RenderWindow* window, float x, float y);
	~Insect();

	// update functions
	void rotate(float angle);
	void updateSpeed(float speedDif);
	void update();

	// render functions
	void renderInsect();
	void drawSpeedVector();
	void render();
};

#endif
