#ifndef DIPSWITCHES_HPP
#define DIPSWITCHES_HPP

#include "../SingleBitDipswitch/SingleBitDipswitch.hpp"
#include "../TwoBitDipswitch/TwoBitDipswitch.hpp"
#include "../../constants/DipswitchConstants.hpp"

struct Dipswitches {
    TwoBitDipswitch numberOfLives{0, DipswitchConstants::numberOfLives};
    SingleBitDipswitch bonusLifeScore{3, DipswitchConstants::isBonusLifeAtOneThousandPoints};
    SingleBitDipswitch coinInfoHidden{7, DipswitchConstants::isCoinInfoHidden};
};

#endif