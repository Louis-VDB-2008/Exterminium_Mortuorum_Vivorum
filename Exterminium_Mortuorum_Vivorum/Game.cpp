#include "Game.h"
#include "Map.h"

Game* Game::GetInstance()
{
    if (instance == nullptr) {
        instance = new Game();
    }
    return instance;
}

void Game::run()
{
    //appeler les fonction
}
