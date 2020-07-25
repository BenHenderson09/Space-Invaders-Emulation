#include <string>
#include <SDL2/SDL_mixer.h>
#include <Intel8080Emulator/Intel8080.hpp>
#include "SoundCircuitry.hpp"

SoundCircuitry::SoundCircuitry() : Intel8080::OutputDevice{3, 5}{}

void SoundCircuitry::writeByte(uint8_t portNumber, uint8_t byte){
    if (portNumber == 3){
        if (byte & 1) playSoundEffect(spaceshipFlyingSound);
        
        if (byte & 0b10){
            playShootingSoundEffect();
        }
        else {
            shotHasBeenFired = false;
        }

        if (byte & 0b100){
            playShotByInvaderSoundEffect();
        }
        else {
            playerHasBeenShotByInvader = false;
        }

        if (byte & 0b1000) playSoundEffect(invaderShotSound);
    }
    else if (portNumber == 5){
        if (byte & 1) playSoundEffect(firstFleetMovementSound);
        if (byte & 0b10) playSoundEffect(secondFleetMovementSound);
        if (byte & 0b100) playSoundEffect(thirdFleetMovementSound);
        if (byte & 0b1000) playSoundEffect(fourthFleetMovementSound);
        if (byte & 0b10000) playSoundEffect(spaceshipShotSound);
    }
}

void SoundCircuitry::playSoundEffect(Mix_Chunk* sound) {
    Mix_PlayChannel(-1, sound, 0);
}

void SoundCircuitry::playShootingSoundEffect(){
    if (!shotHasBeenFired){
        Mix_PlayChannel(-1, playerShootingSound, 0);
    }

    shotHasBeenFired = true;
}

void SoundCircuitry::playShotByInvaderSoundEffect(){
    if (!playerHasBeenShotByInvader){
        Mix_PlayChannel(-1, playerShotByInvaderSound, 0);
    }

    playerHasBeenShotByInvader = true;
}