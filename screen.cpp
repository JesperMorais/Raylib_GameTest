#include "screen.hpp"
#include "state.hpp"
#include <iostream>

void DriveScreen::draw(){
    BeginMode3D(camera);          // everything between here and EndMode3D
        // Draw buss                is rendered through the camera
        // Draw enemies
        // Draw enviorment'
        enemies.updateEnemies(player.position);
        player.draw();
    EndMode3D();
    return;
}

Screen* DriveScreen::update(Session* sesh){
    // update() is pure logic: move things and slide the camera. No drawing here.
    
    player.move();
    checkCameraMovment(&camera, &player.position, &player.orientation);
    return this;
}

//Checks if we have presses button or not.
Screen* MenuScreen::update(Session* sesh){
    bool hover   = CheckCollisionPointRec(GetMousePosition(), menu.startButton);
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER);

    if (hover && clicked) return new DriveScreen();  // leave the menu
    return this;                                     // otherwise keep showing the menu
}

void MenuScreen::draw(){

    if (CheckCollisionPointRec(GetMousePosition(), menu.startButton)) menu.buttonColor = menu.buttonColorHover;
    else menu.buttonColor = GRAY;
    DrawRectangleRec(menu.startButton, menu.buttonColor);
    DrawTexture(menu.textureImage, menu.centerX, menu.centerY, WHITE); //ritar ut bakgrunden
    DrawText("START", 350, 310, 40, WHITE);                    
        
}