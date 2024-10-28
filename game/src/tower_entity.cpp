#include "tower_entity.h"
#include "iostream"

TowerEntity::TowerEntity(float x, float y, int width, int height, EntityType type, float attackRange, float attackDamage, EntityState state,World* worldInstance)
    : Entity(x, y, width, height, type, Right), attackRange(attackRange), attackDamage(attackDamage) ,world(worldInstance)
{

    setState(state); 
}

EntityState TowerEntity::getState() 
{
    return Entity::getState(); 
}

void TowerEntity::setState(EntityState newState)
{
    Entity::setState(newState); 
}
Entity* TowerEntity::getClosestEnemy(const std::vector<Entity*>& enemies) {
    if (enemies.empty()) {
        return nullptr; 
    }

    for (Entity* enemy : enemies) {
        float distance = Vector2Distance({ getX(), getY()}, {enemy->getX(), enemy->getY()});
        if (distance <= TowerEntity::attackRange) {
            return enemy; // Return the first enemy found within range
        }
    }
    return nullptr;// no valid enemy is found
}

void TowerEntity::tick()
{
    Entity* entity = getClosestEnemy(world->getEnemies());
    
    if (entity == NULL)
    {
        return;
    }
    EnemyEntity* closestEnemy = dynamic_cast<EnemyEntity*>(entity);

    if (closestEnemy) {
        setState(Attack);
        closestEnemy->takeDamage(attackDamage);
    }
    else {
        setState(Idle);
}
}
