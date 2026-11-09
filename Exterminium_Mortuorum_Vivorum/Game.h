#pragma once
#include <memory>
#include <vector>
#include "Map.h"
class Enemy;
class Player;
class Game
{
public:
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    ~Game();
    static Game* getInstance();
    bool loadLevel(int newLevel);
    void run();
private:
    Game() = default;
    void setupScreen();
    bool chooseClass();
    void evolvePlayer();
    void drawGame() const;
    void checkCollisions();
    void moveEnemies();
    void spawnEnemies();
    void playTurn(int key);
    bool nextLevel();
    std::unique_ptr<Map> currentMap;
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    int level = 1;
    static constexpr int MAX_LEVEL = 4;
};
