#include "include/raylib.h"
#include "include/raymath.h"


//TODO: tilt camera when moving a specific direction
//fix larp when moving camera
void checkCameraMovment(Camera *camera, Vector3 *position){
    camera->target.x = Lerp(camera->target.x, position->x, 0.1f); //start, end , speed of lerp
    camera->target.y = Lerp(camera->target.y, position->y, 0.1f);
    camera->target.z = Lerp(camera->target.z, position->z, 0.1f);
    camera->position.x = Lerp(camera->position.x, position->x / 3, 0.1f);
}
