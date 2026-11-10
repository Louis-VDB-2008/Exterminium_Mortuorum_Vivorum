#include "HeadlessZombie.h"
#include <cstdlib>

HeadlessZombie::HeadlessZombie(Vector2 pos)
    : Enemy(pos) {
}

void HeadlessZombie::move(const Map& map, const Vector2& playerPos) {
    if (!alive) return;

    // Directions cardinales possibles : Haut, Bas, Gauche, Droite
    static const Vector2 directions[4] = {
        { 0, -1 }, // Haut
        { 0,  1 }, // Bas
        { -1,  0 }, // Gauche
        { 1,  0 }  // Droite
    };

    int randomIndex = std::rand() % 4;
    Vector2 dir = directions[randomIndex];
    Vector2 nextPos = { position.x + dir.x, position.y + dir.y };

    if (canMove(map, nextPos)) {
        position = nextPos;
    }
}