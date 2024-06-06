#include "handleEnemy.hpp"
using namespace std;

void Zombie::draw(){
    for (int i = 0; i < (int)zombiePosList.size(); i++){
        zombieDirection = {0.0f, 0.0f, 0.0f};
        DrawCubeWires(zombiePosList[i], 2.0f, 2.0f, 2.0f, DARKPURPLE);
        DrawModel(zombieModel, {zombiePosList[i].x,(zombiePosList[i].y-1.0f), zombiePosList[i].z}, 5.0f, WHITE);
    }
}

void Zombie::move(Vector3 playerPosition){

    frameCounter = (frameCounter + 1)%animation->frameCount;
    UpdateModelAnimation(zombieModel, animation[0], frameCounter);

    for (auto& zombiePos : zombiePosList) {
        //Move towards player regardless of position
        if(playerPosition.x > zombiePos.x && playerPosition.z > zombiePos.z){ //Spelaren är till höger och framför
            zombiePos.z += 0.1f;
            zombiePos.x += 0.08f;
        }
        else if(playerPosition.x < zombiePos.x && playerPosition.z > zombiePos.z){ //Spelearen är till vänster och framför
            zombiePos.z += 0.1f;
            zombiePos.x -= 0.08f;
        }
        else if(playerPosition.x > zombiePos.x && playerPosition.z < zombiePos.z){ //Spelaren är till höger och bakom
            zombiePos.z -= 0.1f;
            zombiePos.x += 0.08f;
        }
        else if(playerPosition.x < zombiePos.x && playerPosition.z < zombiePos.z){ //Spelaren är till vänster och bakom
            zombiePos.z -= 0.1f;
            zombiePos.x -= 0.08f;
        }
    }
}

void Zombie::initRandomizePositions(){
    SetRandomSeed(GetRandomValue(0, 1000));
    for (int i = 0; i < amountOfZombies; i++){
        
        float x = GetRandomValue(-ROOM_WIDTH, ROOM_WIDTH);
        float z = GetRandomValue(-ROOM_HEIGHT, ROOM_HEIGHT);       
        zombiePosList.push_back({x, 0.0f, z});
    } 
}

vector<Vector3>& Zombie::getAllPosList(){
    return zombiePosList;
}

void Zombie::randomizeXPositions(Vector3& enemyPos){
    enemyPos.x = GetRandomValue(-ROOM_WIDTH, ROOM_WIDTH);
}

void zoomies::draw(){
    DrawModel(zombieModel, position, 1.0f, WHITE);
}

void zoomies::initRandomizePositions(){
        SetRandomSeed(GetRandomValue(0, 1000));
        float x = GetRandomValue(-ROOM_WIDTH, ROOM_WIDTH);
        float z = GetRandomValue(-ROOM_HEIGHT, ROOM_HEIGHT);
        position = {x, 0.0f, z};
}

void zoomies::move(Vector3 playerPosition){
    checkIfIdle(playerPosition);
    if(idleState){
        //Stand still and Maybe change animation to some idle animation
    }
    else{
        //eventually make the zombie change animation to walking
        if(playerPosition.x > position.x && playerPosition.z > position.z){ //Spelaren är till höger och framför
            position.z += 0.1f;
            position.x += 0.08f;
        }
        else if(playerPosition.x < position.x && playerPosition.z > position.z){ //Spelearen är till vänster och framför
            position.z += 0.1f;
            position.x -= 0.08f;
        }
        else if(playerPosition.x > position.x && playerPosition.z < position.z){ //Spelaren är till höger och bakom
            position.z -= 0.1f;
            position.x += 0.08f;
        }
        else if(playerPosition.x < position.x && playerPosition.z < position.z){ //Spelaren är till vänster och bakom
            position.z -= 0.1f;
            position.x -= 0.08f;
        }
    }
}

void zoomies::checkIfIdle(Vector3 playerPosition){
    if(playerPosition.x < position.x + 10.0f || playerPosition.x > position.x - 10.0f){ // kollar om spelare är i närheten
        idleState = false;
    }
    else if(playerPosition.z < position.z + 10.0f || playerPosition.z > position.z - 10.0f){ // kollar om spelare är i närheten
        idleState = false;
    }
    else{
        idleState = true;
    }
}