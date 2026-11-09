#include "ZombieSwimmer.h"
ZombieSwimmer::ZombieSwimmer(Vector2 pos)
    : Enemy(pos), Zombie(pos), Swimmer(pos)
{
}
void ZombieSwimmer::move(const Map& map, const Vector2& playerPos)
{
    Zombie::move(map, playerPos);
}
