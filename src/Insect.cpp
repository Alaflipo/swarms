#include "Insect.h"

void Insect::initInsect(float x, float y) {
	this->shape = sf::RectangleShape();
	this->shape.setPosition(x, y);
	this->shape.setSize(sf::Vector2f(50.0f, 50.0f));
	this->shape.setFillColor(sf::Color::Cyan);
}

Insect::Insect() {
	this->initInsect(0, 0);
}

Insect::Insect(float x, float y) {
	this->initInsect(x, y);
}

Insect::~Insect() {
}

void Insect::update() {
	this->shape.move(sf::Vector2f(1.f, 1.f));
}

void Insect::render(sf::RenderWindow* window) {
	window->draw(this->shape);
}
