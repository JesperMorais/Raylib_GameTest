#include "handlePlayer.hpp"

using namespace std;

void Player::draw(){
    Vector3 modelPosition = position;
    
    modelPosition.x += sin(DEG2RAD * orientation.y) * 5.0f; // Offset model position in front of player
    modelPosition.z += cos(DEG2RAD * orientation.y) * 5.0f;

    Matrix rotation = MatrixRotateY(DEG2RAD * (orientation.y)); // Apply rotation to the model from player orientation
    Matrix initialCorrection = MatrixRotateY(DEG2RAD * 180.0f); // Initial rotation correction for the model
    bussModel.transform = MatrixMultiply(rotation, initialCorrection); // Combine rotation with initial correction

    DrawModel(bussModel, modelPosition, 0.10f, WHITE); // Draw the model at the translated position
    DrawGrid(10, 1.0f);


    Vector3 direction = { sin(DEG2RAD * orientation.y), 0, cos(DEG2RAD * orientation.y) };
    Vector3 endPoint = { position.x + direction.x * 10, position.y, position.z + direction.z * 10 }; // Extend 10 units in front
    DrawLine3D(position, endPoint, LIME); // Draw a line from the boat to the endpoint
    drawParticles();
}

void Player::move(){ //TODO: tilt camera when moving a specific direction
    if (IsKeyDown(KEY_W)) currentSpeed.z = Lerp(currentSpeed.z, -maxSpeed, 0.02f);
    else if (IsKeyDown(KEY_S)) currentSpeed.z = Lerp(currentSpeed.z, maxSpeed, 0.02f);
    else currentSpeed.z = Lerp(currentSpeed.z, 0.0f, 0.02f); // Smoothly stop if no input

    // Turning
    float turnSpeed = 0.9f; // Slower turning speed for boat-like movement
    if (IsKeyDown(KEY_A)) orientation.y += turnSpeed; // Decrease yaw for left turn
    else if (IsKeyDown(KEY_D)) orientation.y -= turnSpeed; // Increase yaw for right turn

    // Normalize orientation to avoid values getting too large
    orientation.y = fmod(orientation.y, 360.0f);
    if (orientation.y < 0) orientation.y += 360.0f;

    // Calculate direction based on orientation
    Vector3 direction = { sin(DEG2RAD * orientation.y), 0, cos(DEG2RAD * orientation.y) };

    // Update position based on current speed and direction
    position.x += currentSpeed.z * direction.x;
    position.z += currentSpeed.z * direction.z;

    updateParticles(GetFrameTime());
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
    if(IsAudioDeviceReady()){   //plays sound when player takes damage
            static Wave wave = LoadWave("sounds/Sidechain_bip.3.wav");
            static Sound sound = LoadSoundFromWave(wave);
            PlaySound(sound);
        }
    
    health--;
    currentSpeed.z = 0.4f;
}

void Player::updateParticles(float deltaTime){
    const float maxDistance = 6.0f; // Maximum distance between particles and player
    const float minZOffset = -1.0f;
    const float maxZOffset = 1.0f;

    for (auto& p : particles) {
        // Move the particle
        p.position.y += p.velocity.y * deltaTime * 5.0f;
        p.position.z += p.velocity.z * deltaTime * 5.0f;

        // Check if particle is too far from player
        float distance = Vector3Distance(p.position, position);
        if (distance > maxDistance) {
            // Respawn particle near the player within a range on the Z-axis
            p.position = { position.x + 0.5f, position.y-1.0f, position.z + GetRandomValue(minZOffset, maxZOffset) };
            p.velocity = { (float)GetRandomValue(-1.0f, 1.0f), 0.0f, (float)GetRandomValue(-1.0f, 1.0f) };
        }
    }
}

void Player::drawParticles() {
        for (const auto& p : particles) {
            DrawCube(p.position, 0.2f, 0.2f, 0.2f, BLUE);
        }
    }

