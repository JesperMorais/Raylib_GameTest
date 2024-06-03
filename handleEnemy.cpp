#include "handleEnemy.hpp"
using namespace std;

void infantry::draw(){
    for (int i = 0; i < (int)infantryPosList.size(); i++){
        DrawCube(infantryPosList[i], 2.0f, 2.0f, 2.0f, GREEN);
        DrawCubeWires(infantryPosList[i], 2.0f, 2.0f, 2.0f, DARKGREEN);
    }
}

void infantry::move(Vector3 playerPosition){
//make infantry move farward, check if that farward movment will collid with Infantry, if so check if we can move sideways x to avoid collision
   for (auto& infantryPos : infantryPosList) {
        infantryPos.z += 0.2f;
     

        // Adjust positioning relative to the player
        if (infantryPos.z > playerPosition.z + 20.0f) {
            infantryPos.z = playerPosition.z - 40.0f;
            // Randomize X positions to spread out the infantry
            // Note: Implementing randomization is omitted for brevity
        }
    }
}


int infantry::checkCollision(Vector3 infPos){
    //check if infantry is collidng with arguemt infPos
    for (const auto& infantryPos : infantryPosList) {
        if (CheckCollisionSpheres(infPos, 0.50f, infantryPos, 0.50f)) {
            return 1;
        }
    }
    return 0;
}

void infantry::initRandomizePositions(){
    SetRandomSeed(GetRandomValue(0, 1000));

    for (int i = 0; i < amountOfInfantry; i++){
        float x = GetRandomValue(-ROOM_WIDTH, ROOM_WIDTH);
        float z = GetRandomValue(-40, -10);
        
        //if(!checkCollision({x, 0.0f, z})){           
            infantryPosList.push_back({x, 0.0f, z});
        //}
    } 
}

void infantry::randomizeXPositions(Vector3& enemyPos){
    enemyPos.x = GetRandomValue(-ROOM_WIDTH, ROOM_WIDTH);
}

vector<Vector3>& infantry::getAllPosList(){
    return infantryPosList;
}

void Zombie::draw(){
    // Just update the frame index and apply the animation once per frame.


    // Draw the model at a specified position
    
    for (int i = 0; i < (int)zombiePosList.size(); i++){
        DrawCubeWires(zombiePosList[i], 2.0f, 2.0f, 2.0f, DARKPURPLE);
        DrawModel(zombieModel, {zombiePosList[i].x,(zombiePosList[i].y-1.0f), zombiePosList[i].z}, 2.0f, WHITE);
    }
}

void Zombie::move(Vector3 playerPosition){
    for (auto& zombiePos : zombiePosList) {
        zombiePos.z += 0.2f;
        if(playerPosition.x > zombiePos.x && playerPosition.z > zombiePos.z){ //går mot spelaren med inte efter den gått förbi
            zombiePos.x += 0.08f;
        }
        else if(playerPosition.x < zombiePos.x && playerPosition.z > zombiePos.z){
            zombiePos.x -= 0.08f;
        }
        if (zombiePos.z > playerPosition.z + 20.0f) {
            zombiePos.z = playerPosition.z - 40.0f;
            randomizeXPositions(zombiePos);
        }
    }
}

void Zombie::initRandomizePositions(){
    SetRandomSeed(GetRandomValue(0, 1000));

    for (int i = 0; i < amountOfZombies; i++){
        float x = GetRandomValue(-ROOM_WIDTH, ROOM_WIDTH);
        float z = GetRandomValue(-40, -10);
        
        //if(!checkCollision({x, 0.0f, z})){           
            zombiePosList.push_back({x, 0.0f, z});
        //}
    } 
}

vector<Vector3>& Zombie::getAllPosList(){
    return zombiePosList;
}

void Zombie::randomizeXPositions(Vector3& enemyPos){
    enemyPos.x = GetRandomValue(-ROOM_WIDTH, ROOM_WIDTH);
}