#ifndef INTERACTIVE_DEVICES_HPP
#define INTERACTIVE_DEVICES_HPP

#include "../InteractiveDevice/InteractiveDevice.hpp"
#include "../../constants/InteractiveDeviceConstants.hpp"

struct InteractiveDevices {
    InteractiveDevice coinSlot {
        InteractiveDeviceConstants::coinSlotPortNumber,
        InteractiveDeviceConstants::coinSlotBitIndex
    };

    InteractiveDevice playerOneStartButton {
        InteractiveDeviceConstants::playerOneStartButtonPortNumber,
        InteractiveDeviceConstants::playerOneStartButtonBitIndex
    };

    InteractiveDevice playerOneShootButton {
        InteractiveDeviceConstants::playerOneShootButtonPortNumber,
        InteractiveDeviceConstants::playerOneShootButtonBitIndex
    };

    InteractiveDevice playerOneLeft {
        InteractiveDeviceConstants::playerOneLeftPortNumber,
        InteractiveDeviceConstants::playerOneLeftBitIndex
    };

    InteractiveDevice playerOneRight {
        InteractiveDeviceConstants::playerOneRightPortNumber,
        InteractiveDeviceConstants::playerOneRightBitIndex
    };

    InteractiveDevice playerTwoStartButton {
        InteractiveDeviceConstants::playerTwoStartButtonPortNumber,
        InteractiveDeviceConstants::playerTwoStartButtonBitIndex
    };

    InteractiveDevice playerTwoShootButton {
        InteractiveDeviceConstants::playerTwoShootButtonPortNumber,
        InteractiveDeviceConstants::playerTwoShootButtonBitIndex
    };

    InteractiveDevice playerTwoLeft {
        InteractiveDeviceConstants::playerTwoLeftPortNumber,
        InteractiveDeviceConstants::playerTwoLeftBitIndex
    };

    InteractiveDevice playerTwoRight {
        InteractiveDeviceConstants::playerTwoRightPortNumber,
        InteractiveDeviceConstants::playerTwoRightBitIndex
    };
};

#endif