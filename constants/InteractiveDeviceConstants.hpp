#ifndef INTERACTIVE_DEVICE_CONSTANTS_HPP
#define INTERACTIVE_DEVICE_CONSTANTS_HPP

#include <cstdint>
#include <string>

namespace InteractiveDeviceConstants {
    const uint8_t coinSlotPortNumber{1};
    const int coinSlotBitIndex{0};

    const uint8_t playerOneStartButtonPortNumber{1};
    const int playerOneStartButtonBitIndex{2};

    const uint8_t playerOneShootButtonPortNumber{1};
    const int playerOneShootButtonBitIndex{4};
    
    const uint8_t playerOneLeftPortNumber{1};
    const int playerOneLeftBitIndex{5};

    const uint8_t playerOneRightPortNumber{1};
    const int playerOneRightBitIndex{6};

    const uint8_t playerTwoStartButtonPortNumber{1};
    const int playerTwoStartButtonBitIndex{1};

    const uint8_t playerTwoShootButtonPortNumber{2};
    const int playerTwoShootButtonBitIndex{4};
    
    const uint8_t playerTwoLeftPortNumber{2};
    const int playerTwoLeftBitIndex{5};

    const uint8_t playerTwoRightPortNumber{2};
    const int playerTwoRightBitIndex{6};
}

#endif