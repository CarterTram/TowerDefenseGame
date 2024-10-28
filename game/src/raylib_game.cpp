#include <iostream>
#include <map>
#include "raylib.h"
#include "world.h"
#include "pubsub.h"
#include "entity_view.h"
#include "player_entity.h"
#include "tile_entity.h"

class Controller : public Subscriber
{
private:
    World world;
    std::vector<EntityView*> views;
    Texture2D background;
    void setupEntities();
    int waveNumber = 1;
    int gold = 20;
    int levelIncreaseCounter;
    float obstacleWidth = 32;
    float obstacleHeight = 32;

public:
    void gameLoop();
    void receiveMessage(std::string channel, std::string message, void* data);
};

int main(void)
{
    Controller controller;
    controller.gameLoop();
    return 0;
}

void Controller::setupEntities()
{


    int numBlocksX = 20;
    int numBlocksY = 10; 
    // Add castle at the end of the path
    world.addCastle(50, 160, 152, 148, 100);
    // First horizontal lane
    for (int i = 0; i < numBlocksX; i++)
    {
        world.addEntity(100 + i * obstacleWidth, 200, obstacleWidth, obstacleHeight, Obstacle);
    }

    // Second horizontal lane
    for (int i = 0; i < numBlocksX-3; i++)
    {
        world.addEntity(100 + i * obstacleWidth, 296, obstacleWidth, obstacleHeight, Obstacle);
    }

    // Third horizontal lane
    for (int layer = 0; layer < 3; layer++) {
        for (int i = 0; i < numBlocksX - 3; i++)
        {
            world.addEntity(192 + i * obstacleWidth, 392 + layer * obstacleHeight, obstacleWidth, obstacleHeight, Obstacle);
        }
    }
    // First vertical lane (left)
    for (int i = 0; i < numBlocksY+5; i++)
    {
        world.addEntity(100, 300 + i * obstacleHeight, obstacleWidth, obstacleHeight, Obstacle);
    }

    for (int i = 0; i < numBlocksY; i++){
 
        world.addEntity(192,488 + i * obstacleHeight, obstacleWidth, obstacleHeight, Obstacle);
    }

    // Second vertical lane (right)
    for (int i = 0; i < numBlocksY-1; i++)
    {
        world.addEntity(96+ numBlocksX*obstacleWidth, 200 + i * obstacleHeight, obstacleWidth, obstacleHeight, Obstacle);
    }
    world.addCastle(50, 160, 152, 148, 100);

}


