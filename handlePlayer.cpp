#include "handlePlayer.hpp"


void Player::drawPlayer(){
        DrawCube(position, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(position, 2.0f, 2.0f, 2.0f, MAROON);
        DrawGrid(10, 1.0f);
}

void Player::checkIfMovePlayer(){
    if (IsKeyDown(KEY_W)) position.z -= 0.1f;
    if (IsKeyDown(KEY_S)) position.z += 0.1f;
    if (IsKeyDown(KEY_A)) position.x -= 0.1f;
    if (IsKeyDown(KEY_D)) position.x += 0.1f;
}   

void Player::showCurrentHealth(int health){
    DrawText(TextFormat("Health: %i", health), 40, 80, 20, RED);  
}
