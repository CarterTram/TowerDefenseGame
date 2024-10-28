#include "tile_entity.h"
#include "enemy_entity.h"
#include <iostream>
TileEntity::TileEntity(int x, int y, int width, int height, TileType type, float damage, bool instantKill)
    : Entity(x, y, width, height, Tile){
    this->type = type,
        this->damage = damage,
        this->instantKill = instantKill;
    switch (type) {
    case Damage: TileEntity::setState(Attack);
        break;
    case Slow: TileEntity::setState(Init);
        break;
    case PushBack: TileEntity::setState(Ruined);
        break;
    case InstantKill: TileEntity::setState(Idle);
        break;

    }


}
void TileEntity::applyEffects(Entity* target) {
    EnemyEntity* enemy = dynamic_cast<EnemyEntity*>(target);
    if (enemy) {
        switch (type) {
        case Damage:
            enemy->takeDamage(damage);
            break;

        case Slow:
            enemy->setSpeed(0.5);
            break;

        case PushBack:
            enemy->setX(125);
            enemy->setY(650);
            break;

        case InstantKill:
            enemy->takeDamage(enemy->getHP());
            cout << "is this working" << endl;
            break;

        default:
            break;
        }
    }
}
bool TileEntity::handleCollisions() {
    for (Entity* entity : collisions) {
        if (entity->getType() == Enemy) {
            applyEffects(entity);
            return true;
        }
        else
            return false;
    }
    return false;
}