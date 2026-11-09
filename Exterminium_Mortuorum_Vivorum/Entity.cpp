#include "Enemy.h"
#include <algorithm>

std::vector<Enemy*> Enemy::allEnemies;

Enemy::Enemy(Vector2 pos)
    : position(pos), alive(true) {
    allEnemies.push_back(this);
}

Enemy::~Enemy() {
    auto it = std::find(allEnemies.begin(), allEnemies.end(), this);
    if (it != allEnemies.end()) {
        allEnemies.erase(it);
    }
}

void Enemy::clearAllEnemies() {
    allEnemies.clear();
}

bool Enemy::canMove(const Map& map, const Vector2& pos) const {
    if (!map.isInside(pos.x, pos.y)) {
        return false;
    }

    const TileInfo& tile = map.getTileInfo(pos.x, pos.y);

    // Si la case est une rivière ('~')
    if (tile.symbol == '~') {
        return canSwim(); // Praticable uniquement si l'ennemi sait nager
    }

    // Sinon case terrestre classique
    return tile.isWalkable;
}