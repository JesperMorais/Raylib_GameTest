#pragma once
#include "handleMenu.hpp"
#include "session.hpp"
#include "handleEnemy.hpp"
#include "handleCamera.hpp"
#include "handlePlayer.hpp"
#include "raylib.h"

class Screen {
    
    public:
        virtual Screen* update(Session* sesh)  = 0; // Should update the screen with relevant info aswell as return the screen to process
        virtual void draw() = 0;
};

class DriveScreen : public Screen{
    //Driving screen
    //Antal zombies
    //Spelare
    //Camera
    public:
        const char* coinDraw = "2";
        Camera camera;            // just data — the bus's chase cam
        Player player;
        EnemieManager enemies{3};   // braces, not parens, for in-class init
        DriveScreen(){
            enemies.initEnemies();
            camera = initCamera3D();   // build it once when we enter the drive screen
        }
        void draw() override;
        Screen* update(Session* sesh) override;
};

class MenuScreen : public Screen{
    public:
    Menu menu;
    MenuScreen(){
        menu.initmenu();
    }
        void draw() override;
        Screen* update(Session* sesh) override;
};