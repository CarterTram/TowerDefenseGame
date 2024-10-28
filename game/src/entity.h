#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include <vector>
#include <string>

using namespace std;

enum EntityType { Cat, Obstacle, Tower, Enemy, CastleMain, BossEnemy,Tile}; // Include types
enum EntityFacing { Up, Down, Left, Right };
enum EntityState { Init, Idle, Attack, Ruined };

class Entity
{
protected:
    float x, y;
    int width, height;
    EntityType type; 
    EntityFacing facing; 
    EntityState state; 
    bool moving;
    bool falling;
    vector<Entity*> collisions; 

public:
    Entity(float x, float y, int width, int height, EntityType type, EntityFacing facing = Right);

    virtual void tick();
    virtual bool handleCollisions();

    float getX(); 
    float getY();
    int getWidth();
    int getHeight();
    void setX(float x);
    void setY(float y);
    EntityType getType();
    EntityFacing getFacing();
    void setFacing(EntityFacing facing);
    bool getMoving();
    void setMoving(bool moving);
    void setFalling(bool falling);
    void addCollision(Entity* entity);
    bool affectedByTiles(Entity* entity);
    // Getter and setter for state
    EntityState getState();
    void setState(EntityState newState);
};

#endif
