#include "Game.h"
#include <curses.h>
#include <cstdlib>
#include <string>
#include "Enemy.h"
#include "HeadlessZombie.h"
#include "Mage.h"
#include "Player.h"
#include "Warrior.h"
#include "WarriorMage.h"
#include "Zombie.h"
#include "ZombieSwimmer.h"
Game::~Game() = default;
Game* Game::getInstance()
{
    static Game instance;
    return &instance;
}
bool Game::loadLevel(int newLevel)
{
    if (newLevel < 1 || newLevel > MAX_LEVEL)
    {
        return false;
    }
    std::unique_ptr<Map> next(new Map);
    const std::string path = "map/Niveau" + std::to_string(newLevel) + ".txt";
    if (!next->loadMap(path))
    {
        return false;
    }
    enemies.clear();
    currentMap = std::move(next);
    level = newLevel;
    spawnEnemies();
    if (player != nullptr)
    {
        player->setMap(currentMap.get());
        player->setPlayerPosition(currentMap->getPlayerSpawn());
    }
    return true;
}
void Game::spawnEnemies()
{
    for (const Vector2& spawn : currentMap->getEnemySpawns())
    {
        if (level == 1) { enemies.emplace_back(new HeadlessZombie(spawn)); }
        else if (level == 2) { enemies.emplace_back(new Zombie(spawn)); }
        else { enemies.emplace_back(new ZombieSwimmer(spawn)); }
    }
}
void Game::setupScreen()
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
bool Game::chooseClass()
{
    erase();
    mvprintw(1, 2, "Choix : 1 Warrior (3 PV) / 2 Mage (1 PV) / R quitter");
    refresh();
    int key = 0;
    while (key != '1' && key != '2')
    {
        key = getch();
        if (key == 'r' || key == 'R' || key == 27) { return false; }
    }
    if (key == '1') { player.reset(new Warrior); }
    else { player.reset(new Mage); }
    return true;
}
void Game::evolvePlayer()
{
    const Vector2 pos = player->getPlayerPosition();
    player.reset(new WarriorMage);
    player->setMap(currentMap.get());
    player->setPlayerPosition(pos);
    erase();
    mvprintw(2, 2, "Evolution : WarriorMage !");
    mvprintw(4, 2, "Appuie sur une touche pour continuer.");
    refresh();
    getch();
}
void Game::drawGame() const
{
    erase();
    currentMap->drawMap();
    attron(COLOR_PAIR(3));
    for (const auto& enemy : enemies)
    {
        if (!enemy->isAlive()) { continue; }
        const Vector2 pos = enemy->getPosition();
        mvaddch(pos.y, pos.x, 'X');
    }
    attroff(COLOR_PAIR(3));
    const Vector2 pos = player->getPlayerPosition();
    attron(COLOR_PAIR(1));
    mvaddch(pos.y, pos.x, 'H');
    attroff(COLOR_PAIR(1));
    mvprintw(currentMap->getHeight() + 1, 0,
        "Niveau %d | %s | PV %d | ZQSD/fleches | E sort | R quitter",
        level, player->getClassName(), player->getHp());
    refresh();
}
void Game::checkCollisions()
{
    const Vector2 pos = player->getPlayerPosition();
    for (auto& enemy : enemies)
    {
        const Vector2 target = enemy->getPosition();
        if (enemy->isAlive() && pos.x == target.x && pos.y == target.y)
        {
            player->onCollision(enemy.get());
        }
    }
}
void Game::moveEnemies()
{
    const Vector2 playerPos = player->getPlayerPosition();
    for (auto& enemy : enemies)
    {
        if (!enemy->isAlive()) { continue; }
        const Vector2 before = enemy->getPosition();
        enemy->move(*currentMap, playerPos);
        const Vector2 after = enemy->getPosition();
        for (const auto& other : enemies)
        {
            if (other.get() == enemy.get() || !other->isAlive()) { continue; }
            const Vector2 occupied = other->getPosition();
            if (after.x == occupied.x && after.y == occupied.y)
            {
                enemy->setPosition(before);
                break;
            }
        }
        checkCollisions();
        if (player->getHp() <= 0) { return; }
    }
}
void Game::playTurn(int key)
{
    if (key == 'e' || key == 'E')
    {
        player->useSpecialAction();
    }
    else
    {
        player->setInput(key);
        player->onUpdate();
    }
    checkCollisions();
    if (player->getHp() > 0)
    {
        moveEnemies();
    }
}
bool Game::nextLevel()
{
    const Vector2 pos = player->getPlayerPosition();
    const Vector2 exit = currentMap->getExit();
    if (pos.x != exit.x || pos.y != exit.y) { return true; }
    if (level == MAX_LEVEL) { return false; }
    const int newLevel = level + 1;
    if (!loadLevel(newLevel)) { return false; }
    if (newLevel == 3) { evolvePlayer(); }
    return true;
}
void Game::run()
{
    setupScreen();
    if (!chooseClass() || !loadLevel(1)) { endwin(); return; }
    bool running = true;
    while (running && player->getHp() > 0)
    {
        drawGame();
        const int key = getch();
        if (key == 'r' || key == 'R' || key == 27) { break; }
        if (key != 'e' && key != 'E' && key != 'z' && key != 'Z' &&
            key != 'q' && key != 'Q' && key != 's' && key != 'S' &&
            key != 'd' && key != 'D' && key != KEY_UP && key != KEY_DOWN &&
            key != KEY_LEFT && key != KEY_RIGHT) {
            continue;
        }
        playTurn(key);
        if (player->getHp() > 0) { running = nextLevel(); }
    }
    erase();
    if (player->getHp() <= 0) { mvprintw(2, 2, "Game Over !"); }
    else if (!running && level == MAX_LEVEL) { mvprintw(2, 2, "Victoire !"); }
    else { mvprintw(2, 2, "Fin de partie."); }
    refresh();
    getch();
    endwin();
}
