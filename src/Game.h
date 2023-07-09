#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

#include "Insect.h"

/**
 * Wrapper class for the game engine
*/

class Game {
private:
	//variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// game logic
	int swarmSize {};

	// game objects
	std::vector<Insect> swarm;

	// private functions
	void initSwarm();
	void initilizeVariables();
	void initWindow();

public:
	Game();
	virtual ~Game();

	//Accessors
	bool running();

	// update functions
	void pollEvents();
	void updateMousePositions();

	void updateSwarmSpeed(float angle);
	void updateSwarm();
	void update();

	// render functions
	void renderSwarm();
	void render();
};

#endif
