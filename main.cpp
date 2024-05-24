
#include "include/raylib.h"
#include "handlePlayer.hpp"
#include "handleCamera.hpp"
#include "handleEnemy.hpp"  
#include "handlePowerUps.hpp"
#include "handleAudio.hpp"
#include <string>
int main(void)
{
    Player player; //initierar spelaren
    HealthPowerUp healthPowerUp; //initierar powerup
    Zombie zombie(5); //initierar fienden
    infantry infantry(10); //initierar fienden
    Camera camera = initCamera(); //initierar kameran
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "COOL GAME");
    InitAudioDevice();
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        playAudio();
        checkCameraMovment(&camera, &player.position); //flyttar kameran efter spelaren
        player.move(); //flyttar spelaren vid behov
        zombie.move(player.position); //flyttar fienden beroende på spelarens position
        infantry.move(player.position); //flyttar fienden beroende på spelarens position
        healthPowerUp.move(); //flyttar powerup
        player.checkCollision(infantry.getAllPosList()); //kollar om spelaren kolliderar med fienden
        player.checkCollision(zombie.getAllPosList()); //kollar om spelaren kolliderar med fienden
       
        DrawText(TextFormat("Health: %i", player.health), 80, 100, 60, RED);
        DrawText(TextFormat("Enemies left: %i", zombie.getActiveEnemies() + infantry.getActiveEnemies()), 80, 150, 60, RED);   
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera); 

                player.draw(); //draw player
                zombie.draw(); //draw enemy
                infantry.draw(); //draw enemy
                healthPowerUp.draw(); //draw powerup
                healthPowerUp.updateLine(player.position); //draw line between player and powerup

            EndMode3D();

        EndDrawing();
    }
    CloseWindow();

    return 0;
}

