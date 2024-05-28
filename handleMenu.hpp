#pragma once

#include "include/raylib.h"
#define __screenWidth 800
#define __screenHeight 600

class Menu{
    public:
        Menu(){
            initmenu();
        }
        bool showMenu; //håller koll på om menyn ska visas eller inte
        Rectangle startButton; //startknappen
        Color buttonColor; //färgen på knappen när musen inte är över
        Color buttonColorHover; //färgen på knappen när musen är över
        Image image; //bakgrundsbilden
        Texture2D textureImage; //bakgrundsbilden som en texture
        int centerX; //centrering av bilden
        int centerY; //centrering av bilden
        void initmenu(); 
        void playMenu();
        bool getShowMenu(){return showMenu;};
};
