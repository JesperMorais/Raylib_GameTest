#include "handleEnemy.hpp"

using namespace std;

void Enemy::drawEnemy(){
    for (const auto& enemyPos : enemyPosList) {
        DrawCube(enemyPos, 2.0f, 2.0f, 2.0f, BLUE);
        DrawCubeWires(enemyPos, 2.0f, 2.0f, 2.0f, DARKBLUE);
    }
}   

void Enemy::moveEnemy(){
    for (auto& enemyPos : enemyPosList) {
        enemyPos.z += 0.2f;
    }
}