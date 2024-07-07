#include "handleObjektiv.hpp"

inline void schoolKids::drawPickup(){ // ska rita ut enskild pickup
    DrawSphere(pickupPosition, 2.0f, PURPLE);
    //fixa model och annat skit
}

inline void schoolKids::drawDropoff(){
    DrawSphere(dropoffPosition, 2.0f, GREEN);
    isDropoffActive = true;
    //fixa model å animation för dropoff
}

void schoolKids::move(Vector3 playerPosition){
    if(isPickupActive  || checkCollision(playerPosition)){ //är den redan aktiv eller kan bli aktiv så flyttar vi pickupen på spelaren
        pickupPosition.y = 10.0f;
        pickupPosition.x = playerPosition.x;
        pickupPosition.z = playerPosition.z;
    }
}

int schoolKids::checkCollisionDropoff(const Vector3 playerPosition){
    float busWidth = 4.0f; // Example width
    float busHeight = 1.0f; // Example height
    float busLength = 8.0f; // Example length

    // Scale factors for the collision detection spheres
    float scaleFactorX = busWidth / 2.0f;
    float scaleFactorY = busHeight / 2.0f;
    float scaleFactorZ = busLength / 2.0f;
    
    if(CheckCollisionSpheres(playerPosition, scaleFactorX, dropoffPosition, 1.0f) ||
        CheckCollisionSpheres(playerPosition, scaleFactorY, dropoffPosition, 1.0f) ||
        CheckCollisionSpheres(playerPosition, scaleFactorZ, dropoffPosition, 1.0f)){
            return 1;
    }
    return 0;
}

int schoolKids::checkCollision(const Vector3 playerPosition){ //kolla om enskild pickup kan bli upp plockad av spelaren
    float busWidth = 4.0f; // Example width
    float busHeight = 1.0f; // Example height
    float busLength = 8.0f; // Example length

    // Scale factors for the collision detection spheres
    float scaleFactorX = busWidth / 2.0f;
    float scaleFactorY = busHeight / 2.0f;
    float scaleFactorZ = busLength / 2.0f;
    // Check collision along each axis

    if (CheckCollisionSpheres(playerPosition, scaleFactorX, pickupPosition, 1.0f) || //spelarens position, spelarens storlek, fiendens position, fiendens storlek
        CheckCollisionSpheres(playerPosition, scaleFactorY, pickupPosition, 1.0f) ||
        CheckCollisionSpheres(playerPosition, scaleFactorZ, pickupPosition, 1.0f)) {
        isPickupActive = true;
        return 1;      
    }  
    return 0;
}

void schoolKids::setDropoffPosition(const Vector3 playerposition){
    if(isPickupActive && !isDropoffActive){ //om pickupen är aktiv och dropoffen inte är aktiv
        //sätt dropoffen till en random position
        float randomX = GetRandomValue((int)playerposition.x - 40,(int)playerposition.x + 40);
        float randomZ = GetRandomValue((int)playerposition.z - 40,(int)playerposition.z + 40);
        dropoffPosition = {randomX, 0.0f, randomZ};
    }

    //kan göra extra kollar så den inte spawnar på oss eller liknande
}

void managePickups::updatePickups(Vector3 playerPos){
    for(auto& pickups : activePickups){
        pickups->drawPickup();
        pickups->move(playerPos);
        
        if(pickups->getIsPickupActive()){ //om pickupen är aktiv
            pickups->setDropoffPosition(playerPos); //sätt dropoffen
            pickups->drawDropoff(); //rita ut dropoffen
            
            if(pickups->checkCollisionDropoff(playerPos)){ 
                activePickups.erase(activePickups.begin()); //tarbort pickupen
                spawnPickup(); //spawnar en ny pickup
            }
        }
    }
};

void managePickups::spawnPickup(){
    activePickups.push_back(new schoolKids()); //körs en gång, ändras senare 
}

int managePickups::isAnyoneActive(){
    for(auto& pickups : activePickups){
        if(pickups->getIsPickupActive())
            return 1;
    }
    return 0;
}

int managePickups::isDropOffActive(){
    for(auto& pickups : activePickups){
        if(pickups->getIsDropoffActive()){
            return 1;
        }
    }
    return 0;
}