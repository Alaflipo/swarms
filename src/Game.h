#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <array>
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
	// 0 = seperation, 1 = cohesion, 2 = alignment
	std::array<float, 3> scalarValues;

	// on screen text
	sf::Font font;
	std::array<sf::Text, 3> scalarText;
	std::array<std::string, 3> scalarNames;

	// game objects
	std::vector<Insect> swarm;

	// private functions
	void initSwarm();
	void initilizeVariables();
	void initText();
	void initWindow();

	// random helpers
	std::string convert_float_to_string(float number);

public:
	Game();
	virtual ~Game();

	//Accessors
	bool running();

	// update functions
	void pollEvents();
	void updateMousePositions();
	void updateScalar(int index, float amount);

	void updateSwarmDirection(float angle);
	void updateSwarmSpeed(float speedDif);
	void updateSwarm();

	void update();

	// render functions
	void renderGameState();
	void renderSwarm();
	void render();
};

#endif
