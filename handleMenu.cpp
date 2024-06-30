#include "handleMenu.hpp"

void Menu::initmenu(){
    showMenu = true; //visar menyn
    startButton = { 300, 300, 200, 50 }; //startknappens position och storlek
    buttonColor = GRAY; //färgen på startknappen
    buttonColorHover = LIGHTGRAY; //färgen på startknappen när musen är över
    
    image = LoadImage("models/backgrounds/real.png"); //laddar in bilden 
    textureImage = LoadTextureFromImage(image); //laddar in bilden som en texture
    centerX = (__screenWidth - textureImage.width) / 2;
    centerY = (__screenHeight - textureImage.height) / 2;
}

void Menu::playMenu(){
    if (CheckCollisionPointRec(GetMousePosition(), startButton) || IsKeyPressed(KEY_ENTER)) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) {
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
}

