#include "Mage.h"
#include <cstdlib>
#include "Enemy.h"
Mage::Mage(int radius) : spellRadius(radius) {}
void Mage::onCollision(Entity* other)
{
    Enemy* enemy = dynamic_cast<Enemy*>(other);
    if (enemy != nullptr && enemy->isAlive())
    {
        hp = 0;
    }
}
void Mage::onUpdate() { move(); }
void Mage::useSpecialAction() { castSpell(); }
void Mage::castSpell()
{
    const Vector2 pos = getPlayerPosition();
    for (Enemy* enemy : Enemy::getAllEnemies())
    {
        if (enemy == nullptr || !enemy->isAlive())
        {
            continue;
        }
        const Vector2 target = enemy->getPosition();
        const int dx = std::abs(target.x - pos.x);
        const int dy = std::abs(target.y - pos.y);
        if (dx <= spellRadius && dy <= spellRadius)
        {
            enemy->setAlive(false);
        }
    }
}
int Mage::getHp() const { return hp; }
const char* Mage::getClassName() const { return "Mage"; }
