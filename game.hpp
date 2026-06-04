#pragma once
// Hold the game/assets class
#include <iostream>
#include "handlePlayer.hpp"
#include "handleObjektiv.hpp"
#include "state.hpp"
#include "screen.hpp"
#include "session.hpp"

class Game{
    public:
    const int SCREENWIDTH = 800;
    const int SCREENHEIGHT = 600;
    bool running;
    Screen* current;
    Session* current_session = new Session;

    void swapScreens(Screen* next){
        delete current;
        current = next;
    }
    Game(){
        InitWindow(SCREENWIDTH, SCREENHEIGHT, "cool game<");
        InitAudioDevice();
        this->running = true;
        current_session->coins = 0;
        current_session->days = 1;
        current = new MenuScreen; // start at menu Screen
        std::cout << "Game init " << this->running << std::endl;
    }

    ~Game(){
        CloseWindow();
        CloseAudioDevice();
        delete current_session;
    }
    void start();
};