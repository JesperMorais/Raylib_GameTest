#include "handleObjektiv.hpp"

 
void schoolKids::draw(){ // ska rita ut enskild pickup
    DrawSphere(positon, 2.0f, PURPLE);
    IsActive = true;
    //fixa model och annat skit
}

int schoolKids::checkCollision(const Vector3 PlayerPos){ //kolla om enskild pickup kan bli upp plockad av spelaren
    float busWidth = 4.0f; // Example width
    float busHeight = 1.0f; // Example height
    float busLength = 8.0f; // Example length

    // Scale factors for the collision detection spheres
    float scaleFactorX = busWidth / 2.0f;
    float scaleFactorY = busHeight / 2.0f;
    float scaleFactorZ = busLength / 2.0f;
    if (CheckCollisionSpheres(PlayerPos, scaleFactorX,positon , 1.0f) || //spelarens position, spelarens storlek, fiendens position, fiendens storlek
        CheckCollisionSpheres(PlayerPos, scaleFactorY, positon, 1.0f) ||
        CheckCollisionSpheres(PlayerPos, scaleFactorZ, positon, 1.0f)) {
        pickedUp = true;
        return 1;      
    }  
    return 0;

}

void schoolKids::move(Vector3 PlayerPos){
    if(pickedUp){
        positon.x = PlayerPos.x;
        positon.y = PlayerPos.y + 5.0f;
        positon.z = PlayerPos.z;
    }
}

void managePickups::update(Vector3 playerPos){
    
    // check for dropoff etc
    for(auto& pickups : activePickups){
        pickups->checkCollision(playerPos);
        pickups->move(playerPos);
    }
}

void managePickups::draw(){
    for(auto& pickups : activePickups){
        pickups->draw();
    }
};

void managePickups::spawnPickup(){
    activePickups.push_back(new schoolKids()); //körs en gång, ändras senare 
}
