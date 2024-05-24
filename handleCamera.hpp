#include "include/raylib.h"
#include "include/raymath.h"

Camera initCamera(){
    Camera camera = { 0 }; // Define the camera to look into our 3d world
    camera.position = { 0.0f, 5.0f, 12.0f };  
    camera.target = { 0.0f, 0.0f, 0.0f };    
    camera.up = { 0.0f, 1.0f, 0.0f };    
    camera.fovy = 70.0f;                               // Field-of-view Y  
    camera.projection = CAMERA_PERSPECTIVE;    
    return camera;
}

void checkCameraMovment(Camera *camera, Vector3 *playerPosition){
    camera->target.x = Lerp(camera->target.x, playerPosition->x, 0.1f); //start, end , speed of lerp
    camera->target.y = Lerp(camera->target.y, playerPosition->y, 0.1f);
    camera->target.z = Lerp(camera->target.z, playerPosition->z, 0.1f);
    camera->position.x = Lerp(camera->position.x, playerPosition->x, 0.1f);
    camera->position.z = Lerp(camera->position.z, playerPosition->z + 12, 0.1f);
}
