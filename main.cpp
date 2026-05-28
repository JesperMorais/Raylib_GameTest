#include "handleGameloop.hpp"
#include "handleEnemy.hpp"
#include "global.hpp"
#include <string>

int main(){
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "COOL GAME"); 
    Menu menu; //initierar menyn
    
    InitAudioDevice();
    SetTargetFPS(TARGETFPS);   
 
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

