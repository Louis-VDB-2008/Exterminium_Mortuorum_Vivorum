#pragma once
#include <vector>
#include "Entity.h"
#include "Map.h"

class Enemy : public Entity
{
public:
    explicit Enemy(Vector2 pos = { 0, 0 });
    virtual ~Enemy();
    Enemy(const Enemy&) = delete;
    Enemy& operator=(const Enemy&) = delete;
    Vector2 getPosition() const;
    void setPosition(const Vector2& pos);
    bool isAlive() const;
    void setAlive(bool state);
    virtual bool canSwim() const;
    bool canMove(const Map& map, const Vector2& pos) const;
    virtual void move(const Map& map, const Vector2& playerPos) = 0;
    void move() override;
    void onUpdate() override;
    void onCollision(Entity* other) override;
    static const std::vector<Enemy*>& getAllEnemies();
    static void clearAllEnemies();

protected:
    Vector2 position;
    bool alive = true;

private:
    static std::vector<Enemy*> allEnemies;
};
