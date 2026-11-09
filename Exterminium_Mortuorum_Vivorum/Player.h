#pragma once
#include "Entity.h"
#include "Vector2.h"
class Map;
class Player : public Entity
{
public:
    ~Player() override = default;
    void setMap(const Map* map);
    Vector2 getPlayerPosition() const;
    void setPlayerPosition(const Vector2& pos);
    void setInput(int key);
    void move() override;
    void onCollision(Entity* other) override;
    void onUpdate() override;
    virtual int getHp() const = 0;
    virtual const char* getClassName() const = 0;
    virtual void useSpecialAction();
protected:
    Vector2 position{ 0, 0 };
    const Map* currentMap = nullptr;
    int input = 0;
};
