#include "Zombie.h"
#include "Swimmer.h"

class ZombieSwimmer : public Zombie, public Swimmer {
public:
    ZombieSwimmer(Vector2 pos = { 0, 0 });
    virtual ~ZombieSwimmer() = default;

    // Récupère la capacité de nager de Swimmer
    bool canSwim() const override { return Swimmer::canSwim(); }

    // Récupère la logique d'IA du Zombie
    void move(const Map& map, const Vector2& playerPos) override {
        Zombie::move(map, playerPos);
    }
};