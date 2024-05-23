#pragma once

#include "include/raylib.h"
#include <iostream>
#include <vector>

using namespace std;

//TODO: Powerups ( health and speed)
//TODO: out of bounds check
//TODO: fixa sväng mechaniken
//TODO: 


class Player{
    public:     
        Vector3 position; //vart spelaren är
        bool hasCollided = false;
        int health;
        float maxSpeed;
        Vector3 currentSpeed {0.0f, 0.0f, 0.0f};
        Player(){position = {0.0f, 0.0f, 0.0f}, health=3, maxSpeed = 0.8f;} //konstruktor
        
        void draw();
        void move();
        void takeDamage();
        void checkCollision(vector<Vector3>& enemiesPosList);
};