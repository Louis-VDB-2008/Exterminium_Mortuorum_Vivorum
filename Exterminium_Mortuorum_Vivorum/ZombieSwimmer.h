#pragma once
#include "Zombie.h"
#include "Swimmer.h"
class ZombieSwimmer : public Zombie, public Swimmer
{
public:
    explicit ZombieSwimmer(Vector2 pos = { 0, 0 });
    ~ZombieSwimmer() override = default;
    bool canSwim() const override { return Swimmer::canSwim(); }
    void move(const Map& map, const Vector2& playerPos) override;
};
