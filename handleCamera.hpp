#pragma once
#include "raylib.h"   // gives us the Camera and Vector3 types
#include "raymath.h"  // gives us Lerp, DEG2RAD, and the math used below

// A raylib Camera is just DATA: position, target, up, fov. It isn't a smart
// object, so it doesn't need a class wrapping it. These two free helpers are
// all we need:
//   initCamera3D()      -> build a camera set up to look at the world
//   checkCameraMovment()-> each frame, slide the camera to chase the bus
Camera initCamera3D();
void checkCameraMovment(Camera *camera, Vector3 *playerPosition, Vector3 *playerOrientation);
