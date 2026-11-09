// Louis Van den Bossche

#pragma once

#include "Map.h"
#include "Player.h"

class Game
{
public:
    Game(const Game&) = delete; // singleton
    Game& operator=(const Game&) = delete;
    ~Game(); // destructeur
    static Game* getInstance();
    bool loadLevel(int newLevel);
    void run();
    bool gameOver();

private:
    Game() = default; // singleton
    void setupScreen(); // ncurses
    void drawCharacters(const Vector2& playerPos) const; // affiche les personages sur la map
    void drawGame(const Vector2& playerPos) const; // affiche la map

    Map* currentMap = nullptr;
    int level = 1;
    static constexpr int MAX_LEVEL = 4; // en vie que pendant la classe et constante, voir cours
};