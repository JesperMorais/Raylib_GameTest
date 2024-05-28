#include "handlePlayer.hpp"
#include "handleCamera.hpp"
#include "handleEnemy.hpp"  
#include "handlePowerUps.hpp"
#include "handleAudio.hpp"
#include "handleMenu.hpp"
#include <string>


int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "COOL GAME");
    InitAudioDevice();
    SetTargetFPS(60);             
    
    Player player; //initierar spelaren
    HealthPowerUp healthPowerUp; //initierar powerup
    Zombie zombie(5); //initierar fienden
    infantry infantry(40); //initierar fienden
    Camera camera = initCamera3D(); //initierar kameran
    Menu menu; //initierar menyn

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {   
            if(menu.getShowMenu()){ //kollar om vi ska vara inne i menyn eller inte
                menu.playMenu();
            }
            else{
                //playAudio();      
                checkCameraMovment(&camera, &player.position, &player.orientation); //flyttar kameran efter spelaren
                player.move(); //flyttar spelaren vid behov
                zombie.move(player.position); //flyttar fienden beroende på spelarens position
                infantry.move(player.position); //flyttar fienden beroende på spelarens position
                healthPowerUp.move(player.position); //flyttar powerup
                player.checkCollision(infantry.getAllPosList()); //kollar om spelaren kolliderar med fienden
                player.checkCollision(zombie.getAllPosList()); //kollar om spelaren kolliderar med fienden
            
                BeginDrawing();
                    ClearBackground(RAYWHITE);
                    BeginMode3D(camera); 
                        player.draw(); //draw player
                        zombie.draw(); //draw enemy
                        infantry.draw(); //draw enemy
                        healthPowerUp.draw(); //draw powerup
                        //healthPowerUp.updateLine(player.position); //draw line between player and powerup
                    EndMode3D();

                EndDrawing();
                DrawText(TextFormat("Enemies left: %i", zombie.getActiveEnemies() + infantry.getActiveEnemies()), 10, 60, 30, RED); 
       } 
    }
    CloseWindow();
    CloseAudioDevice();
    return 0;
}

