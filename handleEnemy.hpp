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
        }

        void draw();
        void move();
        void initRandomizePositions();
        void randomizePositions(Vector3& enemyPos);

        vector<Vector3>& getEnemyPosList(){
            return enemyPosList;
            }
        
};