void Controller::gameLoop()
{
    const int screenWidth = 850;
    const int screenHeight = 750;
    int spawnInterval = 200; //spawn interval maybe higher dont know yet
    int tickCount = 0;
    cout << "testing " << endl;
    std::map<KeyboardKey, PlayerAction> keyMapping = {
        {KEY_W, PlayerUp},
        {KEY_A, PlayerLeft},
        {KEY_S, PlayerDown},
        {KEY_D, PlayerRight}
    };

    PubSub::subscribe("entity", this);

    PubSub::subscribe("enemies", this);

    InitWindow(screenWidth, screenHeight, "Castle Defense");
    SetTargetFPS(60);
    background = LoadTexture("resources/background.png");
    setupEntities();
    bool gameWon = false;

    while (!WindowShouldClose())
    {
        for (auto& [key, action] : keyMapping)
        {
            if (IsKeyPressed(key))
            {
                PubSub::publish("action", "player", &action);
            }
        }
        if (gameWon && IsKeyPressed(KEY_Q)) {
            break;
        }
        if (IsKeyPressed(KEY_B)) {
            Vector2 mousePos = GetMousePosition();
            float gridX = floor(mousePos.x / obstacleWidth) * obstacleWidth;
            float gridY = floor(mousePos.y / obstacleHeight) * obstacleHeight -64; 
            cout << gridY << endl;

            // Check if gold is sufficient 
            if (gold >= 5 ) {
                world.addTower(gridX, gridY, 64, 96, Tower, 100, 2, Init, &world); 
                gold -= 5;
            }
        }
        if (IsKeyPressed(KEY_B)) {
            Vector2 mousePos = GetMousePosition();
            float gridX = floor(mousePos.x / obstacleWidth) * obstacleWidth;
            float gridY = floor(mousePos.y / obstacleHeight) * obstacleHeight - 64;

            if (gold >= 5) {
                world.addTower(gridX, gridY, 64, 96, Tower, 100, 2, Init, &world);
                gold -= 5;
            }
        }

        // Handle tile placements
        if (IsKeyPressed(KEY_D)) {
            Vector2 mousePos = GetMousePosition();
            float gridX = floor(mousePos.x / obstacleWidth) * obstacleWidth;
            float gridY = floor(mousePos.y / obstacleHeight) * obstacleHeight - 64;
            // Add a damaging tile
            if (gold >= 2) {
                world.addTile(gridX, gridY+50, 25, 25, Damage, 200, false);
                gold -= 2;
            }
        }

        if (IsKeyPressed(KEY_S)) {
            Vector2 mousePos = GetMousePosition();
            float gridX = floor(mousePos.x / obstacleWidth) * obstacleWidth;
            float gridY = floor(mousePos.y / obstacleHeight) * obstacleHeight - 64;
            // Add a slowing tile
            if (gold >= 1) {
                world.addTile(gridX, gridY+50, 25, 25, Slow, 0, false);
                gold -= 1;
            }
        }

        if (IsKeyPressed(KEY_P)) {
            Vector2 mousePos = GetMousePosition();
            float gridX = floor(mousePos.x / obstacleWidth) * obstacleWidth;
            float gridY = floor(mousePos.y / obstacleHeight) * obstacleHeight - 64;
            // Add a pushback tile
            if (gold >= 5) {
                world.addTile(gridX, gridY+50, 25, 25, PushBack, 0, false);
                gold -= 5;
            }
        }

        if (IsKeyPressed(KEY_I)) {
            Vector2 mousePos = GetMousePosition();
            float gridX = floor(mousePos.x / obstacleWidth) * obstacleWidth;
            float gridY = floor(mousePos.y / obstacleHeight) * obstacleHeight - 64;
            // Add an instant kill tile
            if (gold >= 7) {
                world.addTile(gridX, gridY +50, 25, 25, InstantKill, 200, true);
                gold -= 7;
            }
        }
    

        
        if (tickCount % spawnInterval == 0) { //spawning enemies
            world.spawnEnemies(world.getCastle());
            spawnInterval -= 3;
            levelIncreaseCounter += 1;
            if (levelIncreaseCounter % 5 == 0) {
                waveNumber++;
            }
            if (waveNumber >= 7) {
                gameWon = true; // win game
            }

        }
        
        if (!gameWon) {
            world.tick();
            tickCount++;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int x = 0; x < screenWidth; x += background.width) {
            for (int y = 0; y < screenHeight; y += background.height) {
                DrawTexture(background, x, y, BROWN);
            }
        }
        int castleCurrentHP = world.getCastle()->getHP(); // Get current castle HP
        DrawText("Castle HP: ", 10, 10, 20, BLACK);
        DrawRectangle(10, 40, 200, 20, LIGHTGRAY);
        DrawRectangle(10, 40, (200 * castleCurrentHP / 100), 20, GREEN);
        DrawText(("Wave: " + std::to_string(waveNumber)).c_str(), 10, 70, 20, BLACK);
        DrawText(("Gold: " + std::to_string(gold)).c_str(), 10, 100, 20, BLACK);

        //menu
        DrawText("Build Tower (B) - Cost: 5 Gold", 250, 30, 20, BLACK);
        DrawText("Add Damage Tile (D) - Cost: 2 Gold", 250, 60, 20, BLACK);
        DrawText("Add Slow Tile (S) - Cost: 1 Gold", 250, 90, 20, BLACK);
        DrawText("Add Pushback Tile (P) - Cost: 5 Gold", 250, 120, 20, BLACK);
        DrawText("Add Instant Kill Tile (I) - Cost: 7 Gold", 250, 150, 20, BLACK);
        if (gameWon) {
            DrawText("You won!", screenWidth / 2 - MeasureText("You won!", 40) / 2, screenHeight / 2 - 20, 40, WHITE);
            DrawText("Press ESC to exit.", screenWidth / 2 - MeasureText("Press Q to exit.", 20) / 2, screenHeight / 2 + 10, 20, BLACK);
        }

        for (EntityView* view : views)
        {
            view->draw();
        }
        for (Entity* enemy : world.getEnemies()) {
            EnemyEntity* enemyEntity = dynamic_cast<EnemyEntity*>(enemy);
            float enemyCurrentHP = enemyEntity->getHP();
            cout << enemyCurrentHP;
            float hpBarWidth = 30;
            float hpBarHeight = 5;
            Vector2 position = { enemy->getX(), enemy->getY() };
            float hpBarX = position.x + (enemy->getWidth() - hpBarWidth) / 2;
            float hpBarY = position.y - 10;

            DrawRectangle(hpBarX, hpBarY, hpBarWidth, hpBarHeight, LIGHTGRAY);
            DrawRectangle(hpBarX, hpBarY,( hpBarWidth *enemyCurrentHP/ enemyEntity->getMaxHP()), hpBarHeight, GREEN);
            DrawRectangle(hpBarX +(hpBarWidth * enemyCurrentHP / enemyEntity->getMaxHP()), hpBarY, hpBarWidth - (hpBarWidth * enemyCurrentHP / enemyEntity->getMaxHP()), hpBarHeight, RED);
        }        


        EndDrawing();
    }
    UnloadTexture(background); 

    for (EntityView* view : views)
    {
        delete view;
    }
    views.clear();

    CloseWindow();
}

void Controller::receiveMessage(std::string channel, std::string message, void* data)
{
    if (channel == "entity" || channel == "enemies")
    {
        if (message == "new")
        {
            EntityView* view = new EntityView(static_cast<Entity*>(data));
            views.push_back(view);
        }
        else if (message == "delete")
        {
            auto it = std::remove_if(views.begin(), views.end(),
                [data](EntityView* view) {
                    if (view->isViewFor(static_cast<Entity*>(data)))
                    {
                        delete view;
                        return true;
                    }
                    return false;
                });
            views.erase(it, views.end());
            cout << "erased in raylib.cpp" << endl;
            world.removeEnemy(static_cast<Entity*>(data));
            if (channel == "enemies")
                gold += 2;
        }


        
    }

}
