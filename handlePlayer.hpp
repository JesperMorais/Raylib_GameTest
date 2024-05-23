#pragma once

#include "include/raylib.h"
#include <iostream>
#include <vector>

using namespace std;

class Player{
    public:     
        Vector3 position; //vart spelaren är
        Vector3 size = {2.0f, 2.0f , 2.0f};
        bool hasCollided = false;
        int health;
        Player(){position = {0.0f, 0.0f, 0.0f}, health=3;} //konstruktor
        
        
        void drawPlayer();
        void checkIfMovePlayer();
        void showCurrentHealth(int health);
        int checkCollision(vector<Vector3>& enemyPos, Vector3 playerPos);
};