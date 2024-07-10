#include "handlePlayer.hpp"
#include "handleCamera.hpp"
#include "handleEnemy.hpp"  
#include "handlePowerUps.hpp"
#include "handleAudio.hpp"
#include "handleMenu.hpp"
#include "handleObjektiv.hpp"
#include <string>

void gameloop(){
    const char* mapModelPath = "models/map.glb"; //sätter sökvägen till modellen
    Model model = LoadModel(mapModelPath); //laddar in modellen

    managePickups Pickups;
    Player player; //initierar spelaren
    HealthPowerUp healthPowerUp; //initierar powerup
    Camera camera = initCamera3D(); //initierar kameran
    EnemieManager enemyManager(0); //initierar ALLA typer av fiender, kan läggas till logik senare.

    enemyManager.initEnemies(); //initierar fiender in i listan från början
    
    //fixa så spelarens position inte är public så vi inte kan ändra på den ;)
    

    while(!WindowShouldClose()){         
                //playAudio();
                Pickups.updatePlayerPos(player.position);
                checkCameraMovment(&camera, &player.position, &player.orientation); //flyttar kameran efter spelaren
                player.move(); //flyttar spelaren vid behov
                healthPowerUp.move(player.position); //flyttar powerup
                BeginDrawing();
                    ClearBackground(RAYWHITE);
                    BeginMode3D(camera); 
                        Pickups.updatePickups();
                        player.draw(); //draw player
                        healthPowerUp.draw(); //draw powerup
                        enemyManager.updateEnemies(player.position); //draw enemies
                        if(enemyManager.checkCollision(player.position, player.orientation))
                            player.takeDamage(); //kollar om spelaren kolliderar med fienden
                        
                        DrawModel(model, {0.0f, 0.0f, 0.0f}, 300.0f, WHITE); //ritar ut modellen
                    EndMode3D();

                EndDrawing();
                DrawText(TextFormat("COINS: %i", player.coins), 10, 10, 30, GREEN);
                DrawText(TextFormat("Pickps: %d", Pickups.getPickupSize()), 10, 20 , 30, BLACK);
                DrawText(TextFormat("Active Pickups: %d", Pickups.isAnyoneActive()), 10, 50, 30, BLACK);
                DrawText(TextFormat("Dropoff: %d", Pickups.isDropOffActive()), 10, 80, 30, GREEN);
    }
}




