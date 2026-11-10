#include "Enemy.h"
#include <algorithm>
std::vector<Enemy*> Enemy::allEnemies;
Enemy::Enemy(Vector2 pos) : position(pos)
{
    allEnemies.push_back(this);
}
Enemy::~Enemy()
{
    auto it = std::find(allEnemies.begin(), allEnemies.end(), this);
    if (it != allEnemies.end())
    {
        allEnemies.erase(it);
    }
}
Vector2 Enemy::getPosition() const { return position; }
void Enemy::setPosition(const Vector2& pos) { position = pos; }
bool Enemy::isAlive() const { return alive; }
void Enemy::setAlive(bool state) { alive = state; }
bool Enemy::canSwim() const { return false; }
void Enemy::move() {}
void Enemy::onUpdate() {}
void Enemy::onCollision(Entity*) { alive = false; }
const std::vector<Enemy*>& Enemy::getAllEnemies() { return allEnemies; }
void Enemy::clearAllEnemies() { allEnemies.clear(); }
bool Enemy::canMove(const Map& map, const Vector2& pos) const
{
    if (!map.isInside(pos.x, pos.y))
    {
        return false;
    }
    const TileInfo& tile = map.getTileInfo(pos.x, pos.y);
    return tile.isWalkable && (tile.symbol != '~' || canSwim());
}
