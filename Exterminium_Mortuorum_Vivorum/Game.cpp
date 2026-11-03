//Louis Van den Bossche

#include "Game.h"
#include "Player.h"

#include <string>

#include <curses.h>

Game* Game::getInstance() //Singleton
{
    static Game instance;
    return &instance;
}

Game::~Game() //destructeur
{
    delete currentMap;
}

bool Game::loadLevel(int newLevel) //crer une carte par niveau est détruit l'ancienne
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

void Game::setupScreen() //intialise ncurses
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

void Game::drawCharacters() const // met les personages sur la carte
{
    const Vector2 player = currentMap->getPlayerSpawn();
    attron(COLOR_PAIR(1));
    mvaddch(player.y, player.x, 'H');
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(3));
    for (const Vector2& enemy : currentMap->getEnemySpawns())
    {
        mvaddch(enemy.y, enemy.x, 'X');
    }
    attroff(COLOR_PAIR(3));
}

void Game::drawGame() const // afiche la carte
{
    erase();
    currentMap->drawMap();
    drawCharacters();
    mvprintw(currentMap->getHeight() + 1, 0,
        "Niveau : %d  N : suivant  R : quitter", level);
    refresh();
}

void Game::run() // boucle de jeux
{
    setupScreen();
    bool gameOver = !loadLevel(level);
    while (!gameOver)
    {
        drawGame();
        //Player::readPlayerInputs();
        const int key = getch();
        if (key == 'r' || key == 'R' || key == 27)
        {
            gameOver = true;
        }
        else if (key == 'n' || key == 'N')
        {
            gameOver = !loadLevel(level + 1);
        }
    }
    endwin();
}
