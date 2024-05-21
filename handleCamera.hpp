#include "include/raylib.h"

//TODO: tilt camera when moving a specific direction

void checkCameraMovment(Camera *camera, Vector3 *position){
    camera->target.x = position->x;
    camera->target.y = position->y;
    camera->target.z = position->z;
    camera->position.x = position->x/3;
}