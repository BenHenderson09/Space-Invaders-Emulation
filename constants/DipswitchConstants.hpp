#ifndef DIPSWITCH_CONSTANTS_HPP
#define DIPSWITCH_CONSTANTS_HPP

#include <cstdint>
#include <string>

namespace DipswitchConstants {
    const int numberOfLivesBitIndex{0};
    const int bonusLifeBitIndex{3};
    const int coinInfoHiddenBitIndex{7};

    // 0 = 3 lives, 1 = 4 lives, 2 = 5 lives, 3 = 6 lives
    const int numberOfLives{0};

    // If set to false, bonus life is at 1500 points
    const bool isBonusLifeAtOneThousandPoints{true};

    // If set to true, the instructions which specify how many coins to insert
    // will not be displayed.
    const bool isCoinInfoHidden{false};
}

#endif