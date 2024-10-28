#ifndef TOWERENTITY_H
#define TOWERENTITY_H

#include "entity.h"
#include "enemy_entity.h"
#include "raylib.h"
#include "raymath.h"
#include "pubsub.h"
#include "world.h"

class TowerEntity : public Entity
{
private:
    World* world;
    float attackRange;
    float attackDamage;

public:
    TowerEntity(float x, float y, int width, int height, EntityType type, float attackRange, float attackDamage, EntityState state, World* worldInstance);

    EntityState getState();

    void setState(EntityState newState);
    Entity* getClosestEnemy(const std::vector<Entity*>& enemies);
    void tick() override;
   // bool handleCollisions() override;
    void attackEnemy(Entity* enemy);
};

#endif