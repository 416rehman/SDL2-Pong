#include <iostream>
#include "game/Game.h"

int main(int argc, char *argv[]) {
    Core::Game game;
    std::cout << "Hello World";
    if (game.Initialize())
    {
        game.BeginPlay();
    }

    game.Shutdown();

    return 0;
}