//hugo
#pragma once
#include "Vector2.h"
class Entity
{
public:
    virtual ~Entity() = default;  //destructeur

    virtual void onCollision(Entity* other) = 0;
    virtual void onUpdate() = 0;

    virtual void move() = 0;
    void applyDamage();
    bool isAlive(int);

private:
    int life = 1;
};