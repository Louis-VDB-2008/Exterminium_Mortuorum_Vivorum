#include "Entity.h"
#include <iostream>

void Entity::DisplayStats()
{
    std::cout << "Entity" << std::endl;
    std::cout << "Life : " << life << std::endl;
    std::cout << "Attack : " << attack << std::endl;
    std::cout << std::endl;
}

void Entity::applyDamage(int value)
{
    SetLife(GetLife() - value);
}


void Entity::Attack(Entity& target)
{
        target.applyDamage(attack);
}

bool Entity::isAlive() {
    return life > 0;
}


// Geter, Setter
int Entity::GetLife() {
    return life;
}

int Entity::SetLife(int value) {
    life = value;
    if (life < 0) {
        life = 0;
    }
    return life;
}

void Entity::move() {

}