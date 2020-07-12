#ifndef DIPSWITCHES_HPP
#define DIPSWITCHES_HPP

#include "../SingleBitDipswitch/SingleBitDipswitch.hpp"
#include "../TwoBitDipswitch/TwoBitDipswitch.hpp"

struct Dipswitches {
    SingleBitDipswitch coinInfoHidden{7, false};
    
    // 0 = 3 lives, 1 = 4 lives, 2 = 5 lives, 3 = 6 lives
    TwoBitDipswitch numberOfLives{0, 0};
};

#endif