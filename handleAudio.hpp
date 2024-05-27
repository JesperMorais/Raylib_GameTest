#pragma once

#include "include/raylib.h"
void playAudio(){
    
    if(IsAudioDeviceReady()){  
            static Wave wave = LoadWave("sounds/Jeppohoj.wav");
            static Sound sound = LoadSoundFromWave(wave);
            if(IsSoundPlaying(sound)){
            }
            else{
                PlaySound(sound);
            }
        }
}