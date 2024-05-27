#include "handlePlayer.hpp"
#include "handleCamera.hpp"
#include "handleEnemy.hpp"  
#include "handlePowerUps.hpp"
#include "handleAudio.hpp"
#include <string>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "COOL GAME");
    InitAudioDevice();
    SetTargetFPS(60);             
    
    bool showMenu = true; //visar menyn
    Rectangle startButton = { 300, 300, 200, 50 }; //startknappens position och storlek
    Color buttonColor = GRAY; //färgen på startknappen
    Color buttonColorHover = LIGHTGRAY; //färgen på startknappen när musen är över
    
    Image image = LoadImage("models/backgrounds/real.png"); //laddar in bilden 
    Texture2D textureImage = LoadTextureFromImage(image); //laddar in bilden som en texture
    int centerX = (screenWidth - textureImage.width) / 2;
    int centerY = (screenHeight - textureImage.height) / 2;

    Player player; //initierar spelaren
    HealthPowerUp healthPowerUp; //initierar powerup
    Zombie zombie(5); //initierar fienden
    infantry infantry(10); //initierar fienden
    Camera camera = initCamera3D(); //initierar kameran

    Model model = LoadModel("models/boat.obj"); // Load OBJ model
    Texture2D textureBoat = LoadTexture("models/Texture/wood1.jpg"); // Load the texture
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textureBoat; // Apply the texture to the model

    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {   
            if (CheckCollisionPointRec(GetMousePosition(), startButton)) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                      showMenu = false; // Hide the menu and start the game
                }
            }           

            if(showMenu){
                if (CheckCollisionPointRec(GetMousePosition(), startButton)) buttonColor = buttonColorHover;
                else buttonColor = GRAY;
                
                BeginDrawing();
                    ClearBackground(RAYWHITE);

                    DrawTexture(textureImage, centerX, centerY, WHITE); //ritar ut bakgrunden
                    DrawRectangleRec(startButton, buttonColor);

                    DrawText("START", 350, 310, 40, WHITE);

                EndDrawing();
            }
            else{
                playAudio();
                checkCameraMovment(&camera, &player.position); //flyttar kameran efter spelaren
                player.move(); //flyttar spelaren vid behov
                zombie.move(player.position); //flyttar fienden beroende på spelarens position
                infantry.move(player.position); //flyttar fienden beroende på spelarens position
                healthPowerUp.move(player.position); //flyttar powerup
                player.checkCollision(infantry.getAllPosList()); //kollar om spelaren kolliderar med fienden
                player.checkCollision(zombie.getAllPosList()); //kollar om spelaren kolliderar med fienden
            
                BeginDrawing();
                    ClearBackground(RAYWHITE);
                    BeginMode3D(camera); 

                        player.draw(); //draw playerhttps://www.phind.com/search?cache=w4gog9kc4cs9vnbrbh3l77u2
                        zombie.draw(); //draw enemy
                        infantry.draw(); //draw enemy
                        healthPowerUp.draw(); //draw powerup
                        //healthPowerUp.updateLine(player.position); //draw line between player and powerup
                    EndMode3D();

                EndDrawing();
                DrawText(TextFormat("Health: %i", player.health), 10, 20, 30, RED);
                DrawText(TextFormat("Enemies left: %i", zombie.getActiveEnemies() + infantry.getActiveEnemies()), 10, 60, 30, RED); 
       } 
    }
    CloseWindow();
    CloseAudioDevice();
    UnloadTexture(textureImage);
    return 0;
}

