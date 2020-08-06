#include <SDL2/SDL_mixer.h>
#include <Intel8080Emulator/Intel8080.hpp>
#include "SoundCircuitry.hpp"

SoundCircuitry::SoundCircuitry() : Intel8080::OutputDevice{3, 5}{}

void SoundCircuitry::writeByte(uint8_t portNumber, uint8_t byte){
    if (portNumber == 3){
        for (const std::pair<Mix_Chunk*, int>& soundWithBitIndex : portThreeSoundsWithBitIndex){
            bool isBitAtIndexSet{byte & (1 << soundWithBitIndex.second)};
            bool isTheSpaceshipFlying{isBitAtIndexSet && soundWithBitIndex.second == 0};
            bool wasBitAtIndexSetPreviously{
                portThreePreviousByte & (1 << soundWithBitIndex.second)
            };

            if (isBitAtIndexSet && !wasBitAtIndexSetPreviously){
                playSoundEffect(soundWithBitIndex.first);
            }
            else if (isTheSpaceshipFlying){ // Spaceship has a repeating sound
                playSoundEffect(soundWithBitIndex.first);
            }
        }

        portThreePreviousByte = byte;
    }
    else if (portNumber == 5){
        for (const std::pair<Mix_Chunk*, int>& soundWithBitIndex : portFiveSoundsWithBitIndex){
            bool isBitAtIndexSet{byte & (1 << soundWithBitIndex.second)};
            bool wasBitAtIndexSetPreviously{portFivePreviousByte & (1 << soundWithBitIndex.second)};
            bool hasTheSpaceshipBeenShot{isBitAtIndexSet && soundWithBitIndex.second == 4};

            if (isBitAtIndexSet && !wasBitAtIndexSetPreviously){
                playSoundEffect(soundWithBitIndex.first);
            }
            else if (hasTheSpaceshipBeenShot){ // Spaceship has a repeating sound when shot also
                playSoundEffect(soundWithBitIndex.first);
            }
        }

        portFivePreviousByte = byte;
    }
}

void SoundCircuitry::playSoundEffect(Mix_Chunk* sound) {
    Mix_PlayChannel(-1, sound, 0);
}