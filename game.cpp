#include "game.hpp"

void Game::start(){
    while(this->running && !WindowShouldClose()){

        
        if(auto next = current->update(current_session.get())){
            current = std::move(next);
        }

        BeginDrawing();
        ClearBackground(WHITE);
        current->draw(current_session.get());
        EndDrawing();

    }
};