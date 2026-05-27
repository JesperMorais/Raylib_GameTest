#pragma once

#include "raylib.h"
void playAudio(){
    
    if(IsAudioDeviceReady()){  
            static Wave wave = LoadWave("sounds/Jeppohoj.wav");
            if (wave.data == NULL){
                printf("Couldn't load audio\n");
                return;
            }
            static Sound sound = LoadSoundFromWave(wave);
            if(IsSoundPlaying(sound)){
            }
            else{
                PlaySound(sound);
            }
        }
}