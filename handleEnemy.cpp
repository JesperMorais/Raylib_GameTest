#include "handleEnemy.hpp"
using namespace std;

void Zoomies::draw(){
    DrawModel(zombieModel, position, 5.0f, WHITE);
}

void Zoomies::initRandomizePositions(){
        SetRandomSeed(GetRandomValue(0, 1000));
        float x = GetRandomValue(-ROOM_WIDTH, ROOM_WIDTH);
        float z = GetRandomValue(-ROOM_HEIGHT, ROOM_HEIGHT);
        position = {x, 0.0f, z};
}

void Zoomies::move(Vector3 playerPosition){

    if(playerPosition.x > position.x && playerPosition.z > position.z){ //Spelaren är till höger och framför
        position.z += 0.1f;
        position.x += 0.08f;
    }
    else if(playerPosition.x < position.x && playerPosition.z > position.z){ //Spelearen är till vänster och framför
        position.z += 0.1f;
        position.x -= 0.08f;
    }
    else if(playerPosition.x > position.x && playerPosition.z < position.z){ //Spelaren är till höger och bakom
        position.z -= 0.1f;
        position.x += 0.08f;
    }
    else if(playerPosition.x < position.x && playerPosition.z < position.z){ //Spelaren är till vänster och bakom
        position.z -= 0.1f;
        position.x -= 0.08f;
    }
}

void Zoomies::checkIfIdle(Vector3 playerPosition){
    if(playerPosition.x < position.x + 10.0f || playerPosition.x > position.x - 10.0f){ // kollar om spelare är i närheten
        idleState = false;
    }
    else if(playerPosition.z < position.z + 10.0f || playerPosition.z > position.z - 10.0f){ // kollar om spelare är i närheten
        idleState = false;
    }
    else{
        idleState = true;
    }
}

int Zoomies::checkCollisionWithPlayer(const Vector3 playerPosition, const Vector3 playerOrientation){ 
    float busWidth = 4.0f; // Example width
    float busHeight = 1.0f; // Example height
    float busLength = 8.0f; // Example length

    // Scale factors for the collision detection spheres
    float scaleFactorX = busWidth / 2.0f;
    float scaleFactorY = busHeight / 2.0f;
    float scaleFactorZ = busLength / 2.0f;
    // Check collision along each axis

    if (CheckCollisionSpheres(playerPosition, scaleFactorX, position, 1.0f) || //spelarens position, spelarens storlek, fiendens position, fiendens storlek
        CheckCollisionSpheres(playerPosition, scaleFactorY, position, 1.0f) ||
        CheckCollisionSpheres(playerPosition, scaleFactorZ, position, 1.0f)) {
        return 1;      
    }  
    return 0;
}

int Zoomies::ID = 0;

Zoomies::Zoomies(): speed(0.1f), id(++ID) { //constructor
    zombieModel = LoadModel(modelPath);
    initRandomizePositions();
}

void EnemieManager::initEnemies(){
    while((int)enemies.size() < maxEnemies){
        spawnEnemy();
    }
}  

void EnemieManager::spawnEnemy(){
    if((int)enemies.size() < maxEnemies){
        enemies.push_back(new Zoomies());
    }
}

void EnemieManager::updateEnemies(Vector3 playerPosition){
    for(auto& enemy : enemies){
        enemy->move(playerPosition);
        enemy->draw();
    }
}

int EnemieManager::checkCollision(Vector3 playerPosition, Vector3 playerOrientation){
        for (auto it = enemies.begin(); it != enemies.end(); ) {
            if ((*it)->checkCollisionWithPlayer(playerPosition, playerOrientation)) {
                int enemyID = (*it)->getID();
                delete *it;
                it = enemies.erase(it);
                cout << "Removed Enemy with ID: " << enemyID << endl;
                spawnEnemy();
                return 1;
            } else {
                ++it;
            }
        }
        return 0;
}


