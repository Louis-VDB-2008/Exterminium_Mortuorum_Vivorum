//Louis Van den Bossche

#pragma once

#include "Map.h"

class Game
{
public:
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    ~Game(); // destructeur
    static Game* getInstance(); //  singleton
    bool loadLevel(int newLevel);
    void run();

private:
    Game() = default;
    void setupScreen();
    void drawCharacters() const;
    void drawGame() const;

    Map* currentMap = nullptr;
    int level = 1;
    static constexpr int MAX_LEVEL = 4;
};
