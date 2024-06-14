#pragma once
#include "include/raylib.h"
#include <vector>
#include <iostream>
#include <ctime>
#include "include/raymath.h"
#define ROOM_WIDTH 100
#define ROOM_HEIGHT 100

using namespace std;


class Enemies{
    public:
        Enemies(){};
        virtual ~Enemies(){};

        virtual void draw() = 0; //Ritar ut fienden på spelplanen
        virtual void move(Vector3 position) = 0; //flyttar spelaren
        virtual void initRandomizePositions() = 0; //initerar fienden med random positioner
        virtual int checkCollisionWithPlayer(const Vector3 playerPosition, const Vector3 playetOrientation) = 0;
        virtual int getID() = 0;
};



//TODO: FIXA orienteringen på fienden så att den kollar åt rätt håll
//TODO: Fixa så att fienden inte kan gå igenom väggar eller varandra
//TODO: animationer.
class Zoomies : public Enemies{
    protected:
        static int ID; //id som delas mellan alla zombies
        static Model zombieModel; //gemensam modell för alla zombies
        static bool isModelLoaded; //kollar om modellen är laddad     
    
    private:
        static void loadZombieModel(); //laddar in modellen
        
        bool idleState = true;
        float speed; //should be random for every zombie

        Vector3 position; //initate position when created
        Vector3 direction; //initate direction when created

        void initRandomizePositions() override; //gives random positions to the zombies only when they are created
        void checkIfIdle(Vector3 playerPosition); //updates the idle state of the zombie

    public: 
        int getID()override{return id;} //returnerar id för varje zombie
        int id; //unikt id för varje zombie
        Zoomies(); //constructor    
        void draw() override;
        void move(Vector3 position) override; //tar in spelarens position kollar även om den är idle
        int checkCollisionWithPlayer(const Vector3 playerPosition, const Vector3 playetOrientation)override; //kollar om spelaren kolliderar med fienden  
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
    void initEnemies(); //initiates enemies into the list
    void spawnEnemy(); //spawns a new enemy
    void updateEnemies(Vector3 playerPosition); //moves and draws the enemies
    int checkCollision(Vector3 playerPosition, Vector3 playerOrientation); //checks if the player collides with an enemy return 1 if true
};

