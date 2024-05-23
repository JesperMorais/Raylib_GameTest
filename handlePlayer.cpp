#include "handlePlayer.hpp"
#include "include/raymath.h"
#include <iostream>


#define enemyAmount 10 
using namespace std;

void Player::drawPlayer(){
        DrawCube(position, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(position, 2.0f, 2.0f, 2.0f, MAROON);
        DrawGrid(10, 1.0f);
}

void Player::checkIfMovePlayer(){ //TODO: tilt camera when moving a specific direction
    float speed = 00.50f;
    if (IsKeyDown(KEY_W)) position.z = Lerp(position.z, position.z - speed, 0.4f); //start, end speed of lerp
    if (IsKeyDown(KEY_S)) position.z = Lerp(position.z, position.z + speed, 0.4f); 
    if (IsKeyDown(KEY_A)) position.x = Lerp(position.x, position.x - speed, 0.4f);
    if (IsKeyDown(KEY_D)) position.x = Lerp(position.x, position.x + speed, 0.4f);
}   

void Player::showCurrentHealth(int health){
    if (health == 3){
        DrawText("Health: <3 <3 <3", 200, 100, 20, RED);
    }
    else if(health == 2){
        DrawText("Health: <3 <3", 200, 100, 20, RED);
    }
    else if(health == 1){
        DrawText("Health: <3", 200, 100, 20, RED);
    }
    else{
        DrawText("Health: ", 200, 100, 20, RED);
    }
}

 int Player::checkCollision(vector<Vector3>& enemyPosList, Vector3 playerPos){
    for (const auto& enemyPos : enemyPosList) {
            if ((enemyPos.z <= playerPos.z + size.z) &&
                (playerPos.z <= enemyPos.z + size.z) &&
                (enemyPos.x <= playerPos.x + size.x) &&
                (playerPos.x <= enemyPos.x + size.x)) {
                return 1;
            }
        }
        return 0;
    }