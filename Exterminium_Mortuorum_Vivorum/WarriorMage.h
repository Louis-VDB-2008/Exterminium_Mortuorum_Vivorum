#pragma once
#include "Warrior.h"
#include "Mage.h"
class WarriorMage : public Warrior, public Mage
{
public:
    WarriorMage();
    void onCollision(Entity* other) override;
    void onUpdate() override;
    void useSpecialAction() override;
    int getHp() const override;
    const char* getClassName() const override;
};
