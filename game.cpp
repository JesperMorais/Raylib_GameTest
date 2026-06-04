#include "game.hpp"

void Game::start(){
    while(this->running && !WindowShouldClose()){

        Screen* next = current->update(current_session);
        if(next != current){
            cout << "swapping! :)";
            // If we are on the wrong screen, swap
            swapScreens(next);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        current->draw();
        EndDrawing();

    }
};