#include "handleObjektiv.hpp"
#include "handlePlayer.hpp"
 
void schoolKids::draw(){ // ska rita ut enskild pickup
    DrawSphere(positon, 2.0f, PURPLE);
    
    if(IsActiveDrop == true){
        DrawSphere(dropPosition, 3.0f, BLACK);
    }
    //fixa model och annat skit
}

void schoolKids::move(Vector3 PlayerPos){
    if(pickedUp){
        positon.x = PlayerPos.x;
        positon.y = PlayerPos.y + 5.0f;
        positon.z = PlayerPos.z;
    }
}

void managePickups::update(Player* player){
    
    // check for dropoff etc
    for(auto& pickups : activePickups){
        // Check if we can ppickup the pickup
        pickups->move(player->position);

        if(player->checkCollision(pickups->positon) && pickups->pickedUp != true){
            pickups->pickedUp = true;
        }
        //check if drop can be pickuped up.
        if(pickups->pickedUp){
            if(player->checkCollision(pickups->dropPosition)){
                pickups->pickedUp = false;
                pickups->positon = {player->position.x +10,player->position.y, player->position.z + 10};
            }
        }
        if(pickups->pickedUp == true && pickups->getIsActiveDrop() == false){
            //spawn drop
            pickups->dropPosition = {pickups->positon.x + 4, pickups->positon.y, pickups->positon.z+4};
            pickups->IsActiveDrop = true;
        }
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
