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
	sf::Vector2f speed;
	sf::Vector2f position;

	// shape object
	sf::CircleShape shape;

	//private functions
	void initInsect(float x, float y);

public:
	// construct / destruct
	Insect(sf::RenderWindow* window);
	Insect(sf::RenderWindow* window, float x, float y);
	~Insect();

	// update functions
	void rotateSpeed(float angle);
	void updateSpeed(sf::Vector2f speedDif);
	void update();

	// render functions
	void renderInsect();
	void drawSpeedVector();
	void render();
};

#endif
