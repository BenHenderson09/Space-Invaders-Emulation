#ifndef SOUND_CIRCUITRY_HPP
#define SOUND_CIRCUITRY_HPP

#include <cstdint>
#include <map>
#include <SDL2/SDL_mixer.h>
#include <Intel8080Emulator/Intel8080.hpp>
#include "../../constants/SoundCircuitryConstants.hpp"

class SoundCircuitry : public Intel8080::OutputDevice {
    public:
        SoundCircuitry();

        virtual void writeByte(uint8_t portNumber, uint8_t byte) override;
        
    private:
        uint8_t portThreePreviousByte;
        uint8_t portFivePreviousByte;

        Mix_Chunk* firstFleetMovementSound
            {Mix_LoadWAV(SoundCircuitryConstants::firstFleetMovementSoundPath.c_str())};

        Mix_Chunk* secondFleetMovementSound
            {Mix_LoadWAV(SoundCircuitryConstants::secondFleetMovementSoundPath.c_str())};

        Mix_Chunk* thirdFleetMovementSound
            {Mix_LoadWAV(SoundCircuitryConstants::thirdFleetMovementSoundPath.c_str())};
        
        Mix_Chunk* fourthFleetMovementSound
            {Mix_LoadWAV(SoundCircuitryConstants::fourthFleetMovementSoundPath.c_str())};

        Mix_Chunk* invaderShotSound
            {Mix_LoadWAV(SoundCircuitryConstants::invaderShotSoundPath.c_str())};

        Mix_Chunk* playerShotByInvaderSound
            {Mix_LoadWAV(SoundCircuitryConstants::playerShotByInvaderSoundPath.c_str())};

        Mix_Chunk* playerShootingSound
            {Mix_LoadWAV(SoundCircuitryConstants::playerShootingSoundPath.c_str())};

        Mix_Chunk* spaceshipFlyingSound
            {Mix_LoadWAV(SoundCircuitryConstants::spaceshipFlyingSoundPath.c_str())};

        Mix_Chunk* spaceshipShotSound
            {Mix_LoadWAV(SoundCircuitryConstants::spaceshipShotSoundPath.c_str())};

        std::map<Mix_Chunk*, int> portThreeSoundsMappedToBitIndexes {
            {spaceshipFlyingSound, SoundCircuitryConstants::bitIndexOfSpaceshipFlyingSound},
            {playerShootingSound, SoundCircuitryConstants::bitIndexOfPlayerShoootingSound},
            {playerShotByInvaderSound, SoundCircuitryConstants::bitIndexOfPlayerShotByInvaderSound},
            {invaderShotSound, SoundCircuitryConstants::bitIndexOfInvaderShotSound}
        };

        std::map<Mix_Chunk*, int> portFiveSoundsMappedToBitIndexes {
            {firstFleetMovementSound, SoundCircuitryConstants::bitIndexOfFirstFleetMovementSound},
            {secondFleetMovementSound, SoundCircuitryConstants::bitIndexOfSecondFleetMovementSound},
            {thirdFleetMovementSound, SoundCircuitryConstants::bitIndexOfThirdFleetMovementSound},
            {fourthFleetMovementSound, SoundCircuitryConstants::bitIndexOfFourthFleetMovementSound},
            {spaceshipShotSound, SoundCircuitryConstants::bitIndexOfSpaceshipShotSound}
        };

        std::map<Mix_Chunk*, int>& findMapOfSoundsAndBitIndexesForPortNumber(uint8_t portNumber);
        void handleSoundForBitOfPort
            (const std::pair<Mix_Chunk*, int>& soundWithBitIndex, uint8_t portNumber);
        uint8_t& findPreviousByteForPortNumber(uint8_t portNumber);
        bool isTheSpaceshipMakingSound(int bitIndex, uint8_t portNumber);
        void playSoundEffect(Mix_Chunk* sound);
        void updatePreviousByteOfPortNumber(uint8_t portNumber, uint8_t byte);
};


#endif