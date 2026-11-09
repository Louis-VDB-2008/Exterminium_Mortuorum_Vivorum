#pragma once
class Entity
{
public:
    virtual ~Entity() = default;
    virtual void onCollision(Entity* other) = 0;
    virtual void onUpdate() = 0;
    virtual void move() = 0;
};
