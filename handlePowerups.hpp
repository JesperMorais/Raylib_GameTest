#pragma once
#include "include/raylib.h"
#include <vector>
#include <iostream>
#include "include/raymath.h"
#include <corecrt.h>

//fixa collision check för powerups i player
//fixa så att powerups inte spawnar på samma position som fiender

class PowerUp{ //template for powerups
    public:
        virtual void draw() = 0;
        virtual void move(Vector3 playerPos) = 0;
        virtual Vector3 getPosition() = 0;
};


class HealthPowerUp : public PowerUp{
    public:
        Vector3 position;
        HealthPowerUp(){
            position = {0.0f, 0.0f, -40.0f};
        };

        void draw() override{
            DrawSphere(position, 1.0f, BLUE);

        }

        void move(Vector3 playerPos) override{
            position.y = 0.5f + 0.1f * sinf(5.0f * GetTime());
            position.z += 0.1f;
            
            if(position.z > playerPos.z + 20.0f){
                position.z = playerPos.z - 40.0f;   
            }
        }

        Vector3 getPosition() override{
            return position;
        }

        //follows the player if it moves to far
        void updateLine(Vector3 playerPos){ //draws line between player and powerup    
            DrawLine3D(position, playerPos, RED);
        }
};