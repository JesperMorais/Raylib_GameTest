#include "screen.hpp"
#include "state.hpp"
#include <iostream>
#include <memory>

void DriveScreen::draw(Session* sesh){
    BeginMode3D(camera);          
        // Draw enviorment'
        enemies.drawEnemies();
        player.draw();
        mp.draw();
    EndMode3D();
    DrawText(TextFormat("HEALTH: %i", player.health), 10, 10, 30, RED);
    DrawText(TextFormat("DAYS: %i", sesh->days), 10, 40, 30, BLUE);
    
    // Health bar: one red block per point, laid out right-to-left from x=700.
    for (int i = 0; i < player.health; i++){
        DrawRectangle(700 - i * 40, 10, 40, 10, RED);
    }
    return;
}

std::unique_ptr<Screen> DriveScreen::update(Session* sesh){
    // update() is pure logic: move things and slide the camera. No drawing here.
    player.move();
    enemies.moveEnemies(player.position);
    if (enemies.getMaxEnemies() != (sesh->days * 3)){ // Update sesh days
        enemies.setMaxEnemies(sesh->days * 3);
        enemies.initEnemies();
    }

    if(enemies.checkCollision(player)){
        player.health--;
    }
    checkCameraMovment(&camera, &player.position, &player.orientation);
    if (IsKeyPressed(KEY_G)){
        return std::make_unique<MenuScreen>();
    }

    mp.update(&player);
    if(enemies.getEnemiesSize() < 1){
        return std::make_unique<EndDayScren>();
    }

    return nullptr;
}

void EndDayScren::draw(Session* sesh){
    // Show days and coins.
    // button to go back to driverScreen +1 day
    DrawRectangleRec(returnButton, returnColor);
    DrawText("New day", 320, 310, 40, WHITE);
}

std::unique_ptr<Screen> EndDayScren::update(Session* sesh){
    bool hover   = CheckCollisionPointRec(GetMousePosition(), returnButton);
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER);
    if (hover && clicked) {
        sesh->days++;
        return std::make_unique<DriveScreen>();
    }
    return nullptr;                                     // otherwise keep showing the menu
}

//Checks if we have presses button or not.
std::unique_ptr<Screen> MenuScreen::update(Session* sesh){
    bool hover   = CheckCollisionPointRec(GetMousePosition(), menu.startButton);
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER);

    if (hover && clicked) return std::make_unique<DriveScreen>(); // leave the menu
    return nullptr;                                     // otherwise keep showing the menu
}

void MenuScreen::draw(Session* sesh){

    if (CheckCollisionPointRec(GetMousePosition(), menu.startButton)) menu.buttonColor = menu.buttonColorHover;
    else menu.buttonColor = GRAY;
    DrawRectangleRec(menu.startButton, menu.buttonColor);
    DrawTexture(menu.textureImage, menu.centerX, menu.centerY, WHITE); //ritar ut bakgrunden
    DrawText("START", 350, 310, 40, WHITE);                    
        
}