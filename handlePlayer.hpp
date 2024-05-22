#pragma once

#include "include/raylib.h"
#include <stdio.h>
#include <iostream>

class Player{
    public:     
        Vector3 position; //vart spelaren är
        Vector3 out = {2.0f, 2.0f , 2.0f};
        
        int health;
        Player(){position = {0.0f, 0.0f, 0.0f}, health=3;} //konstruktor
        
        
        void drawPlayer();
        void checkIfMovePlayer();
        void showCurrentHealth(int health);
        int check(Vector3 enemyPos, Vector3 playerPos);
};