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

void playCollisionSound(){
    if(IsAudioDeviceReady()){  
            static Wave wave = LoadWave("sounds/Sidechain_bip.3.wav");
            static Sound sound = LoadSoundFromWave(wave);
            PlaySound(sound);
        }
}

