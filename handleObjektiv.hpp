#include "include/raylib.h"
#include <vector>
#include <iostream>
using namespace std;

enum pickupState {
    READY_FOR_PICKUP,
    PICKED_UP,
};

class Pickups{
    public:
        virtual void draw() = 0; //rita ut picupen
        virtual void move(Vector3 PlayerPos) = 0;
        virtual int checkCollision(const Vector3 playerpos) = 0;
        virtual bool active() = 0; //kollar om pickupen är active
};

class schoolKids: public Pickups{
    public:
        schoolKids(){
            positon = {10.0f, 0.0f, 10.0f};
        };
        Vector3 positon;
        bool IsActive = false; //är true när den blivit upp plockat
        
        void draw() override;
        int checkCollision(const Vector3 PlayerPos) override;
        void setPosition(Vector3 PlayerPos);
        void move(Vector3 PlayerPos) override;
        bool active(){return IsActive;}; //returnar om det är active elelr ej

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
        
        int isAnyoneActive(); //kollar om någon pickup blivit upp plockad
};