#ifndef ENEMY_ENTITY_H
#define ENEMY_ENTITY_H

#include "entity.h"
#include "castle.h"
#include "pubsub.h"
#include <world.h>

class EnemyEntity : public Entity {
private:
    enum class Direction { None, Right, Left };
    Direction lastDirection = Direction::None;
    float speed;
    int hp;
    int Maxhp;
    bool turningNeeded;
    float yspeed = 2;
    Castle* targetCastle;
    std::vector<Vector2> path;
    bool isDead = false;

public:
    EnemyEntity(float x, float y, int width, int height, float speed, int hp, Castle* castle);
    EnemyEntity(float x, float y, int width, int height, float speed, int hp, Castle* castle, bool isBoss);
    void tick() override;
    void takeDamage(int damage);

    int getHP() const;
    int getMaxHP() const;

 /*   bool handleCollisions(std::vector<Entity*> obstacles);*/
    bool handleCollisions();
    void findPath(float targetX, float targetY, std::vector<Entity*> obstacles);
    void followPath();
    void setSpeed(int speed);
    bool isValidPosition(Vector2 position);
};

#endif
