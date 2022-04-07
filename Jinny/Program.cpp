#include <chrono>
#include <iostream>

#include "Game.h"
#include "StartScene.h"
#include "PongGameScene.h"


// Main loop
int main(int argc, char* args[])
{
    // Initialisation of game
    relic::Game game{ new relic::pong::PongGameScene() };

    // Game loop
    while (!(game.isGameOver()))
    {
        //auto begin = std::chrono::steady_clock::now();

        // Update Pattern
        game.update();

        //fps
        //std::cout << 1000000 / std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count() << "fps" << std::endl;
    }

    return 0;
}