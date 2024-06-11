#include "handleGameloop.hpp"
#include "handleEnemy.hpp"
#include <string>

int main(){
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "COOL GAME"); 
    
    Menu menu; //initierar menyn
    InitAudioDevice();
    SetTargetFPS(60);   
 
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {   
            if(menu.getShowMenu()){ //kollar om vi ska vara inne i menyn eller inte
                menu.playMenu();
            }
            else{
                gameloop();
            } 
    }
    CloseWindow();
    CloseAudioDevice();
    return 0;
}

