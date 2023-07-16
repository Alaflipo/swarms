#ifndef INSECT_H
#define INSECT_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "vectorMath.h"
#include <iostream>
#include <vector>

class Insect {
private:
	// Window reference
	sf::RenderWindow* window;

	// physics
	float radius;
	float radiusCircle;
	float speed;
	sf::Vector2f direction;
	sf::Vector2f position;

	// shape object
	sf::CircleShape shape;
	sf::CircleShape visionCircle;

	//private functions
	void initInsect(float x, float y);
	void clipWalls();

public:
	// construct / destruct
	Insect(sf::RenderWindow* window);
	Insect(sf::RenderWindow* window, float x, float y);
	~Insect();

	// getters
	sf::Vector2f getPosition();
	sf::Vector2f getDirection();

	// update functions
	void rotate(float angle);
	void updateSpeed(float speedDif);
	void seperation(std::vector<Insect>& others, float scalar);
	void alignment(std::vector<Insect>& others, float scalar);
	void cohesion(std::vector<Insect>& others, float scalar);
	void update();

	// render functions
	void drawInsect();
	void drawSpeedVector();
	void render();
};

#endif
