
#include <vector>
#include <chrono>
#include <iostream>

#include "Game.h"
#include "StartScene.h"


// Game decleration
Jinny::Game* game = new Jinny::Game();

int main(int argc, char* args[])
{
	// Game initialization
	game->initialize(new Jinny::StartScene());

	// Main loop
	while (!(game->isGameOver()))
	{
		//auto begin = std::chrono::steady_clock::now();

		// Update Pattern	
		game->update();

		//fps
		//std::cout << 1000000 / std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count() << "fps" << std::endl;
	}

	// Close game
	game->close();

	return 0;
}