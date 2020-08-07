#ifndef DIPSWITCHES_HPP
#define DIPSWITCHES_HPP

#include "../SingleBitDipswitch/SingleBitDipswitch.hpp"
#include "../TwoBitDipswitch/TwoBitDipswitch.hpp"
#include "../../constants/DipswitchConstants.hpp"

struct Dipswitches {
    TwoBitDipswitch numberOfLivesSwitch {
        DipswitchConstants::numberOfLivesBitIndex,
        DipswitchConstants::numberOfLives
    };

    SingleBitDipswitch bonusLifeSwitch {
        DipswitchConstants::bonusLifeBitIndex,
        DipswitchConstants::isBonusLifeAtOneThousandPoints
    };

    SingleBitDipswitch coinInfoHiddenSwitch {
        DipswitchConstants::coinInfoHiddenBitIndex,
        DipswitchConstants::isCoinInfoHidden
    };
};

#endif