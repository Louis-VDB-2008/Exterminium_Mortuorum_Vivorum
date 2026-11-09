#pragma once
#include "Player.h"
class Mage : virtual public Player
{
public:
    explicit Mage(int radius = 1);
    void onCollision(Entity* other) override;
    void onUpdate() override;
    void useSpecialAction() override;
    void castSpell();
    int getHp() const override;
    const char* getClassName() const override;
protected:
    int hp = 1;
    int spellRadius = 1;
};
