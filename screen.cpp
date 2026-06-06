#include "screen.hpp"
#include "state.hpp"
#include <iostream>

void DriveScreen::draw(Session* sesh){
    BeginMode3D(camera);          
        // Draw enviorment'
        enemies.drawEnemies();
        player.draw();
    EndMode3D();
    DrawText(TextFormat("COINS: %i", sesh->coins), 10, 10, 30, GREEN);
    DrawText(TextFormat("DAYS: %i", sesh->days), 10, 40, 30, BLUE);
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

    if(enemies.getEnemiesSize() < 1){
        return new EndDayScren;
    }

    return this;
}

void EndDayScren::draw(Session* sesh){
    // Show days and coins.
    // button to go back to driverScreen +1 day
    DrawRectangleRec(returnButton, returnColor);
    DrawText("New day", 320, 310, 40, WHITE);
}

Screen* EndDayScren::update(Session* sesh){
    bool hover   = CheckCollisionPointRec(GetMousePosition(), returnButton);
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER);
    if (hover && clicked) {
        sesh->days++;
        return new DriveScreen();  // leave the menu
    }
    return this;                                     // otherwise keep showing the menu
}

//Checks if we have presses button or not.
Screen* MenuScreen::update(Session* sesh){
    bool hover   = CheckCollisionPointRec(GetMousePosition(), menu.startButton);
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER);

    if (hover && clicked) return new DriveScreen();  // leave the menu
    return this;                                     // otherwise keep showing the menu
}

void MenuScreen::draw(Session* sesh){

    if (CheckCollisionPointRec(GetMousePosition(), menu.startButton)) menu.buttonColor = menu.buttonColorHover;
    else menu.buttonColor = GRAY;
    DrawRectangleRec(menu.startButton, menu.buttonColor);
    DrawTexture(menu.textureImage, menu.centerX, menu.centerY, WHITE); //ritar ut bakgrunden
    DrawText("START", 350, 310, 40, WHITE);                    
        
}