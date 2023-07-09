#ifndef INSECT_H
#define INSECT_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Insect {
private:
	sf::RectangleShape shape;

	//private functions
	void initInsect(float x, float y);

public:
	// construct / destruct
	Insect();
	Insect(float x, float y);
	~Insect();

	// update functions
	void update();

	// render functions
	void render(sf::RenderWindow* window);
};

#endif
