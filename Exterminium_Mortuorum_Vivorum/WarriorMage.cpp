#include "WarriorMage.h"
WarriorMage::WarriorMage() : Warrior(3), Mage(1) {}
void WarriorMage::onCollision(Entity* other)
{
    Warrior::onCollision(other);
}
void WarriorMage::onUpdate() { move(); }
void WarriorMage::useSpecialAction() { Mage::castSpell(); }
int WarriorMage::getHp() const { return Warrior::getHp(); }
const char* WarriorMage::getClassName() const { return "WarriorMage"; }
