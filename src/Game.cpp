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

	this->scalarNames[0] = "Seperation";
	this->scalarValues[0] = 0.1;
	this->scalarNames[1] = "Alignment";
	this->scalarValues[1] = 0.1;
	this->scalarNames[2] = "Cohesion";
	this->scalarValues[2] = 0.01;
}

void Game::initText() {
	if (!this->font.loadFromFile("Arial.ttf")) {
		std::cout << "Error loading font \n";
	}

	for (int i { 0 }; (unsigned)i < this->scalarText.size(); i++) {
		sf::Text text;
		text.setFont(this->font);
		text.setCharacterSize(10);
		text.setFillColor(sf::Color::Black);
		text.setPosition(10, i * 15 + 10);
		this->scalarText[i] = text;
	}
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
	this->initText();
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
				// Update scalars
				// Seperation
				if (this->event.key.code == sf::Keyboard::Q)
					this->updateScalar(0, 0.01);
				if (this->event.key.code == sf::Keyboard::A)
					this->updateScalar(0, -0.01);
				// alignment
				if (this->event.key.code == sf::Keyboard::W)
					this->updateScalar(1, 0.01);
				if (this->event.key.code == sf::Keyboard::S)
					this->updateScalar(1, -0.01);
				// cohesion
				if (this->event.key.code == sf::Keyboard::E)
					this->updateScalar(2, 0.001);
				if (this->event.key.code == sf::Keyboard::D)
					this->updateScalar(2, -0.001);
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

void Game::updateScalar(int index, float amount) {
	if (this->scalarValues[index] + amount >= 0.0)
		this->scalarValues[index] += amount;
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
		insect.alignment(this->swarm, this->scalarValues[1]);
		insect.cohesion(this->swarm, this->scalarValues[2]);
		insect.seperation(this->swarm, this->scalarValues[0]);
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

std::string Game::convert_float_to_string(float number) {
	std::string str { std::to_string(number) };
	str.erase(str.find_last_not_of('0') + 1, std::string::npos);
	str.erase(str.find_last_not_of('.') + 1, std::string::npos);
	return str;
}

void Game::renderGameState() {
	for (int i { 0 }; (unsigned)i < scalarText.size(); i++) {
		scalarText[i].setString(scalarNames[i] + ": " + this->convert_float_to_string(scalarValues[i]));
		this->window->draw(scalarText[i]);
	}
}


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
	this->renderGameState();

	// tell app that window is done drawing and we can display
	this->window->display();
}
