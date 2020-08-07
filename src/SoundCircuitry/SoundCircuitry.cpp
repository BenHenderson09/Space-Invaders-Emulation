#include <SDL2/SDL_mixer.h>
#include <Intel8080Emulator/Intel8080.hpp>
#include "SoundCircuitry.hpp"

SoundCircuitry::SoundCircuitry() : Intel8080::OutputDevice{3, 5}{}

void SoundCircuitry::writeByte(uint8_t portNumber, uint8_t byte){
    std::map<Mix_Chunk*, int>& soundsMappedToBitIndexesForPort {
        findMapOfSoundsAndBitIndexesForPortNumber(portNumber)
    };

    for (const std::pair<Mix_Chunk*, int>& soundWithBitIndex : soundsMappedToBitIndexesForPort){
        bool isBitAtIndexSet{byte & (1 << soundWithBitIndex.second)};
        
        if (isBitAtIndexSet){
            handleSoundForBitOfPort(soundWithBitIndex, portNumber);
        }
    }

    updatePreviousByteOfPortNumber(portNumber, byte);
}

std::map<Mix_Chunk*, int>& SoundCircuitry::findMapOfSoundsAndBitIndexesForPortNumber
        (uint8_t portNumber){
    if (portNumber == 3){
        return portThreeSoundsMappedToBitIndexes;
    }
    else {
        return portFiveSoundsMappedToBitIndexes;
    }
}

void SoundCircuitry::handleSoundForBitOfPort
        (const std::pair<Mix_Chunk*, int>& soundWithBitIndex, uint8_t portNumber){
    uint8_t& previousByteOfPort{findPreviousByteForPortNumber(portNumber)};

    bool wasBitAtIndexSetPreviously {
        previousByteOfPort & (1 << soundWithBitIndex.second)
    };

    bool shouldSoundEffectBePlayed { // Only the spaceship can have a repeating sound.
        !wasBitAtIndexSetPreviously ||
        isTheSpaceshipMakingSound(soundWithBitIndex.second, portNumber)
    };

    if (shouldSoundEffectBePlayed){
        playSoundEffect(soundWithBitIndex.first);
    }
}

uint8_t& SoundCircuitry::findPreviousByteForPortNumber(uint8_t portNumber){
    if (portNumber == 3){
        return portThreePreviousByte;
    }
    else {
        return portFivePreviousByte;
    }
}


bool SoundCircuitry::isTheSpaceshipMakingSound(int bitIndex, uint8_t portNumber){
    int bitIndexOfSpaceshipSoundForPortNumber;

    if (portNumber == 3){
        bitIndexOfSpaceshipSoundForPortNumber =
            SoundCircuitryConstants::bitIndexOfSpaceshipFlyingSound;
    }
    else {
        bitIndexOfSpaceshipSoundForPortNumber = 
            SoundCircuitryConstants::bitIndexOfSpaceshipShotSound;
    }

    return bitIndex == bitIndexOfSpaceshipSoundForPortNumber;
}

void SoundCircuitry::playSoundEffect(Mix_Chunk* sound) {
    Mix_PlayChannel(-1, sound, 0);
}

void SoundCircuitry::updatePreviousByteOfPortNumber(uint8_t portNumber, uint8_t byte){
    findPreviousByteForPortNumber(portNumber) = byte;
}