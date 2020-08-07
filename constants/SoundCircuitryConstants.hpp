#ifndef SOUND_CIRCUITRY_CONSTANTS_HPP
#define SOUND_CIRCUITRY_CONSTANTS_HPP

#include <string>
#include <initializer_list>
#include <cstdint>

namespace SoundCircuitryConstants {
    // Port 3
    const int bitIndexOfSpaceshipFlyingSound{0};
    const int bitIndexOfPlayerShoootingSound{1};
    const int bitIndexOfPlayerShotByInvaderSound{2};
    const int bitIndexOfInvaderShotSound{3};

    // Port 5
    const int bitIndexOfFirstFleetMovementSound{0};
    const int bitIndexOfSecondFleetMovementSound{1};
    const int bitIndexOfThirdFleetMovementSound{2};
    const int bitIndexOfFourthFleetMovementSound{3};
    const int bitIndexOfSpaceshipShotSound{4};

    const std::string firstFleetMovementSoundPath{"../sound/first_fleet_movement.wav"};
    const std::string secondFleetMovementSoundPath{"../sound/second_fleet_movement.wav"};
    const std::string thirdFleetMovementSoundPath{"../sound/third_fleet_movement.wav"};
    const std::string fourthFleetMovementSoundPath{"../sound/fourth_fleet_movement.wav"};
    const std::string invaderShotSoundPath{"../sound/invader_shot.wav"};
    const std::string playerShotByInvaderSoundPath{"../sound/player_shot_by_invader.wav"};
    const std::string playerShootingSoundPath{"../sound/player_shooting.wav"};
    const std::string spaceshipFlyingSoundPath{"../sound/spaceship_flying.wav"};
    const std::string spaceshipShotSoundPath{"../sound/spaceship_shot.wav"};
}

#endif