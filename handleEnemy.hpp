#include "include/raylib.h"
#include <vector>
#include <iostream>
#define MAX_ENEMIES 10
#define ROOM_WIDTH 40
#define ROOM_HEIGHT 40
#define enemyAmount 100
using namespace std;

class Enemies{
    public:
        vector<Vector3> enemyPosList;
        
        Enemies(){
            initRandomizePositions();
            } //konstruktor

        void draw(); //spawnar fiender
        void move(); //flyttar fiender och hanterar hur de respawnar
        void initRandomizePositions(); //initierar fiendernas positioner
        void randomizePositions(Vector3& enemyPos); //randomiserar fiendernas positioner när de respawnar

        vector<Vector3>& getEnemyPosList(){ return enemyPosList; }
        
};