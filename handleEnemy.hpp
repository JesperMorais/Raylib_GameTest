#include "include/raylib.h"
#include <vector>
#include <iostream>
#define MAX_ENEMIES 10
#define ROOM_WIDTH 40
#define ROOM_HEIGHT 40
#define enemyAmount 10 
using namespace std;

class Enemy{
    public:
        vector<Vector3> enemyPosList;

        Enemy(){
            initRandomizePositions();
        }

        void drawEnemy();
        void moveEnemy();
        void initRandomizePositions();
        void randomizePositions(Vector3& enemyPos);

        vector<Vector3>& getEnemyPosList(){
            return enemyPosList;
            }
        
};