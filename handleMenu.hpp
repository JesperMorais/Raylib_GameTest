#pragma once

#include "include/raylib.h"
#define __screenWidth 800
#define __screenHeight 600

class Menu{
    public:
        Menu(){
            initmenu();
        }

        bool showMenu;
        Rectangle startButton;
        Color buttonColor;
        Color buttonColorHover;
        Image image;
        Texture2D textureImage;
        int centerX;
        int centerY;
        void initmenu();
        void playMenu();
        bool getShowMenu(){return showMenu;};
};
