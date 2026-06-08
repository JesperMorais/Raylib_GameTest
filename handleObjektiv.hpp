#pragma once
#include "raylib.h"
#include <vector>
#include <iostream>
#include "handlePlayer.hpp"
using namespace std;

class Pickups{
    public:
        virtual void draw() = 0; //rita ut picupen
        virtual void move(Vector3 PlayerPos) = 0;
        bool getIsActiveDrop()const{return IsActiveDrop;};
        Vector3 positon;
        Vector3 dropPosition;
        bool IsActiveDrop = false;
        bool pickedUp = false;
};

class schoolKids: public Pickups{
    public:
        schoolKids(){
            positon = {5.0f, 0.0f, 5.0f};
        };
        void draw() override;
        void move(Vector3 PlayerPos) override;
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
        void update(Player* player);
        int getPickupSize(){return (int)activePickups.size();};
};