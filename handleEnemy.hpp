#include "include/raylib.h"
#include <vector>
#include <iostream>
#define MAX_ENEMIES 10
#define ROOM_WIDTH 40
#define ROOM_HEIGHT 40
#define enemyAmount 50
using namespace std;

struct enemie{
    Vector3 position;
    Vector3 speed;
    Color color;
};



class Enemies{
    public:
        vector<Vector3> enemyPosList;
        int currentEnemies;
        
        Enemies(){
            initRandomizePositions();
        }
        virtual void draw(); //virtual function
        virtual void move(Vector3 position); //virtual function
        void initRandomizePositions();
        void randomizePositions(Vector3& enemyPos);

        vector<Vector3>& getEnemyPosList(){
            return enemyPosList;
            }
        
};


class Zombie : public Enemies{
    public:
        void draw() override;
        void move(Vector3 position) override; 
};   