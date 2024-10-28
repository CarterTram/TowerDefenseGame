#include <iostream>
#include <algorithm>
#include "entity.h"

Entity::Entity(float x, float y, int width, int height, EntityType type, EntityFacing facing)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->type = type;
    this->facing = facing;
    this->moving = false;
}

float Entity::getX() {
    return x;
}

float Entity::getY() {
    return y;
}

int Entity::getWidth() {
    return width;
}

int Entity::getHeight() {
    return height;
}

void Entity::setX(float x) {
    this->x = x;
}

void Entity::setY(float y) {
    this->y = y;
}

EntityType Entity::getType() {
    return type;
}

EntityFacing Entity::getFacing() {
    return facing;
}

void Entity::setFacing(EntityFacing facing) {
    this->facing = facing;
}

bool Entity::getMoving() {
    return moving;
}

void Entity::setMoving(bool moving) {
    this->moving = moving;
}

void Entity::tick() {}

void Entity::addCollision(Entity* entity) {
    collisions.push_back(entity);
}

bool Entity::handleCollisions() {
    collisions.clear();
    return false;
}

EntityState Entity::getState() {
    return state;
}

void Entity::setState(EntityState newState) {
    state = newState;
}
void Entity::setFalling(bool falling)
{
    this->falling = falling;
}
bool Entity::affectedByTiles(Entity* entity) {
    if (entity->getType() == EntityType::Enemy)
        return true;
    else
        false;
}
