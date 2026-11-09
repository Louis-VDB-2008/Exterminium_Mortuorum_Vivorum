#include "Warrior.h"
#include "Enemy.h"
Warrior::Warrior(int initialHp) : hp(initialHp) {}
void Warrior::takeDamage(int amount)
{
    hp -= amount;
    if (hp < 0)
    {
        hp = 0;
    }
}
void Warrior::onCollision(Entity* other)
{
    Enemy* enemy = dynamic_cast<Enemy*>(other);
    if (enemy != nullptr && enemy->isAlive())
    {
        enemy->setAlive(false);
        takeDamage(1);
    }
}
void Warrior::onUpdate() { move(); }
int Warrior::getHp() const { return hp; }
const char* Warrior::getClassName() const { return "Warrior"; }
