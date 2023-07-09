#include <iostream>

#include "Game.h"

int main() {

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	// init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	// initilize game object
	Game game {};

	while (game.running()) {

		// update
		game.update();

		// render
		game.render();
	}

	return 0;
}
