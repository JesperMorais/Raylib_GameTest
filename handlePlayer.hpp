#pragma once

#include "include/raylib.h"
#include <stdio.h>
#include <iostream>

class Player{
    public:     
        Vector3 position; //vart spelaren är
        int health;
        Player(){position = {0.0f, 0.0f, 0.0f}, health=3;} //konstruktor
        
        void drawPlayer();
        void checkIfMovePlayer();
        void showCurrentHealth(int health);
};