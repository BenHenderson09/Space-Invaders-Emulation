#ifndef SOUND_CIRCUITRY_HPP
#define SOUND_CIRCUITRY_HPP

#include <cstdint>
#include <Intel8080Emulator/Intel8080.hpp>
#include <SDL2/SDL_mixer.h>
#include "../../config/SoundCircuitryConfig.hpp"

class SoundCircuitry : public Intel8080::OutputDevice {
    public:
        SoundCircuitry();

        virtual void writeByte(uint8_t portNumber, uint8_t byte) override;
    private:
        bool shotHasBeenFired{false};
        bool playerHasBeenShotByInvader{false};

        Mix_Chunk* firstFleetMovementSound
            {Mix_LoadWAV(SoundCircuitryConfig::firstFleetMovementPath.c_str())};

        Mix_Chunk* secondFleetMovementSound
            {Mix_LoadWAV(SoundCircuitryConfig::secondFleetMovementPath.c_str())};

        Mix_Chunk* thirdFleetMovementSound
            {Mix_LoadWAV(SoundCircuitryConfig::thirdFleetMovementPath.c_str())};
        
        Mix_Chunk* fourthFleetMovementSound
            {Mix_LoadWAV(SoundCircuitryConfig::fourthFleetMovementPath.c_str())};

        Mix_Chunk* invaderShotSound
            {Mix_LoadWAV(SoundCircuitryConfig::invaderShotPath.c_str())};

        Mix_Chunk* playerShotByInvaderSound
            {Mix_LoadWAV(SoundCircuitryConfig::playerShotByInvaderPath.c_str())};

        Mix_Chunk* playerShootingSound
            {Mix_LoadWAV(SoundCircuitryConfig::playerShootingPath.c_str())};

        Mix_Chunk* spaceshipFlyingSound
            {Mix_LoadWAV(SoundCircuitryConfig::spaceshipFlyingPath.c_str())};

        Mix_Chunk* spaceshipShotSound
            {Mix_LoadWAV(SoundCircuitryConfig::spaceshipShotPath.c_str())};

        void playSoundEffect(Mix_Chunk* sound);
        void playShootingSoundEffect();
        void playShotByInvaderSoundEffect();
};


#endif