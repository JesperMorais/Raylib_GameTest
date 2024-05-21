#include "include/raylib.h"
#include <vector>
#define MAX_ENEMIES 10
#define ROOM_WIDTH 40
#define ROOM_HEIGHT 40
using namespace std;

class Enemy{
    public:
        Vector3 enemyPos;
        Enemy(){
            enemyPos = {0.0f, 0.0f, -5.0f};
        }
        void drawEnemy();
        void moveEnemy();
};