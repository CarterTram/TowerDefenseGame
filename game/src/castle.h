#ifndef CASTLE_H
#define CASTLE_H

#include "entity.h"

class Castle : public Entity {
private:
    int hp;

public:
    Castle(float x, float y, int width, int height, int hp);
    void takeDamage(int amount);
    bool isDestroyed() const;
    int getHP() const;
};

#endif
