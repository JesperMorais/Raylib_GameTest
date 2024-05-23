#include "include/raylib.h"
#include "include/raymath.h"


//TODO: tilt camera when moving a specific direction
//fix larp when moving camera
void checkCameraMovment(Camera *camera, Vector3 *playerPosition){
    camera->target.x = Lerp(camera->target.x, playerPosition->x, 0.1f); //start, end , speed of lerp
    camera->target.y = Lerp(camera->target.y, playerPosition->y, 0.1f);
    camera->target.z = Lerp(camera->target.z, playerPosition->z, 0.1f);
    camera->position.x = Lerp(camera->position.x, playerPosition->x, 0.1f);
    camera->position.z = Lerp(camera->position.z, playerPosition->z + 12, 0.1f);
}
