#include <iostream>
#include <cstdlib>
#include <ctime>
#include "world.h"
#include "player_entity.h"
#include "tower_entity.h"
#include "enemy_entity.h"

World::World() {
    srand(time(NULL));
    waveNumber = 1;
    castle = nullptr; 
}

void World::tick() {
    for (Entity* entity : entities)
        entity->tick();

    collisions.clear();
    for (Entity* entity : entities) {
        if (entity->getMoving()) {
            for (Entity* entity2 : entities) {
                if (entity != entity2) {
                    checkCollision(entity, entity2);
                }
            }
        }
    }

    deletions.clear();
    //tile logic maybe crashing
    //separation of new code
    for (Entity* entity : collisions) {
        if (entity->handleCollisions())
            deletions.push_back(entity);
    }

    for (Entity* entity : deletions) {
        auto result = find(entities.begin(), entities.end(), entity);
        if (result != entities.end())
            entities.erase(result);

        PubSub::publish("entity", "delete", entity);
        delete entity;
    }
}

void World::checkCollision(Entity* entity, Entity* entity2) {
    Rectangle rec1 = { entity->getX(), entity->getY(), entity->getWidth(), entity->getHeight() };
    Rectangle rec2 = { entity2->getX(), entity2->getY(), entity2->getWidth(), entity2->getHeight() };

    if (CheckCollisionRecs(rec1, rec2)) {
        entity->addCollision(entity2);
        if (find(collisions.begin(), collisions.end(), entity) == collisions.end())
            collisions.push_back(entity);

        if (!entity2->getMoving()) {
            entity2->addCollision(entity);
            if (find(collisions.begin(), collisions.end(), entity2) == collisions.end())
                collisions.push_back(entity2);
        }
    }
}

void World::clearWorld() {
    for (Entity* entity : entities) {
        PubSub::publish("entity", "delete", entity);
        delete entity;
    }
    entities.clear();
}

void World::addEntity(int x, int y, int width, int height, EntityType type) {
    Entity* entity = new Entity(x, y, width, height, type);
    PubSub::publish("entity", "new", entity);
    entities.push_back(entity);
}

void World::addPlayer(int x, int y, int width, int height, EntityType type) {
    Entity* entity = new PlayerEntity(x, y, width, height, type);
    PubSub::publish("entity", "new", entity);
    entities.push_back(entity);
}

void World::addTower(int x, int y, int width, int height, EntityType type, float attackRange, float attackDamage, EntityState state, World* worldInstance) {
    Entity* tower = new TowerEntity(x, y, width, height, type, attackRange, attackDamage, state, worldInstance);
    PubSub::publish("entity", "new", tower);
    entities.push_back(tower);
}

void World::addCastle(float x, float y, int width, int height, int hp) {
    this->castle = new Castle(x, y, width, height, hp); 
    PubSub::publish("entity", "new", this->castle);
    entities.push_back(this->castle);
}

void World::addEnemy(float x, float y, int width, int height, float speed, int hp, Castle* targetCastle) {
    Entity* enemy = new EnemyEntity(x, y, width, height, speed, hp, targetCastle);
    PubSub::publish("entity", "new", enemy);
    entities.push_back(enemy);
    enemies.push_back(enemy);
}

Castle* World::getCastle() const { 
    return castle;
}
vector<Entity*> World::getEnemies() const{
    return enemies;
}
void World::removeEnemy(Entity* enemy) {
    entities.erase(std::remove(entities.begin(), entities.end(), enemy), entities.end());
    cout << "entity erased in world" << endl;
    enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
}
void World::addTile(int x, int y, int width, int height, TileType type, float damage, bool instantKill) {
    Entity* tile = new TileEntity(x, y, width, height, type, damage,instantKill);
    PubSub::publish("entity", "new", tile);
    entities.push_back(tile);
}


void World::spawnEnemies(Castle*castle) {
        float spawnX = 150;
        float spawnY = 650;
        int enemyWidth = 48;
        int enemyHeight = 48;
        float speed = 2.0f;
        int hp = 700;
        addEnemy(spawnX, spawnY, enemyWidth, enemyHeight, speed, hp, castle);       

}

