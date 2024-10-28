    #include "enemy_entity.h"
    #include "raylib.h"
    #include "iostream"
    #include "stdlib.h"
    EnemyEntity::EnemyEntity(float x, float y, int width, int height, float speed, int hp, Castle* castle)
        : Entity(x, y, width, height, EntityType::Enemy), speed(speed), hp(hp), targetCastle(castle)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->type = EntityType::Enemy;
        Entity::state = EntityState::Attack;
        this->Maxhp = hp;
    }
    EnemyEntity::EnemyEntity(float x, float y, int width, int height, float speed, int hp, Castle* castle, bool isBoss)
        : Entity(x, y, width, height, EntityType::BossEnemy), speed(speed), hp(hp), targetCastle(castle)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->type = EntityType::BossEnemy;
    
    }
    void EnemyEntity::takeDamage(int damage) {
        hp -= damage;
        if (hp <= 0) {
            hp = 0;
            isDead = true;
        }
    }
    void EnemyEntity::setSpeed(int speed) {
        this->speed = speed;
    }

    int EnemyEntity::getHP() const {
        return hp;
    }

    int EnemyEntity::getMaxHP() const {
        return Maxhp;
    }

    void EnemyEntity::tick()
    {
        if (isDead) {
          
            PubSub::publish("enemies", "delete", this);
            delete this;
            return;
   
        }
        setMoving(true);
        y -= yspeed;
        if (lastDirection == Direction::Left) {
            x += speed;
        }
        if (lastDirection == Direction::Right) {
            x -= speed;
        }

        if (turningNeeded) {
            if (lastDirection == Direction::Right) {

                lastDirection = Direction::Left;
                cout << "left" << endl;
            }
            else if (lastDirection == Direction::Left) {

                lastDirection = Direction::Right;
                cout << "right" << endl;
            }
            else {
                lastDirection = Direction::Right; 
                cout << "Right" << endl;
            }
        
        }
        turningNeeded = false;
    }

    bool EnemyEntity::handleCollisions()
    {
        for (Entity* entity : collisions) {
            if (entity->getType() == CastleMain) {
                targetCastle->takeDamage(15);
                isDead = true;
                return false;
            }
            else if (entity->getType() == Obstacle) {
                int xDistance = abs(getX() - entity->getX());
                int yDistance = abs(getY() - entity->getY());

                if (xDistance > yDistance) {
                    if (x < entity->getX()) {
                        setX(getX() -2 );
                        yspeed = 2;
                        speed = 0;
                    }
                    else {
                        setX(getX() + 2);
                        yspeed = 2;
                        speed = 0;
                    }
                }
                else {
                    turningNeeded = true;
                    if (y < entity->getY()) {
                        setY(getY() - (2));
                        yspeed = 0;
                        speed = 2;
                    }
                    else
                    {
                        yspeed = 0;
                        speed = 2;
                        setY(getY() + (2));
                    }
                }
            }
    

        }
    

        collisions.clear();
        return false;
    }
    //bool EnemyEntity::handleCollisions(vector<Entity*> obstacles)
    //{
    //    for (Entity* obstacle : obstacles) {
    //        if (x < obstacle->getX() + obstacle->getWidth() &&
    //            x + width > obstacle->getX() &&
    //            y < obstacle->getY() + obstacle->getHeight() &&
    //            y + height > obstacle->getY()) {
    //            return true;
    //        }
    //    }
    //    return false;
    //}

    //bool EnemyEntity::handleCollisions()
    //{
    //    for (Entity* entity : collisions) {
    //        if (entity->getType() == Obstacle) {
    //            path.clear();
    //            findPath(targetCastle->getX(), targetCastle->getY(), collisions);
    //            return true;
    //        }
    //    }
    //
    //    collisions.clear();
    //    return false;
    //}

    //void EnemyEntity::findPath(float targetX, float targetY, vector<Entity*> collisions)
    //{
    //    Vector2 currentPos = { x, y };
    //
    //    if (currentPos.x == targetX && currentPos.y == targetY) return;
    //
    //    vector<Vector2> directions = { {0, speed}, {speed, 0}, {0, -speed}, {-speed, 0} };
    //
    //    for (auto dir : directions) {
    //        Vector2 nextPos = { currentPos.x + dir.x, currentPos.y + dir.y };
    //
    //        if (!handleCollisions() && isValidPosition(nextPos)) {
    //            path.push_back(nextPos);
    //            if (nextPos.x == targetX && nextPos.y == targetY) return; // Reached target
    //            //do something to do dmg to the castle;
    //            findPath(targetX, targetY, collisions);
    //            if (!path.empty()) return;
    //        }
    //    }
    //}
    //
    //bool EnemyEntity::isValidPosition(Vector2 position)
    //{
    //    Rectangle rec = { position.x, position.y, width, height };
    //    for (Entity* obstacle : collisions) {
    //        Rectangle obstacleRec = { obstacle->getX(), obstacle->getY(), obstacle->getWidth(), obstacle->getHeight() };
    //        if (CheckCollisionRecs(rec, obstacleRec)) {
    //            return false; 
    //        }
    //    }
    //    return true; // Valid position collision return false
    //}
    //
    //void EnemyEntity::followPath()
    //{
    //    if (!path.empty()) {
    //        Vector2 nextPos = path.front();
    //        x = nextPos.x;
    //        y = nextPos.y;
    //        path.erase(path.begin());
    //    }
    //}
