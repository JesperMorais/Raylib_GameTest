#pragma once

#include "include/raylib.h"
#include "include/raymath.h"
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
        const char* modelPath;
        Model bussModel;

        vector<Particle> particles;  //container för partiklar
        Vector3 position; //vart spelaren är
        Vector3 orientation; //vart spelaren tittar mot
        bool hasCollided = false;
        int coins = 0;
        float maxSpeed;
        Vector3 currentSpeed {0.0f, 0.0f, 0.0f};
        Player(){position = {0.0f, 0.0f, 0.0f}, orientation = {0.0f, 0.0f, 0.0f}, maxSpeed = 0.5f;
            particles.resize(50); //skapar 100 partiklar
             for (auto& p : particles) {
                p.position = {position.x + 0.1f, position.y-1.0f, position.z + GetRandomValue(-1.0f, 1.0f) };
                p.velocity = {(float)GetRandomValue(-1.0f, 1.0f), 0.0f, (float)GetRandomValue(-1.0f, 1.0f)};
        }
        modelPath = "models/bussTest3.glb";
        bussModel = LoadModel(modelPath); 
        } //konstruktor
        
        void draw();
        void move();
        void takeDamage();
        void updateParticles(float deltaTime); //uppdaterar partiklar tar in frames per second
        void drawParticles();
        void DrawWireBox();
};