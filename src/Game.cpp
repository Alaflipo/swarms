#include "Game.h"

/**
 *
 * ==========================================
 * =============PRIVATE FUNCTIONS============
 * ==========================================
 *
*/


/**
 *
 * ==========================================
 * ===============INITILIZATION==============
 * ==========================================
 *
*/

void Game::initSwarm() {

	for (int i { 0 }; i < this->swarmSize; i++) {
		float randX { static_cast<float>(rand() % static_cast<int>(this->window->getSize().x)) };
		float randY { static_cast<float>(rand() % static_cast<int>(this->window->getSize().y)) };
		Insect insect { this->window, randX, randY };
		this->swarm.push_back(insect);
	}
}

void Game::initilizeVariables() {
	this->window = nullptr;

	// Game logic
	this->swarmSize = 50;
}

void Game::initWindow() {
	this->videoMode.height = 800.0;
	this->videoMode.width = 1000.0;
	this->window = new sf::RenderWindow(this->videoMode, "Swarms");

	this->window->setFramerateLimit(100);
}

// CONSTRUCT AND DESTRUCT FUNCTION
Game::Game() {
	this->initilizeVariables();
	this->initWindow();
	this->initSwarm();
}

Game::~Game() {
	delete this->window;
}

// ACESSOR HELPER FUNCTION
bool Game::running() {
	return this->window->isOpen();
}

/**
 *
 * ==========================================
 * =============UPDATE FUNCTIONS=============
 * ==========================================
 *
*/


void Game::pollEvents() {
	// Event polling
	while (window->pollEvent(this->event)) {
		// Go trough each even typ
		switch (this->event.type) {
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->event.key.code == sf::Keyboard::Escape)
					this->window->close();
				if (this->event.key.code == sf::Keyboard::Left)
					this->updateSwarmDirection(-5.0f);
				if (this->event.key.code == sf::Keyboard::Right)
					this->updateSwarmDirection(5.0f);
				if (this->event.key.code == sf::Keyboard::Up)
					this->updateSwarmSpeed(1.0f);
				if (this->event.key.code == sf::Keyboard::Down)
					this->updateSwarmSpeed(-1.0f);
				break;
			default:
				break;
		}
	}
}

void Game::updateMousePositions() {
	/**
	 * @return void
	 *
	 * Updates the mouse positions:
	 * - mouse position relative to window (vector2i)
	*/

	// update mouse position
	// Relative to the screen: sf::Mouse::getPosition().x
	// Relative to the window: sf::Mouse::getPosition(*this->window).x

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

// updates the direction of the swarm by changing the angle (in degree)
void Game::updateSwarmDirection(float angle) {
	for (auto& insect : this->swarm) {
		insect.rotate(angle);
	}
}

void Game::updateSwarmSpeed(float speedDif) {
	for (auto& insect : this->swarm) {
		insect.updateSpeed(speedDif);
	}
}

void Game::updateSwarm() {
	for (auto& insect : this->swarm) {
		insect.seperation(this->swarm, 0.1);
		insect.alignment(this->swarm, 0.01);
		insect.cohesion(this->swarm, 0.001);
		insect.update();
	}
}

void Game::update() {
	this->pollEvents();
	this->updateMousePositions();
	this->updateSwarm();
}

/**
 *
 * ==========================================
 * =============RENDER FUNCTIONS=============
 * ==========================================
 *
*/

void Game::renderSwarm() {

	for (auto& insect : this->swarm) {
		insect.render();
	}
}

void Game::render() {
	/**
	 * @return void
	 * - clear old frame
	 * - render objects
	 * - display frame in the window
	 *
	 * Renders the game objects
	*/

	// clear old frame
	this->window->clear(sf::Color(42, 64, 82));

	// draw everything to the window
	this->renderSwarm();

	// tell app that window is done drawing and we can display
	this->window->display();
}
