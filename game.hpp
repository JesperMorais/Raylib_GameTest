#pragma once
// Hold the game/assets class
#include <iostream>
#include "handlePlayer.hpp"
#include "handleObjektiv.hpp"
#include "state.hpp"
#include "screen.hpp"
#include "session.hpp"
#include <memory>

class Game{
    public:
    const int SCREENWIDTH = 800;
    const int SCREENHEIGHT = 600;
    bool running;
    std::unique_ptr<Screen> current = std::make_unique<MenuScreen>();
    std::unique_ptr<Session> current_session = std::make_unique<Session>();

    Game(){
        InitWindow(SCREENWIDTH, SCREENHEIGHT, "cool game<");
        InitAudioDevice();
        this->running = true;
        current_session->coins = 0;
        current_session->days = 1;
        std::cout << "Game init " << this->running << std::endl;
    }

    ~Game(){
        CloseWindow();
        CloseAudioDevice();
    }
    void start();
};