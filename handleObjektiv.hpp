#pragma once
#include "raylib.h"
#include <vector>
#include <iostream>
using namespace std;

class Pickups{
    public:
        virtual void draw() = 0; //rita ut picupen
        virtual int checkCollision(const Vector3 playerpos) = 0;
        virtual void move(Vector3 PlayerPos) = 0;
};

class schoolKids: public Pickups{
    public:
        Vector3 positon;
        bool IsActive = false; //är true när den blivit upp plockat
        schoolKids(){
            positon = {5.0f, 0.0f, 5.0f};
        };
        void draw() override;
        int checkCollision(const Vector3 PlayerPos) override;
        void move(Vector3 PlayerPos) override;

        bool getIsActive(){return IsActive;};

        bool pickedUp = false;

};

class managePickups{
    private:
        vector<Pickups*> activePickups;
    public:
        managePickups(){
            spawnPickup(); //initierar Pickups.
        };
        void spawnPickup();
        void draw();
        void update(Vector3 playerpos);
        int getPickupSize(){return (int)activePickups.size();};
};