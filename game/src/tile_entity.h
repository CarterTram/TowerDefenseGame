#ifndef TILE_ENTITY_H
#define TILE_ENTITY_H

#include "entity.h"
#include "tile_type.h"

class TileEntity : public Entity {
public:
    TileType type;
    float damage;
    float slowFactor;
    float pushBack ;
    bool instantKill;

    TileEntity(int x, int y, int width, int height, TileType type, float damage = 0, bool instantKill = false);
    bool handleCollisions();
    void applyEffects(Entity* target);
};

#endif
