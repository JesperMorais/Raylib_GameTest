#include "handleObjektiv.hpp"

 
void schoolKids::draw(){ // ska rita ut enskild pickup
    DrawSphere(positon, 2.0f, PURPLE);
    //fixa model och annat skit
}

void schoolKids::move(Vector3 playerPosition){
    if(IsActive){
        positon.y = 10.0f;
        positon.x = playerPosition.x;
        positon.z = playerPosition.z;
    }
    else if(checkCollision(playerPosition)){
        positon.y = 10.0f;
        positon.x = playerPosition.x;
        positon.z = playerPosition.z;
    }
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

    if (CheckCollisionSpheres(playerPosition, scaleFactorX, positon, 1.0f) || //spelarens position, spelarens storlek, fiendens position, fiendens storlek
        CheckCollisionSpheres(playerPosition, scaleFactorY, positon, 1.0f) ||
        CheckCollisionSpheres(playerPosition, scaleFactorZ, positon, 1.0f)) {
        IsActive = true;
        return 1;      
    }  
    return 0;
}

void managePickups::updatePickups(Vector3 playerPos){
    for(auto& pickups : activePickups){
        pickups->draw();
        pickups->move(playerPos);
    }
};

void managePickups::spawnPickup(){
    activePickups.push_back(new schoolKids()); //körs en gång, ändras senare 
}

int managePickups::isAnyoneActive(){
    for(auto& pickups : activePickups){
        if(pickups->active())
            return 1;
    }
    return 0;
}
