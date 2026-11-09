
#include "Entity.h"
#include "Map.h"
#include <vector>

class Enemy : public Entity {
protected:
    Vector2 position;
    bool alive;

    static std::vector<Enemy*> allEnemies;

public:
    Enemy(Vector2 pos = { 0, 0 });
    virtual ~Enemy();

    Vector2 getPosition() const { return position; }
    void setPosition(const Vector2& pos) { position = pos; }

    bool isAlive() const { return alive; }
    void setAlive(bool state) { alive = state; }

    // Capacité de nager (false par défaut)
    virtual bool canSwim() const { return false; }

    // Validation du déplacement (prend en compte la rivière et la capacité de nager)
    bool canMove(const Map& map, const Vector2& pos) const;

    virtual void move(const Map& map, const Vector2& playerPos) = 0;

    static const std::vector<Enemy*>& getAllEnemies() { return allEnemies; }
    static void clearAllEnemies();
};