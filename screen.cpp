#include "screen.hpp"
#include "state.hpp"
#include <iostream>

void DriveScreen::draw(){
    BeginMode3D(camera);          
        // Draw enviorment'
        enemies.drawEnemies();
        player.draw();
    EndMode3D();
    return;
}

Screen* DriveScreen::update(Session* sesh){
    // update() is pure logic: move things and slide the camera. No drawing here.
    player.move();
    enemies.moveEnemies(player.position);
    if (enemies.getMaxEnemies() != (sesh->days * 3)){ // Update sesh days
        enemies.setMaxEnemies(sesh->days * 3);
    }
    if(enemies.checkCollision(player)){
        sesh->coins++;
        cout << "coints now at: " << sesh->coins << endl;
    }
    checkCameraMovment(&camera, &player.position, &player.orientation);
    if (IsKeyPressed(KEY_G)){
        return new MenuScreen;
    }
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