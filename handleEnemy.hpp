#include "include/raylib.h"
#include <vector>
#define MAX_ENEMIES 10
#define ROOM_WIDTH 40
#define ROOM_HEIGHT 40
#define enemyAmount 10 
using namespace std;

class Enemy{
    public:
        vector<Vector3> enemyPosList;

        Enemy(){
           for (int i = 0; i < enemyAmount; i++){
                float x = GetRandomValue(-ROOM_WIDTH / 2, ROOM_WIDTH / 2);
                float z = GetRandomValue(-ROOM_HEIGHT / 2, ROOM_HEIGHT / 2);
                enemyPosList.push_back({x, 0.0f, z});
            } 
        }

        void drawEnemy();
        void moveEnemy();
        
        vector<Vector3>& getEnemyPosList(){
            return enemyPosList;
            }
        
};