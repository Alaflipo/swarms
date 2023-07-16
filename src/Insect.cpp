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
	this->radiusCircle = this->radius * 5;
	this->speed = 1.0f;

	// define triangle shape (circle with 3 corners)
	this->shape = sf::CircleShape(this->radius, 3);
	this->visionCircle = sf::CircleShape(this->radiusCircle);
	this->shape.setPosition(x, y);
	this->visionCircle.setPosition(x, y);
	this->shape.setOrigin(this->radius, this->radius);
	this->visionCircle.setOrigin(this->radiusCircle, this->radiusCircle);

	int randomColor { rand() % 150 };
	this->shape.setFillColor(sf::Color(randomColor, 200, 230));
	this->visionCircle.setFillColor(sf::Color(255, 255, 255, 20));

	this->position = sf::Vector2f { x, y };
	float randX = static_cast<float>(rand() % 100) / 100.0;
	float randY = static_cast<float>(rand() % 100) / 100.0;
	this->direction = VecMath::normalize(sf::Vector2f { randX, randY });
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

sf::Vector2f Insect::getPosition() {
	return this->position;
}

sf::Vector2f Insect::getDirection() {
	return this->direction;
}

/**
 *
 * ==========================================
 * =============UPDATE FUNCTIONS=============
 * ==========================================
 *
*/

void Insect::clipWalls() {
	if (this->position.x <= 0)
		position.x += this->window->getSize().x;
	else if (this->position.x >= this->window->getSize().x)
		position.x -= this->window->getSize().x;
	if (this->position.y <= 0)
		position.y += this->window->getSize().y;
	else if (this->position.y >= this->window->getSize().y)
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

// Insects try to steer away from each other when present in radius
void Insect::seperation(std::vector<Insect>& others, float scalar = 0.01) {
	for (auto& other : others) {
		if (&other != this) {
			// if there is another insect that is close change direction
			float distance { VecMath::length(this->position - other.getPosition()) };
			if (distance < this->radiusCircle * 2) {
				// // add difference vector between the two
				sf::Vector2f normalDif { VecMath::normalize(this->position - other.getPosition()) };
				// direction change is determined by how close they are to each other (the
				// close the strong the seperation effect) and a scalar factor
				this->direction += scalar * normalDif;
			}
		}
	}
}

// Move towards the direction of the insects around
void Insect::alignment(std::vector<Insect>& others, float scalar = 0.01) {
	for (auto& other : others) {
		if (&other != this) {
			// if there is another insect that is close
			if (VecMath::distance(other.getPosition(), this->position) < this->radiusCircle * 2) {
				this->direction += scalar * other.getDirection();
			}
		}
	}
}

// move towards the average position of it's neighbours
void Insect::cohesion(std::vector<Insect>& others, float scalar = 0.001) {
	float neighbours { 0.0 };
	sf::Vector2f average_pos { 0.0, 0.0 };
	for (auto& other : others) {
		if (&other != this) {
			// if there is another insect that is close
			if (VecMath::distance(other.getPosition(), this->position) < this->radiusCircle * 2) {
				neighbours += 1.0;
				average_pos += other.getPosition();
			}
		}
	}

	// move towards the center
	if (neighbours > 0)
		this->direction += scalar * ((average_pos / neighbours) - this->position);
}

void Insect::update() {
	// Normalize the direction
	this->direction = VecMath::normalize(this->direction);
	// update the position by the direction vector
	this->position += this->speed * this->direction;
	// don't let them leave the screen
	this->clipWalls();

	// set the shapes position
	this->shape.setPosition(this->position);
	this->visionCircle.setPosition(this->position);
}

/**
 *
 * ==========================================
 * =============RENDER FUNCTIONS=============
 * ==========================================
 *
*/

// rotate the object into the direction of the direction
void Insect::drawInsect() {
	// calculate the angle between the y-axis and the direction vector
	float angle { VecMath::calculateAngle(sf::Vector2f(0.f, -1.f), this->direction) };

	// select the angle clockwise
	if (this->direction.x <= 0)
		angle = 360 - angle;
	// rotate the shape according to the angle (clockwise)
	this->shape.setRotation(angle);

	this->window->draw(this->visionCircle);
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
	this->drawSpeedVector();
	this->drawInsect();
}
