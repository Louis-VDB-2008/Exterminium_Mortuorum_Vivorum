#include "Zombie.h"
#include <cmath>

Zombie::Zombie(Vector2 pos)
    : Enemy(pos) {
}

void Zombie::move(const Map& map, const Vector2& playerPos) {
    if (!alive) return;

    Vector2 nextPos = position;
    int dx = playerPos.x - position.x;
    int dy = playerPos.y - position.y;

    // Tente d'abord le déplacement sur l'axe le plus éloigné du joueur
    if (std::abs(dx) >= std::abs(dy) && dx != 0) {
        nextPos.x += (dx > 0) ? 1 : -1;
    }
    else if (dy != 0) {
        nextPos.y += (dy > 0) ? 1 : -1;
    }

    // Si le premier choix est valide, on se déplace
    if (canMove(map, nextPos)) {
        position = nextPos;
    }
    // Sinon, on tente l'axe secondaire
    else {
        nextPos = position;
        if (std::abs(dx) < std::abs(dy) && dx != 0) {
            nextPos.x += (dx > 0) ? 1 : -1;
        }
        else if (dy != 0) {
            nextPos.y += (dy > 0) ? 1 : -1;
        }

        if (canMove(map, nextPos)) {
            position = nextPos;
        }
    }
}