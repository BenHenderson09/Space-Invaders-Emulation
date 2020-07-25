#include <string>
#include <SDL2/SDL_mixer.h>
#include <Intel8080Emulator/Intel8080.hpp>
#include "SoundCircuitry.hpp"

SoundCircuitry::SoundCircuitry() : Intel8080::OutputDevice{3, 5}{}

void SoundCircuitry::writeByte(uint8_t portNumber, uint8_t byte){
    if (portNumber == 3){
        //if (byte & 1) std::cout << "UFO flying\n";
        //if (byte & 0b10) playSoundEffect(playerShootingSound);
        //if (byte & 0b100) std::cout << "You died\n";
        //if (byte & 0b1000) std::cout << "Invader blows up\n";
    }
    else if (portNumber == 5){
        if (byte & 1) playSoundEffect(firstFleetMovementSound);
        if (byte & 0b10) playSoundEffect(secondFleetMovementSound);
        if (byte & 0b100) playSoundEffect(thirdFleetMovementSound);
        if (byte & 0b1000) playSoundEffect(fourthFleetMovementSound);
        //if (byte & 0b10000) std::cout << "UFO HIT\n";
    }
}

void SoundCircuitry::playSoundEffect(Mix_Chunk* sound) {
    Mix_PlayChannel(-1, sound, 0);
}
