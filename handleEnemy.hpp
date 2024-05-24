#include "include/raylib.h"
#include <vector>
#include <iostream>
#include "include/raymath.h"
#define MAX_ENEMIES 10
#define ROOM_WIDTH 40
#define ROOM_HEIGHT 40
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

class infantry : public Enemies{
    public:
        int amountOfInfantry;
        vector<Vector3> infantryPosList;
        
        infantry(int amount): amountOfInfantry(amount){ 
            initRandomizePositions();
        }

        void draw() override;
        void move(Vector3 position) override; 
        virtual vector<Vector3>& getAllPosList()override;
        void initRandomizePositions() override;
        void randomizeXPositions(Vector3& enemyPos)override;
        int getActiveEnemies() override {
            return (int)infantryPosList.size();
        }

};


//Klass för fienden Zombie
//Den rör sig mot spelaren men efter den nått spelarens z led slutar den och åker rakt fram
class Zombie : public Enemies{
    public:
        int amountOfZombies;
        vector<Vector3> zombiePosList;

        Zombie(int zombies) : amountOfZombies(zombies){
            initRandomizePositions();

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