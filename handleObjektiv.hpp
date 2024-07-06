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
        virtual ~Pickups(){};
        virtual void drawPickup() = 0; //rita ut picupen
        virtual void drawDropoff() = 0; //rita ut dropoffen
        virtual void move(Vector3 PlayerPos) = 0; //rör på pickupem
        virtual int checkCollision(const Vector3 playerpos) = 0;
        virtual int checkCollisionDropoff(const Vector3 playerpos) = 0;
        virtual bool getIsPickupActive() = 0; //kollar om pickupen är active
        virtual bool getIsDropoffActive() = 0;
        virtual void setDropoffPosition(const Vector3 PlayerPos) = 0;
};

class schoolKids: public Pickups{
    public:
        ~schoolKids(){
        };
        schoolKids(){
            pickupPosition = {10.0f, 0.0f, 10.0f};
            dropoffPosition = {0.0f, 0.0f, -20.0f};
        };
        Vector3 pickupPosition;
        Vector3 dropoffPosition;

        bool isPickupActive = false; //är true när den blivit upp plockat
        bool isDropoffActive = false; //är true när den e aktiv
        
        void drawPickup() override;
        void drawDropoff() override;

        int checkCollision(const Vector3 PlayerPos) override;
        int checkCollisionDropoff(const Vector3 playerpos) override;

        void setDropoffPosition(const Vector3 PlayerPos);
        void move(Vector3 PlayerPos) override;
        
        bool getIsPickupActive(){return isPickupActive;}; //returnar om det är active elelr ej
        bool getIsDropoffActive(){return isDropoffActive;};

};

class managePickups{
    private:
        pickupState currentState;
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
        void spawnPickup();
        void updatePickups(Vector3 playerPosition);
        int getPickupSize(){
            return (int)activePickups.size();};
        
        int isAnyoneActive(); //kollar om någon pickup blivit upp plockad
        int isDropOffActive();
        void handleDropOff(); //Hanterar allt som ska ske vid en dropoff
};