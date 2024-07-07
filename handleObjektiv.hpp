#include "include/raylib.h"
#include <vector>
#include <iostream>
using namespace std;

//TODO: Pil till pickupen?
//TODO: Ge poäng till spelaren vid dropoff
//TODO: Random position till pickupen varje gång. 
//TODO: Modeller

class Pickups{
    public:
        virtual ~Pickups(){};
        inline virtual void drawPickup() = 0; //rita ut picupen
        inline virtual void drawDropoff() = 0; //rita ut dropoffen
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
        };
        Vector3 pickupPosition;
        Vector3 dropoffPosition;

        bool isPickupActive = false; //är true när den blivit upp plockat
        bool isDropoffActive = false; //är true när den e aktiv
        
        inline void drawPickup() override;
        inline void drawDropoff() override;

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
};