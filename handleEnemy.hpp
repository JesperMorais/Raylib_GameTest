#pragma once
#include "include/raylib.h"
#include <vector>
#include <iostream>
#include "include/raymath.h"
#define MAX_ENEMIES 10
#define ROOM_WIDTH 100
#define ROOM_HEIGHT 100
#define enemyAmount 20
#define zombieAmount 10
using namespace std;


class Enemies{
    public:
        Enemies(){};

        virtual void draw() = 0; //Ritar ut fienden på spelplanen
        virtual void move(Vector3 position) = 0; //flyttar spelaren
        virtual vector<Vector3>& getAllPosList() = 0; //returnerar en lista med fienders positioner
        virtual void initRandomizePositions() = 0; //initerar fienden med random positioner
        virtual void randomizeXPositions(Vector3& enemyPos) = 0; //randomiserar x positionen för en fienden
        virtual int getActiveEnemies() = 0; //returnerar antalet aktiva fiender
        int checkCollision(Vector3 cubePos); //retunerar 1 vid kollision och 0 vid ingen kollision

        
};

void initilizeEnemies(Enemies* enemies, int amountOfEnemies, Vector3 playerPosition){
    for(int i = 0; i < amountOfEnemies; i++){
        enemies[i].initRandomizePositions();
    }

}

//zombie class for a single zombie
class zoomies : public Enemies{
    private:
        const char* modelPath = "models/zombiee.glb"; 
        Model zombieModel = LoadModel(modelPath);
        bool idleState = true;
        float speed; //should be random for every zombie
        Vector3 position; //initate position when created
        Vector3 direction; //initate direction when created
        void initRandomizePositions() override;
        void checkIfIdle(Vector3 playerPosition); //updates the idle state of the zombie
        void randomizeXPositions(Vector3& enemyPos) override;

    public:
        zoomies(Vector3 playerPosition){
            initRandomizePositions();
            speed = 0.1f;
        }
        void draw() override;
        void move(Vector3 position) override; //tar in spelarens position kollar även om den är idle
};

class Zombie : public Enemies{
    public:
        int amountOfZombies;
        vector<Vector3> zombiePosList;
        Vector3 zombieDirection;
        const char* zombieModelPath;
        Model zombieModel;
        int animCount;
        int frameCounter;
        ModelAnimation* animation;
        vector<bool> idleState;

        //bool animationsLoaded = true; //debugging
        
        Zombie(int zombies) : amountOfZombies(zombies), zombieModelPath("models/zombiee.glb"), zombieModel(LoadModel(zombieModelPath)){
            initRandomizePositions();
            animation = LoadModelAnimations(zombieModelPath, &animCount);
            for(int i = 0; i < amountOfZombies; i++){
                idleState.push_back(true);
            }
        };
        
        void draw() override;
        void move(Vector3 position) override; 
        virtual vector<Vector3>& getAllPosList()override;
        void initRandomizePositions() override;
        void randomizeXPositions(Vector3& enemyPos)override;
        int getActiveEnemies() override {
            return (int)zombiePosList.size();
        }
        
};   

//vanlig infanterist som rör sig frammåt