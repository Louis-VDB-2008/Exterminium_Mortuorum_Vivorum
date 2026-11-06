#pragma once
#include "Vector2.h"
#include "Entity.h"

class Player : public Entity
{
public:
    int readPlayerInputs();
    Vector2 getDirection();
    bool analyseKey(int);
    bool canMove();
    bool specialAction;

    // Redéfinition des méthodes virtuelles pures d'Entity
    void onCollision(Entity* other) override;
    void onUpdate() override;
    void move() override;

    Vector2 getPlayerPosition() const;  // geter
    void setPlayerPosition(const Vector2& pos); // seter

private:
    Vector2 position{ 0, 0 };
};