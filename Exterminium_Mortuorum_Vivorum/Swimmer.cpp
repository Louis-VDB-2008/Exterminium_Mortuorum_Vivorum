#include "Swimmer.h"

Swimmer::Swimmer(Vector2 pos)
    : Enemy(pos) {
}

void Swimmer::move(const Map& map, const Vector2& playerPos) {
    // Si la classe Swimmer est utilisée seule (déplacement de base)
}