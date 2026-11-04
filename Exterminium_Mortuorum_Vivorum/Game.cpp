// Louis Van den Bossche

#include "Game.h"
#include "Player.h"
#include <string>
#include <curses.h>
#include <iostream>

Game* Game::getInstance() // Singleton
{
    static Game instance;
    return &instance;
}

Game::~Game() // destructeur
{
    delete currentMap;
}

bool Game::gameOver()
{
    Player player;
    if (!player.specialAction)
    {
        return true;
    }
    return false;
}

bool Game::loadLevel(int newLevel) // Charge le niveau
{
    if (newLevel < 1 || newLevel > MAX_LEVEL)
    {
        return false;
    }
    Map* newMap = new Map;
    const std::string fileName = "map/Niveau" + std::to_string(newLevel) + ".txt";
    if (!newMap->loadMap(fileName))
    {
        delete newMap;
        return false;
    }
    delete currentMap;
    currentMap = newMap;
    level = newLevel;
    return true;
}

void Game::setupScreen() // ncurses
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
}

void Game::drawCharacters(const Vector2& playerPos) const // affiche les personage sur la map
{
    attron(COLOR_PAIR(1));
    mvaddch(playerPos.y, playerPos.x, 'H');
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(3));
    for (const Vector2& enemy : currentMap->getEnemySpawns())
    {
        mvaddch(enemy.y, enemy.x, 'X');
    }
    attroff(COLOR_PAIR(3));
}

void Game::drawGame(const Vector2& playerPos) const // affiche la map
{
    erase();
    currentMap->drawMap();
    drawCharacters(playerPos);
    mvprintw(currentMap->getHeight() + 1, 0,
        "Niveau : %d  N : suivant  R : quitter", level);
    refresh();
}

void Game::run() // lance le jeu
{
    setupScreen();
    bool gameOver = !loadLevel(level);

    Player player; // créer une instance player
    if (!gameOver)
    {
        player.setPlayerPosition(currentMap->getPlayerSpawn()); // intialise la position du joueur
    }

    while (!gameOver)
    {
        drawGame(player.getPlayerPosition());
        player.move();
    }
    endwin();
}