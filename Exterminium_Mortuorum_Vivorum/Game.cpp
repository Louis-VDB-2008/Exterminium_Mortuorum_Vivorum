#include "Game.h"
#include "Map.h"
#include "Enemy.h"
#include "Player.h"

Game* Game::GetInstance()
{
    if (instance == nullptr) 
    {
        instance = new Game();
    }
    return instance;
}

void Game::run()
{
    Map::chargerCarte();
    Map::afficherCarte();
}
