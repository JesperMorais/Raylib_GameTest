#include "handleEnemy.hpp"
using namespace std;

Model Zoomies::zombieModel = {};
bool Zoomies::isModelLoaded = false;

void Zoomies::loadZombieModel() {
       if (!isModelLoaded) {
            const char* modelPath = "models/zombiee.glb"; 
            zombieModel = LoadModel(modelPath);
            isModelLoaded = true;
    }
}

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

    Vector3 toPlayer = Vector3Subtract(playerPosition, position);
    float desiredYaw = atan2(toPlayer.x, toPlayer.z) * RAD2DEG;
    
    // Smoothly adjust orientation
    float turnSpeed = 4.0f;
    float lerpYaw = Lerp(orientation.y, desiredYaw, turnSpeed * GetFrameTime());
    orientation.y = lerpYaw;
    
    // Calculate movement direction based on orientation
    direction = { sin(DEG2RAD * orientation.y), 0, cos(DEG2RAD * orientation.y) };
    
    // Update position
    position.x += speed * direction.x;
    position.z += speed * direction.z;
    
    zombieModel.transform = MatrixRotateY(DEG2RAD * orientation.y);
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
    loadZombieModel(); //körs bara en gång
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


