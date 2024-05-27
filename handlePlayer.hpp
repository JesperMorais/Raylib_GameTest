#pragma once

#include "include/raylib.h"
#include <iostream>
#include <vector>


using namespace std;

//TODO: Powerups ( health and speed)
//TODO: out of bounds check
//TODO: fixa sväng mechaniken

typedef struct Particles{
    Vector3 position;
    Vector3 velocity;
}Particle;

class Player{
    public:
        vector<Particle> particles;  //container för partiklar
        Vector3 position; //vart spelaren är
        Vector3 orientation; //vart spelaren tittar mot
        bool hasCollided = false;
        int health;
        float maxSpeed;
        Vector3 currentSpeed {0.0f, 0.0f, 0.0f};
        Player(){position = {0.0f, 0.0f, 0.0f}, orientation = {0.0f, 0.0f, 0.0f}, health=3, maxSpeed = 0.5f;
            particles.resize(50); //skapar 100 partiklar
             for (auto& p : particles) {
                p.position = {position.x + 0.1f, position.y-1.0f, position.z + GetRandomValue(-1.0f, 1.0f) };
                p.velocity = {(float)GetRandomValue(-1.0f, 1.0f), 0.0f, (float)GetRandomValue(-1.0f, 1.0f)};
        }
        } //konstruktor
        
        void draw();
        void move();
        void takeDamage();
        void checkCollision(vector<Vector3>& enemiesPosList);
        void updateParticles(float deltaTime); //uppdaterar partiklar tar in frames per second
        void drawParticles();
};