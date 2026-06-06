#pragma once
#include "raylib.h"
#include <vector>
#include <iostream>
#include <ctime>
#include "handlePlayer.hpp"
#include "raymath.h"
#define ROOM_WIDTH 100
#define ROOM_HEIGHT 100
#define AMOUNT_ENEMIS 15

using namespace std;

enum ZombieAnimationType{
    IDLE = 0,
    WAVE = 1,
    WALK = 2,
    RUNATTACK = 3,
    RUN = 4,
    ATTACK = 6
};

class Enemies{
    public:
        Enemies(){};
        virtual ~Enemies(){};

        virtual void draw() = 0; //Ritar ut fienden på spelplanen
        virtual void move(Vector3 position) = 0; //flyttar spelaren
        virtual void initRandomizePositions() = 0; //initerar fienden med random positioner
        virtual int getID() = 0;
        virtual Vector3 getPosition() = 0;
};



//TODO: FIXA orienteringen på fienden så att den kollar åt rätt håll
//TODO: Fixa så att fienden inte kan gå igenom väggar eller varandra
//TODO: animationer.
class Zoomies : public Enemies{
    protected:
        static int ID; //id som delas mellan alla zombies
        static Model zombieModel; //gemensam modell för alla zombies
        static bool isModelLoaded; //kollar om modellen är laddad     
        //animations
        static int animCount; //antal animationer
        //static int animFrameCounter; //frame counter
        static ZombieAnimationType currentAnimation; //nuvarande animation        
        static ModelAnimation* anim; //lista av animationer
    
    private:
        static void loadZombieModel(); //laddar in modellen
        static int findAnim(const char* clipName); //hittar en animation via dess namn
        bool idleState = true;
        float speed; //should be random for every zombie
        unsigned int timeSinceAnimationChange = 0;

        Vector3 position; //initate position when created
        Vector3 direction; //initate direction when created
        Vector3 orientation; //initate orientation when created

        void initRandomizePositions() override; //gives random positions to the zombies only when they are created
        void checkIfIdle(Vector3 playerPosition); //updates the idle state of the zombie
        void updateAnimation(ZombieAnimationType animType); //updates the animation of the zombie
    public: 
        Vector3 getPosition(){return position;};
        int getID()override{return id;} //returnerar id för varje zombie
        int id; //unikt id för varje zombie
        Zoomies(); //constructor    
        void draw() override;
        void move(Vector3 position) override; //tar in spelarens position kollar även om den är idle
};

class EnemieManager{
    private:
        int timeSinceLastSpawn = 0;
        int spawnRate = 60;
        vector<Enemies*> enemies;
        int maxEnemies;
    public:
        EnemieManager(int inputEnemies): maxEnemies(inputEnemies){};
        ~EnemieManager(){ //tar bort fiender vid dekonstruktion så vi inte får någon memory leak
            for (auto enemy : enemies) {
                delete enemy;
            }
        }
    void setMaxEnemies(int amount){ maxEnemies = amount; } //sets the max amount of enemies
    int getMaxEnemies(){ return maxEnemies; } //returns the max amount of enemies
    void initEnemies(); //initiates enemies into the list
    void spawnEnemy(); //spawns a new enemy
    void moveEnemies(Vector3 playerPosition); //logic: moves every enemy toward the player
    void drawEnemies();                        //rendering: draws every enemy
    int checkCollision(Player player); //checks if the player collides with an enemy return 1 if true
    size_t getEnemiesSize(){return this->enemies.size();}; // todo add guardrails if enemies its not init yet
};

