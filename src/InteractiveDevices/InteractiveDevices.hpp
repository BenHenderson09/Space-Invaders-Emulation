#ifndef INTERACTIVE_DEVICES_HPP
#define INTERACTIVE_DEVICES_HPP

#include "../InteractiveDevice/InteractiveDevice.hpp"

struct InteractiveDevices {
    InteractiveDevice coinSlot{1, 0};

    InteractiveDevice playerOneStartButton{1, 2};
    InteractiveDevice playerOneShootButton{1, 4};
    InteractiveDevice playerOneLeft{1, 5};
    InteractiveDevice playerOneRight{1, 6};
    
    InteractiveDevice playerTwoStartButton{1, 1};
    InteractiveDevice playerTwoShootButton{2, 4};
    InteractiveDevice playerTwoLeft{2, 5};
    InteractiveDevice playerTwoRight{2, 6};
};

#endif