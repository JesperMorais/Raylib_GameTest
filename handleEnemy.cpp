#include "handleEnemy.hpp"

using namespace std;

void Enemies::initRandomizePositions(){
    SetRandomSeed(GetRandomValue(0, 1000));
    for (int i = 0; i < enemyAmount; i++){
        float x = GetRandomValue(-ROOM_WIDTH, ROOM_WIDTH);
        float z = GetRandomValue(-40, -10);
        enemyPosList.push_back({x, 0.0f, z});
    } 
}

void Enemies::randomizePositions(Vector3& enemyPos){
    enemyPos.x = GetRandomValue(-ROOM_WIDTH, ROOM_WIDTH);
}

void Enemies::draw(){
    for (int i = 0; i < (int)enemyPosList.size(); i++){
        DrawCube(enemyPosList[i], 2.0f, 2.0f, 2.0f, BLUE);
        DrawCubeWires(enemyPosList[i], 2.0f, 2.0f, 2.0f, DARKBLUE);
    }
}   

void Enemies::move(Vector3 playerPosition){
    for (auto& enemyPos : enemyPosList) {
        enemyPos.z += 0.2f;
        if (enemyPos.z > playerPosition.z + 20.0f) {
            enemyPos.z = playerPosition.z - 40.0f;
            randomizePositions(enemyPos);
        }
    }
}
