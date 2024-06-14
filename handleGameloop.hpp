#include "handlePlayer.hpp"
#include "handleCamera.hpp"
#include "handleEnemy.hpp"  
#include "handlePowerUps.hpp"
#include "handleAudio.hpp"
#include "handleMenu.hpp"
#include <string>

void gameloop(){
    Player player; //initierar spelaren
    HealthPowerUp healthPowerUp; //initierar powerup
    Camera camera = initCamera3D(); //initierar kameran
    EnemieManager enemyManager(15); //initierar ALLA typer av fiender, kan läggas till logik senare.

    enemyManager.initEnemies(); //initierar fiender in i listan från början
    
    while(!WindowShouldClose()){         
                //playAudio();      
                checkCameraMovment(&camera, &player.position, &player.orientation); //flyttar kameran efter spelaren
                player.move(); //flyttar spelaren vid behov
                healthPowerUp.move(player.position); //flyttar powerup
                
                BeginDrawing();
                    ClearBackground(RAYWHITE);
                    BeginMode3D(camera); 
                        player.draw(); //draw player
                        healthPowerUp.draw(); //draw powerup
                        enemyManager.updateEnemies(player.position); //draw enemies
                        enemyManager.checkCollision(player.position, player.orientation); //kollar om spelaren kolliderar med fienden
                    EndMode3D();

                EndDrawing();
                DrawText(TextFormat("COINS: %i", player.coins), 10, 10, 30, GREEN);
    }
}




