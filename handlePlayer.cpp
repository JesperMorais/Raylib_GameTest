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
    vector<int> indicesToRemove; // Temporary container to store indices of elements to remove

    for (size_t i = 0; i < enemyPosList.size(); ++i) {
        const auto& enemyPos = enemyPosList[i];
        if (CheckCollisionSpheres(position, 1.0f, enemyPos, 1.0f)) {
            indicesToRemove.push_back(i); // Store index of element to remove
            if (hasCollided == false) {
                takeDamage();
            }
            hasCollided = true;
        }
    }
    // Remove elements from the list based on collected indices
    for (auto it = indicesToRemove.rbegin(); it!= indicesToRemove.rend(); ++it) {
        enemyPosList.erase(enemyPosList.begin() + *it);
    }
    hasCollided = false;
 }

 void Player::takeDamage(){
    if(IsAudioDeviceReady()){  
            static Wave wave = LoadWave("sounds/Sidechain_bip.3.wav");
            static Sound sound = LoadSoundFromWave(wave);
            PlaySound(sound);
        }
    health--;
    currentSpeed.z = 0.4f;
}