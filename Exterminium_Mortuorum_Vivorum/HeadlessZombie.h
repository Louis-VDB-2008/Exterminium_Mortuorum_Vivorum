#pragma once
#include "Enemy.h"
class HeadlessZombie : virtual public Enemy
{
public:
    explicit HeadlessZombie(Vector2 pos = { 0, 0 });
    ~HeadlessZombie() override = default;
    void move(const Map& map, const Vector2& playerPos) override;
};
