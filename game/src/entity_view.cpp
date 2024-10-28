#include <map>
#include <string>
#include "entity_view.h"
#include "textures.h"
#include <iostream>

struct SpriteSheetInfo
{
    string fileName;
    int numFrames = 0;
    int numRows = 0;
    map<EntityFacing, int> facings;
    map<EntityState, int> stateRows;
    map<EntityState, int> numberOfFrames; 
};

map<EntityType, SpriteSheetInfo> spriteMapping = {
    {Obstacle, {"resources/wall.png", 1, 1, {
        {Right, 0}},
        {},
        {
            {Init, 1},
            {Idle, 1},
            {Attack, 1},
            {Ruined, 1}
        }
    }},
    {CastleMain, {"resources/castle.png", 1, 1, {
        {Right, 0}},
        {},
        {
            {Init, 1},
            {Idle, 1},
            {Attack, 1},
            {Ruined, 1}
        }
    }},
    {Tower, {"resources/Sphere_Tower.png", 8, 4, {
        {Right, 0}},
        {
            {Init, 0},
            {Idle, 1},
            {Attack,2},
            {Ruined, 3}
        },
        {
            {Init, 6},
            {Idle, 8},
            {Attack, 7},
            {Ruined, 1}
        }
    }},
    {Enemy, {"resources/slime.png", 6, 1, {
        {Right, 0},
        {Left, 0},
        {Up, 0},
        {Down, 0}},
        {},
        {
            {Init, 6},
            {Idle, 6},
            {Attack, 6},
            {Ruined, 6}
        }
    }},
        {Tile, {"resources/tiles.png", 5, 5, {
        {Right, 0} 
    }, {   
        {Init, 0},
        {Idle, 1},
        {Attack, 2},
        {Ruined, 4}}, 
        {
        {Init, 1},
        {Idle, 1},
        {Attack, 1},
        {Ruined, 1}
    }}
    }

};

EntityView::EntityView(Entity* entity)
{
    this->entity = entity;
    texture = Textures::loadTexture(spriteMapping[entity->getType()].fileName);
    frame = 0;
    delay = 1;
}

bool EntityView::isViewFor(Entity* entity)
{
    return this->entity == entity;
}

void EntityView::draw()
{
    int animationDelay = 5;
    EntityState currentState = entity->getState();
    int numFrames = spriteMapping[entity->getType()].numFrames;
    //new changes
     int numberOfFrames = spriteMapping[entity->getType()].numberOfFrames[entity->getState()];
     if (numberOfFrames == NULL)
         numberOfFrames = 1;

    
    if (entity->getMoving() || entity->getType() == Tower)
    {
        delay--;

        if (delay == 0)
        {
            frame = (frame + 1) % numberOfFrames;
            delay = animationDelay;
        }
    }
    else
    {
        frame = 0;
        delay = animationDelay;
    }

    int frameWidth = texture.width / numFrames;
    int frameHeight = 1;
    int row = 0;
    
    Rectangle frameRec;
   
    
        //frameRec = { (float)frame * frameWidth, (float)row * frameWidth, (float)frameWidth, (float)frameWidth };
        //row = spriteMapping[entity->getType()].facings[entity->getFacing()];
 
        
        frameWidth = texture.width / numFrames;
        frameHeight = texture.height / spriteMapping[entity->getType()].numRows;
        row = spriteMapping[entity->getType()].stateRows[currentState];
        frameRec = { (float)frame * frameWidth,(float)row * frameHeight,(float)frameWidth, (float)frameHeight };
      
    DrawTextureRec(texture, frameRec, { entity->getX(), entity->getY() }, WHITE);
}
