#include "handlePlayer.hpp"
#include "include/raymath.h"


void Player::drawPlayer(){
        DrawCube(position, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(position, 2.0f, 2.0f, 2.0f, MAROON);
        DrawGrid(10, 1.0f);
}

void Player::checkIfMovePlayer(){ //TODO: tilt camera when moving a specific direction
    float speed = 1.00f;
    if (IsKeyDown(KEY_W)) position.z = Lerp(position.z, position.z - speed, 0.4f); //start, end speed of lerp
    if (IsKeyDown(KEY_S)) position.z = Lerp(position.z, position.z + speed, 0.4f);
    if (IsKeyDown(KEY_A)) position.x = Lerp(position.x, position.x - speed, 0.4f);
    if (IsKeyDown(KEY_D)) position.x = Lerp(position.x, position.x + speed, 0.4f);
}   

void Player::showCurrentHealth(int health){
    DrawText(TextFormat("Health: %i", health), 40, 80, 20, RED);  
}
