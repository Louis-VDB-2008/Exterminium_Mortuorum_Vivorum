#include "Enemy.h"

class Swimmer : virtual public Enemy {
public:
    Swimmer(Vector2 pos = { 0, 0 });
    virtual ~Swimmer() = default;

    // Active la traversée des rivières
    bool canSwim() const override { return true; }

    void move(const Map& map, const Vector2& playerPos) override;
};