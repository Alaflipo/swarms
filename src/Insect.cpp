#include "Insect.h"

/**
 *
 * ==========================================
 * ===============INITILIZATION==============
 * ==========================================
 *
*/

void Insect::initInsect(float x, float y) {
	this->radius = 10.f;
	this->speed = 10.0f;

	// define triangle shape (circle with 3 corners)
	this->shape = sf::CircleShape(this->radius, 3);
	this->shape.setPosition(x, y);
	this->shape.setOrigin(this->radius, this->radius);
	this->shape.setFillColor(sf::Color::Cyan);

	this->position = sf::Vector2f { x, y };
	this->direction = sf::Vector2f { 1.f, 0.f };
}

Insect::Insect(sf::RenderWindow* window) {
	this->window = window;
	this->initInsect(0, 0);
}

Insect::Insect(sf::RenderWindow* window, float x, float y) {
	this->window = window;
	this->initInsect(x, y);
}

Insect::~Insect() {
}

/**
 *
 * ==========================================
 * =============UPDATE FUNCTIONS=============
 * ==========================================
 *
*/

void Insect::clipWalls() {
	if (this->position.x < 0)
		position.x += this->window->getSize().x;
	else if (this->position.x > this->window->getSize().x)
		position.x -= this->window->getSize().x;
	if (this->position.y < 0)
		position.y += this->window->getSize().y;
	else if (this->position.y > this->window->getSize().y)
		position.y -= this->window->getSize().y;
}

void Insect::rotate(float angle) {
	float angleRad { VecMath::toRadians(angle) };

	// using rotation matrix
	float newX {
		VecMath::dotProduct(
			this->direction,
			sf::Vector2f { std::cos(angleRad), -1 * std::sin(angleRad) }
		)
	};
	float newY {
		VecMath::dotProduct(
			this->direction,
			sf::Vector2f { std::sin(angleRad), std::cos(angleRad) }
		)
	};
	this->direction = sf::Vector2f { newX, newY };
}

void Insect::updateSpeed(float speedDif) {
	this->speed += speedDif;
}

void Insect::update() {
	// update the position by the direction vector
	this->position += this->speed * this->direction;
	// don't let them leave the screen
	this->clipWalls();

	// set the shapes position
	this->shape.setPosition(this->position);
}

/**
 *
 * ==========================================
 * =============RENDER FUNCTIONS=============
 * ==========================================
 *
*/

// rotate the object into the direction of the direction
void Insect::renderInsect() {
	// calculate the angle between the y-axis and the direction vector
	float angle { VecMath::calculateAngle(sf::Vector2f(0.f, -1.f), this->direction) };

	// select the angle clockwise
	if (this->direction.x <= 0)
		angle = 360 - angle;
	// rotate the shape according to the angle (clockwise)
	this->shape.setRotation(angle);

	std::cout << angle << "\n";

	this->window->draw(this->shape);
}

void Insect::drawSpeedVector() {
	sf::Vertex line[] = {
		sf::Vertex(this->position),
		sf::Vertex(this->position + (10.0f * this->speed * this->direction))
	};

	this->window->draw(line, 2, sf::Lines);
}

void Insect::render() {
	this->renderInsect();
	this->drawSpeedVector();
}
