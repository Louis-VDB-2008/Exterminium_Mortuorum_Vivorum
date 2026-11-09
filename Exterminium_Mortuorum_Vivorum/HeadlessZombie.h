#include "Enemy.h"

class HeadlessZombie : virtual public Enemy {
public:
    HeadlessZombie(Vector2 pos = { 0, 0 });
    virtual ~HeadlessZombie() = default;

    void move(const Map& map, const Vector2& playerPos) override;
};