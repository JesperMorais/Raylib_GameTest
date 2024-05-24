#include "include/raylib.h"
#include <vector>
#include <iostream>
#include "include/raymath.h"
#include <corecrt.h>

class PowerUp{
    public:
        virtual void draw() = 0;
        virtual void move() = 0;
        virtual Vector3 getPosition() = 0;
        virtual void setPosition(Vector3 pos) = 0;

};


class HealthPowerUp : public PowerUp{
    public:
        Vector3 position;
        HealthPowerUp(){
            position = {0.0f, 0.0f, 0.0f};
        };

        void draw() override{
            DrawSphere(position, 1.0f, GRAY);
        }

        void move() override{
            position.y = 0.5f + 0.1f * sinf(2.0f * GetTime());
        }

        Vector3 getPosition() override{
            return position;
        }

        void setPosition(Vector3 pos) override{
            position = pos;
        }

        //follows the player if it moves to far
        void updateLine(Vector3 playerPos){
            if(playerPos.z - position.z > 10.0f){ //if player is more than 10 units away from powerup
                position.z = Lerp(playerPos.z - 10.0f, position.z, 0.02f);
                DrawLine3D(position, playerPos, RED);
            }
            else if(playerPos.z - position.z < -10.0f){ //if player is more than 10 units away from powerup
                position.z = Lerp(playerPos.z + 10.0f, position.z, 0.02f);
                DrawLine3D(position, playerPos, RED);
            }else{
                DrawLine3D(position, playerPos, BLACK);
            }

            if(playerPos.x - position.x > 10.0f){ //if player is more than 10 units away from powerup
                position.x = Lerp(playerPos.x - 10.0f, position.x, 0.02f);
                DrawLine3D(position, playerPos, RED);
            }
            else if(playerPos.x - position.x < -10.0f){ //if player is more than 10 units away from powerup
                position.x = Lerp(playerPos.x + 10.0f, position.x, 0.02f);
                DrawLine3D(position, playerPos, RED);
            }
            else{
                DrawLine3D(position, playerPos, BLACK);
            }
        }
};