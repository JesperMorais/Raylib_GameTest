#include "handlePlayer.hpp"
#include "include/raymath.h"
#include <iostream>
using namespace std;

void Player::draw(){
        DrawCube(position, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(position, 2.0f, 2.0f, 2.0f, MAROON);
        DrawGrid(10, 1.0f);
}

void Player::move(){ //TODO: tilt camera when moving a specific direction
    if (IsKeyDown(KEY_W)) currentSpeed.z = Lerp(currentSpeed.z, -maxSpeed, 0.02f);
    else if (IsKeyDown(KEY_S)) currentSpeed.z = Lerp(currentSpeed.z, maxSpeed, 0.02f);
    
    if (IsKeyDown(KEY_A)) currentSpeed.x = Lerp(currentSpeed.x, -maxSpeed, 0.02f);
    else if (IsKeyDown(KEY_D)) currentSpeed.x = Lerp(currentSpeed.x, maxSpeed, 0.02f);
    
    if (!IsKeyDown(KEY_W)) currentSpeed.z = Lerp(currentSpeed.z, 0.0f, 0.02f);
    else if (!IsKeyDown(KEY_S)) currentSpeed.z = Lerp(currentSpeed.z, 0.0f, 0.02f);

    if (!IsKeyDown(KEY_A)) currentSpeed.x = Lerp(currentSpeed.x, 0.0f, 0.02f);
    else if (!IsKeyDown(KEY_D)) currentSpeed.x = Lerp(currentSpeed.x, 0.0f, 0.02f);

    position.x += currentSpeed.x;
    position.z += currentSpeed.z;
}   

void Player::checkCollision(vector<Vector3>& enemyPosList){
    for (const auto& enemyPos : enemyPosList) {
            if (CheckCollisionSpheres(position, 1.0f, enemyPos, 1.0f)) {
                if (hasCollided == false){
                takeDamage();
            }
            hasCollided = true; 
            }
        }
    hasCollided = false;
 }

 void Player::takeDamage(){
     health--;
     currentSpeed.z = 0.4f;
}