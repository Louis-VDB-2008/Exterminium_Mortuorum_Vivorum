#pragma once
#include "Entity.h"
#include "Utilities.h"

class Player : public Entity
{
public:
    int readPlayerInputs();
    //Utilities::Vector2 getDirection(int);
    virtual void onUpdate() = 0;
public:
    int x;
    int y;
    bool hidden;
    int oxygene;
    int energie;
};

