#include "Enemy.h"

class Zombie : virtual public Enemy {
public:
    Zombie(Vector2 pos = { 0, 0 });
    virtual ~Zombie() = default;

    void move(const Map& map, const Vector2& playerPos) override;
};#pragma once
