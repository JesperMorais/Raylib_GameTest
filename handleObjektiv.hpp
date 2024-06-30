#include "include/raylib.h"
#include <vector>
#include <iostream>
using namespace std;

class Pickups{
    public:
        virtual void draw() = 0; //rita ut picupen
        virtual int checkCollision(const Vector3 playerpos) = 0;
};

class schoolKids: public Pickups{
    public:
        Vector3 positon;
        bool IsActive = false; //är true när den blivit upp plockat
        schoolKids(){
            positon = {10.0f, 0.0f, 10.0f};
        };
        
        void draw() override;
        int checkCollision(const Vector3 PlayerPos) override;
        void setPosition(Vector3 PlayerPos);

        bool getIsActive(){return IsActive;};

};

class managePickups{
    private:
        vector<Pickups*> activePickups;
    public:
        managePickups(){
            spawnPickup(); //initierar Pickups.
        };
        void spawnPickup();
        void updatePickups(Vector3 playerPosition);

    
        int getPickupSize(){
            return (int)activePickups.size();};
};