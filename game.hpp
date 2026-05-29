#pragma once
// Hold the game/assets class
#include "handlePlayer.hpp"
#include "handleCamera.hpp"
#include "handleEnemy.hpp"  
#include "handlePowerups.hpp"
#include "handleAudio.hpp"
#include "handleMenu.hpp"
#include "handleObjektiv.hpp"
#include <string>

class game:
    public:
    
    private:
        const char* mapModelPath = "models/map.glb";
