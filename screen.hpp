#pragma once
#include "handleMenu.hpp"
#include "session.hpp"
#include "handleEnemy.hpp"
#include "handleCamera.hpp"
#include "handlePlayer.hpp"
#include "handleObjektiv.hpp"
#include "raylib.h"

class Screen {
    public:
        virtual Screen* update(Session* sesh)  = 0; // Should update the screen with relevant info aswell as return the screen to process
        virtual void draw(Session* sesh) = 0;
};

class DriveScreen : public Screen{
    //Driving screen
    //Antal zombies
    //Spelare
    //Camera
    public:
        Camera camera;            // just data — the bus's chase cam
        Player player;
        EnemieManager enemies{3};   // braces, not parens, for in-class init
        managePickups mp;
        DriveScreen(){
            enemies.initEnemies();
            camera = initCamera3D();   // build it once when we enter the drive screen
        }
        void draw(Session* sesh) override;
        Screen* update(Session* sesh) override;
};

class EndDayScren : public Screen{
    // When day is over, we come here, upgrade rebuild etc.
    public:
        void draw(Session* sesh) override;
        Screen* update(Session* sesh) override;
        Rectangle returnButton; // return button
        Color returnColor;
        EndDayScren(){
            returnButton = {300,300,210,50};
            returnColor = PURPLE;
        }
};

class MenuScreen : public Screen{
    public:
    Menu menu;
    MenuScreen(){
        menu.initmenu();
    }
        void draw(Session* sesh) override;
        Screen* update(Session* sesh) override;
};