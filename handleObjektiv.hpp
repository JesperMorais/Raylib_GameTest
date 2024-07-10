#include "include/raylib.h"
#include <vector>
#include <iostream>
using namespace std;

//TODO: Pil till pickupen?
//TODO: Ge poäng till spelaren vid dropoff
//TODO: Modeller

class Pickups{
    public:
        virtual ~Pickups(){};
        inline virtual void drawPickup() = 0; //rita ut picupen
        inline virtual void drawDropoff() = 0; //rita ut dropoffen
        virtual void move() = 0; //rör på pickupem
        virtual int checkCollision() = 0;
        virtual int checkCollisionDropoff() = 0;
        virtual bool getIsPickupActive() = 0; //kollar om pickupen är active
        virtual bool getIsDropoffActive() = 0;
        virtual void setDropoffPosition() = 0;
        inline virtual void setPlayerPosition(Vector3 pos) = 0;
};

class schoolKids: public Pickups{
    public:
        ~schoolKids(){
        };
        schoolKids(){
            float randomX = GetRandomValue((int)PP.x - 25,(int)PP.x + 25);
            float randomZ = GetRandomValue((int)PP.z - 25,(int)PP.z + 25);
            pickupPosition = {(float)randomX, 2.0f, randomZ};
        };
        Vector3 pickupPosition;
        Vector3 dropoffPosition;

        Vector3 PP; //playerPosition

        bool isPickupActive = false; //är true när den blivit upp plockat
        bool isDropoffActive = false; //är true när den e aktiv
        
        inline void drawPickup() override;
        inline void drawDropoff() override;

        int checkCollision() override;
        int checkCollisionDropoff() override;

        inline void setPlayerPosition(Vector3 pos){PP = pos;};
        void setDropoffPosition();
        void move() override;
        
        bool getIsPickupActive(){return isPickupActive;}; //returnar om det är active elelr ej
        bool getIsDropoffActive(){return isDropoffActive;};

};

class managePickups{
    private:
        vector<Pickups*> activePickups;
    public:
        managePickups(){
            spawnPickup(); //initierar Pickups.
        };
        ~managePickups(){
            for(auto& pickups : activePickups){
                delete pickups;
            }
        }
        void updatePlayerPos(Vector3 playerPos);
        void spawnPickup();
        void updatePickups();
        int getPickupSize(){
            return (int)activePickups.size();};
        
        int isAnyoneActive(); //kollar om någon pickup blivit upp plockad
        int isDropOffActive();
};