#pragma once

Camera initCamera3D(){
    Camera camera = { 0 }; // Define the camera to look into our 3d world
    camera.position = { 0.0f, 16.0f, 12.0f };  
    camera.target = { 0.0f, 0.0f, 0.0f };    
    camera.up = { 0.0f, 10.0f, 0.0f };    
    camera.fovy = 60.0f;                               // Field-of-view Y  
    camera.projection = CAMERA_PERSPECTIVE;    
    return camera;
}

void checkCameraMovment(Camera *camera, Vector3 *playerPosition, Vector3 *playerOrientation){
       // Follow the player
    camera->target.x = Lerp(camera->target.x, playerPosition->x, 0.5f);
    camera->target.y = Lerp(camera->target.y, playerPosition->y, 0.5f);
    camera->target.z = Lerp(camera->target.z, playerPosition->z, 0.5f);

    // Calculate the direction vector based on player orientation
    Vector3 direction = { sin(DEG2RAD * playerOrientation->y), 0, cos(DEG2RAD * playerOrientation->y) };

    // Determine the distance from the player to the camera
    float distance = 30.0f; // Adjust this value as needed to set the desired distance

    // Set the camera's position to be behind the player, maintaining the specified distance
    camera->position.x = Lerp(camera->position.x, playerPosition->x + direction.x * distance, 0.5f);
    camera->position.z = Lerp(camera->position.z, playerPosition->z + direction.z * distance, 0.5f);
}
