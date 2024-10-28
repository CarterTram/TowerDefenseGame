#include <iostream>
#include "player_entity.h"
#include "world.h"

#include <iostream>

PlayerEntity::PlayerEntity(float x, float y, int width, int height, EntityType type)
    : Entity(x, y, width, height, type)
{
    PubSub::subscribe("action", this);

    movementCountdown = 0;
    targetX = 0;
    targetY = 0;
    speedX = 0;
    speedY = 0;
}

void PlayerEntity::tick()
{
    if (movementCountdown > 0)
    {
        movementCountdown--;

        if (movementCountdown == 0)
        {
            setMoving(false);
            setX(targetX);
            setY(targetY);
        }
        else
        {
            setX(getX() + speedX);
            setY(getY() + speedY);
        }
    }
}

void PlayerEntity::receiveMessage(string channel, string message, void* data)
{
    if (channel == "action" && message == "player")
    {
        PlayerAction* action = (PlayerAction*)data;

        if (*action == PlayerRight)
        {
            targetX = getX() + 32;
            targetY = getY();
            speedX = 32.0 / 60.0;
            speedY = 0;
            setMoving(true);
            setFacing(Right);
            movementCountdown = 60;
        }

        if (*action == PlayerLeft)
        {
            targetX = getX() - 32;
            targetY = getY();
            speedX = -32.0 / 60.0;
            speedY = 0;
            setMoving(true);
            setFacing(Left);
            movementCountdown = 60;
        }

        if (*action == PlayerUp)
        {
            targetX = getX();
            targetY = getY() - 32;
            speedX = 0;
            speedY = -32.0 / 60.0;
            setMoving(true);
            setFacing(Up);
            movementCountdown = 60;
        }

        if (*action == PlayerDown)
        {
            targetX = getX();
            targetY = getY() + 32;
            speedX = 0;
            speedY = 32.0 / 60.0;
            setMoving(true);
            setFacing(Down);
            movementCountdown = 60;
        }
    }
}

bool PlayerEntity::handleCollisions()
{
    for (Entity* entity : collisions)
    {
        if (entity->getType() == Obstacle)
        {
            setMoving(false);
            movementCountdown = 0;

            setX(getX() - speedX);
            setY(getY() - speedY);
        }
    }

    collisions.clear();
    return false;
}