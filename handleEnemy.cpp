#include "handleEnemy.hpp"

void Enemy::drawEnemy(){
    DrawCube(enemyPos, 2.0f, 2.0f, 2.0f, BLUE);
    DrawCubeWires(enemyPos, 2.0f, 2.0f, 2.0f, DARKBLUE);
}   

void Enemy::moveEnemy(){
    enemyPos.z += 0.1f;
    if(enemyPos.z > 20.0f) {
        enemyPos.z = -20.0f;
    }
}