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

	// define triangle shape (circle with 3 corners)
	this->shape = sf::CircleShape(this->radius, 3);
	this->shape.setPosition(x, y);
	this->shape.setOrigin(this->radius, this->radius);
	this->shape.setFillColor(sf::Color::Cyan);

	this->position = sf::Vector2f { x, y };
	this->speed = sf::Vector2f { 1.f, 0.f };
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

void Insect::rotateSpeed([[maybe_unused]] float angle) {
	float angleRad { VecMath::toRadians(angle) };

	// using rotation matrix
	float newX {
		VecMath::dotProduct(
			this->speed,
			sf::Vector2f { std::cos(angleRad), -1 * std::sin(angleRad) }
		)
	};
	float newY {
		VecMath::dotProduct(
			this->speed,
			sf::Vector2f { std::sin(angleRad), std::cos(angleRad) }
		)
	};
	this->speed = sf::Vector2f { newX, newY };
}

void Insect::updateSpeed(sf::Vector2f speedDif) {
	this->speed += speedDif;
	// normalize the vector
	this->speed = this->speed / VecMath::length(this->speed);
}

void Insect::update() {
	this->shape.move(this->speed);
	this->position = shape.getPosition();
}

/**
 *
 * ==========================================
 * =============RENDER FUNCTIONS=============
 * ==========================================
 *
*/

// rotate the object into the direction of the speed
void Insect::renderInsect() {
	// calculate the angle between the y-axis and the speed vector
	float angle { VecMath::calculateAngle(sf::Vector2f(0.f, -1.f), this->speed) };

	// select the angle clockwise
	if (this->speed.x <= 0)
		angle = 360 - angle;
	// rotate the shape according to the angle (clockwise)
	this->shape.setRotation(angle);

	std::cout << angle << "\n";

	this->window->draw(this->shape);
}

void Insect::drawSpeedVector() {
	sf::Vertex line[] = {
		sf::Vertex(this->position),
		sf::Vertex(this->position + (100.0f * this->speed))
	};

	this->window->draw(line, 2, sf::Lines);
}

void Insect::render() {
	this->renderInsect();
	this->drawSpeedVector();
}
