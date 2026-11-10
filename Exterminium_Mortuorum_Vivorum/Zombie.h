#pragma once
#include "Enemy.h"
class Zombie : virtual public Enemy
{
public:
    explicit Zombie(Vector2 pos = { 0, 0 });
    ~Zombie() override = default;
    void move(const Map& map, const Vector2& playerPos) override;
};
