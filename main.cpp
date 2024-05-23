
#include "include/raylib.h"
#include "handlePlayer.hpp"
#include "handleCamera.hpp"
#include "handleEnemy.hpp"  
#include <string>
int main(void)
{
    Camera camera = { 0 }; // Define the camera to look into our 3d world
    Player player;
    Enemy enemy;
    camera.position = { 0.0f, 10.0f, 10.0f };  
    camera.target = { 0.0f, 0.0f, 0.0f };    
    camera.up = { 0.0f, 1.0f, 0.0f };    
    camera.fovy = 70.0f;                               // Field-of-view Y  
    camera.projection = CAMERA_PERSPECTIVE;          // Camera mode type

    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "test drawtext");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        player.checkIfMovePlayer(); //fungerar
        checkCameraMovment(&camera, &player.position); //fungerar
        enemy.moveEnemy();

        if(player.checkCollision(enemy.getEnemyPosList(), player.position)){
            DrawText("Collision", 200, 200, 20, RED);
            if (player.hasCollided == false){
                player.health--;
            }
            player.hasCollided = true;    
        }else
            player.hasCollided = false;
        

        DrawText(TextFormat("Health: %i", player.health), 80, 100, 60, RED);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera); 

                player.drawPlayer(); //draw player
                enemy.drawEnemy(); //draw enemy

            EndMode3D();

        EndDrawing();

    }

    CloseWindow();

    return 0;
}

