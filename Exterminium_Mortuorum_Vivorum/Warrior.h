#pragma once
#include "Player.h"
class Warrior : virtual public Player
{
public:
    explicit Warrior(int initialHp = 3);
    void takeDamage(int amount);
    void onCollision(Entity* other) override;
    void onUpdate() override;
    int getHp() const override;
    const char* getClassName() const override;
protected:
    int hp = 3;
};
