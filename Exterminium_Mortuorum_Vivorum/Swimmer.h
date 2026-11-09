#pragma once
#include "Enemy.h"
class Swimmer : virtual public Enemy
{
public:
    explicit Swimmer(Vector2 pos = { 0, 0 });
    ~Swimmer() override = default;
    bool canSwim() const override { return true; }
    void move(const Map& map, const Vector2& playerPos) override;
};
