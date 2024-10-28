#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "entity.h"
#include "castle.h"
#include "enemy_entity.h"
#include "tile_entity.h"

using namespace std;

enum PlayerAction { CreateEnemy, PlayerUp, PlayerDown, PlayerRight, PlayerLeft };

class World {
private:
    vector<Entity*> entities;
    vector<Entity*> collisions;
    vector<Entity*> deletions;
    vector<Entity*> enemies;
    Castle* castle; // variable for the castle , added using addCasltle below()
    int waveNumber;
    int spawnDelay;
    int spawnCounter;
    int spawnInterval = 500; //spawn interval maybe higher dont know yet
    int tickCount = 0;
    World* world;
    void checkCollision(Entity* entity, Entity* entity2);
;

public:
    World();
    void spawnEnemies(Castle* castle);
    void clearWorld();
    void addEntity(int x, int y, int width, int height, EntityType type);
    void addPlayer(int x, int y, int width, int height, EntityType type);
    void addTower(int x, int y, int width, int height, EntityType type, float attackRange, float attackDamage, EntityState state, World* worldInstance);
    void addCastle(float x, float y, int width, int height, int hp);
    void addEnemy(float x, float y, int width, int height, float speed, int hp, Castle* targetCastle);
    vector<Entity*> getEnemies() const;  
    void removeEnemy(Entity* enemy);
    void addTile(int x, int y, int width, int height, TileType type, float damage, bool instantKill);
    Castle* getCastle() const; 

    void tick();
};

#endif 