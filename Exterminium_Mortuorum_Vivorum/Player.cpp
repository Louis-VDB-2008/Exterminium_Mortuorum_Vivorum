#include "Player.h"
#include <curses.h>
#include "Map.h"
void Player::setMap(const Map* map) { currentMap = map; }
Vector2 Player::getPlayerPosition() const { return position; }
void Player::setPlayerPosition(const Vector2& pos) { position = pos; }
void Player::setInput(int key) { input = key; }
void Player::onCollision(Entity*) {}
void Player::onUpdate() { move(); }
void Player::useSpecialAction() {}
void Player::move()
{
    Vector2 next = position;
    switch (input)
    {
    case 'z': case 'Z': case KEY_UP: --next.y; break;
    case 's': case 'S': case KEY_DOWN: ++next.y; break;
    case 'q': case 'Q': case KEY_LEFT: --next.x; break;
    case 'd': case 'D': case KEY_RIGHT: ++next.x; break;
    default: return;
    }
    if (currentMap != nullptr && currentMap->isInside(next.x, next.y) &&
        currentMap->getTileInfo(next.x, next.y).isWalkable)
    {
        position = next;
    }
}
