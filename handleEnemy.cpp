#include "handleEnemy.hpp"

using namespace std;

void Enemy::initRandomizePositions(){
    SetRandomSeed(GetRandomValue(0, 1000));
    for (int i = 0; i < enemyAmount; i++){
        float x = GetRandomValue(-ROOM_WIDTH, ROOM_WIDTH);
        float z = GetRandomValue(-40, -10);
        enemyPosList.push_back({x, 0.0f, z});
    } 
}

void Enemy::randomizePositions(Vector3& enemyPos){
    SetRandomSeed(GetRandomValue(0, 1000));
    enemyPos.x = GetRandomValue(-ROOM_WIDTH, ROOM_WIDTH);
    enemyPos.z = -40;
    
}

void Enemy::drawEnemy(){
    for (int i = 0; i < enemyAmount; i++){
        DrawCube(enemyPosList[i], 2.0f, 2.0f, 2.0f, BLUE);
        DrawCubeWires(enemyPosList[i], 2.0f, 2.0f, 2.0f, DARKBLUE);
    }
}   

void Enemy::moveEnemy(){
    for (auto& enemyPos : enemyPosList) {
        enemyPos.z += 0.2f;
        if (enemyPos.z > 40) {
            enemyPos.z = -40;
            randomizePositions(enemyPos);
        }
    }
}