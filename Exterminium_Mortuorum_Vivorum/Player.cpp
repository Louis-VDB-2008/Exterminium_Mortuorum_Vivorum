#include "Player.h"
#include <curses.h>
#include "Map.h"

int Player::readPlayerInputs() {
    const int key = getch();
    switch (key) {
    case 'z': return 1;
    case 's': return 2;
    case 'q': return 3;
    case 'd': return 4;
    case 'n': return -1;
    case 'r': return -2;
    default:  return 0;
    }
}

Vector2 Player::getDirection() { // transforme l'inputs en direction
    int key = readPlayerInputs();
    Player::specialAction = Player::analyseKey(key);
    if (key == 1) return Vector2{ 0, -1 };
    if (key == 2) return Vector2{ 0, 1 };
    if (key == 3) return Vector2{ -1, 0 };
    if (key == 4) return Vector2{ 1, 0 };
    return Vector2{ 0, 0 };
}

void Player::onCollision(Entity* other) {
    // Logique de collision à implémenter (ex: subir des dégâts si ennemi)
}

void Player::onUpdate() {
    // Logique de mise à jour à chaque frame
}

Vector2 Player::getPlayerPosition() const {
    return position;
}

void Player::setPlayerPosition(const Vector2& pos) {
    position = pos;
}

void Player::move() // recupere direction et change coordonnées
{
    Vector2 ancienPos = Player::getPlayerPosition();
    Vector2 dir = getDirection();
    position.x += dir.x;
    position.y += dir.y;
    if (!Player::canMove()) {
        Player::setPlayerPosition(ancienPos);
    }
}


bool Player::analyseKey(int key)
{
    if (key > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::canMove()
{
    Vector2 newPos = Player::getPlayerPosition();
    int newX = newPos.x;
    int newY = newPos.y;
    Map map;
    if (map.isInside(newX, newY))
    {
        return false;
    }

    return true;
}