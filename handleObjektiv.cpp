#include "handleObjektiv.hpp"

 
void schoolKids::draw(){ // ska rita ut enskild pickup
    DrawSphere(positon, 2.0f, PURPLE);
    IsActive = true;
    //fixa model och annat skit
}

int schoolKids::checkCollision(const Vector3 PlayerPos){ //kolla om enskild pickup kan bli upp plockad av spelaren
    return 0;
}

void schoolKids::setPosition(Vector3 PlayerPos){
    if(pickedUp){
        positon.x = PlayerPos.x;
        positon.y = PlayerPos.x + 5.0f;
        positon.z = PlayerPos.z;
    }
}

void managePickups::updatePickups(Vector3 playerPos){
    for(auto& pickups : activePickups){
        pickups->draw();
    }
};

void managePickups::spawnPickup(){
    activePickups.push_back(new schoolKids()); //körs en gång, ändras senare 
}
