
#include "include/raylib.h"
#include "handlePlayer.hpp"
#include "handleCamera.hpp"
#include "handleEnemy.hpp"  
#include <string>
int main(void)
{
    Player player; //initierar spelaren
    Enemies enemies; //initierar fienden
    Camera camera = initCamera(); //initierar kameran

    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "COOL GAME");
 
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        checkCameraMovment(&camera, &player.position); //flyttar kameran efter spelaren
        player.move(); //flyttar spelaren vid behov
        enemies.move(); //flyttar fienden
        player.checkCollision(enemies.getEnemyPosList()); //kollar om spelaren kolliderar med fienden
       
        DrawText(TextFormat("Health: %i", player.health), 80, 100, 60, RED);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera); 

                player.draw(); //draw player
                enemies.draw(); //draw enemy

            EndMode3D();

        EndDrawing();

    }
    CloseWindow();

    return 0;
}

