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
    Zombie zombie(15); //initierar fienden
    //infantry infantry(5); //initierar fienden
    Camera camera = initCamera3D(); //initierar kameran
    
    while(!WindowShouldClose()){         
                //playAudio();      
                checkCameraMovment(&camera, &player.position, &player.orientation); //flyttar kameran efter spelaren
                player.move(); //flyttar spelaren vid behov
                zombie.move(player.position); //flyttar fienden beroende på spelarens position
                healthPowerUp.move(player.position); //flyttar powerup
                player.checkCollision(zombie.getAllPosList()); //kollar om spelaren kolliderar med fienden
            
                BeginDrawing();
                    ClearBackground(RAYWHITE);
                    BeginMode3D(camera); 
                        player.draw(); //draw player
                        zombie.draw(); //draw enemy
                        healthPowerUp.draw(); //draw powerup
                    EndMode3D();

                EndDrawing();
                DrawText(TextFormat("Enemies left: %i", zombie.getActiveEnemies()), 10, 60, 30, RED); 
                DrawText(TextFormat("COINS: %i", player.coins), 10, 10, 30, GREEN);
    }
}




