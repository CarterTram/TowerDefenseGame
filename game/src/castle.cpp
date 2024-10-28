#include "castle.h"

Castle::Castle(float x, float y, int width, int height, int hp)
    : Entity(x, y, width, height, EntityType::CastleMain), hp(hp) {}

void Castle::takeDamage(int amount)
{
    hp -= amount;
}

bool Castle::isDestroyed() const
{
    return hp <= 0;
}

int Castle::getHP() const
{
    return hp;
}
