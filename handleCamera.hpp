#include "include/raylib.h"

//TODO: tilt camera when moving a specific direction
//fix larp when moving camera
void checkCameraMovment(Camera *camera, Vector3 *position){
    // Lerp the camera's target position towards the player's position
    camera->target.x = Lerp(camera->target.x, position->x, 0.1f);
    camera->target.y = Lerp(camera->target.y, position->y, 0.1f);
    camera->target.z = Lerp(camera->target.z, position->z, 0.1f);

    // Lerp the camera's position towards the player's position divided by 3
    camera->position.x = Lerp(camera->position.x, position->x / 3, 0.1f);
}


    //camera->target.x = position->x;
    //camera->target.y = position->y;
   // camera->target.z = position->z;
    //camera->position.x = position->x/3;