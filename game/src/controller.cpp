//#include <iostream>
//#include <map>
//#include "controller.h"
//#include "raylib.h"
//#include "enemy_entity.h"
//#include "world.h"
//
//void Controller::gameLoop()
//{
//    const int screenWidth = 800;
//    const int screenHeight = 450;
//
//    map<KeyboardKey, PlayerAction> keyMapping;
//
//    keyMapping[KEY_W] = PlayerUp;
//    keyMapping[KEY_A] = PlayerLeft;
//    keyMapping[KEY_S] = PlayerDown;
//    keyMapping[KEY_D] = PlayerRight;
//    int x = 400;
//    int y = 200;
//    world.addTower(x, y, 64, 64, Tower, 200,100,Init);
//
//    PubSub::subscribe("entity", this);
//
//    InitWindow(screenWidth, screenHeight, "Tower Defense Game");
//    SetTargetFPS(60);
//
//}
//    