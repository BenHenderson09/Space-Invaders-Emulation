#ifndef DIPSWITCHES_HPP
#define DIPSWITCHES_HPP

#include "../SingleBitDipswitch/SingleBitDipswitch.hpp"
#include "../TwoBitDipswitch/TwoBitDipswitch.hpp"

struct Dipswitches {
    // 0 = 3 lives, 1 = 4 lives, 2 = 5 lives, 3 = 6 lives
    TwoBitDipswitch numberOfLives{0, 0};

    // Bonuse life will be provided at a certain score.
    // 0 = 1500 points, 1 = 1000 at points
    SingleBitDipswitch bonusLifeScore{0, 0}; // TODO test this

    // If set to false, then the instructions which specify how many
    // coins to insert will not be displayed.
    SingleBitDipswitch coinInfoHidden{7, false};
};

#endif