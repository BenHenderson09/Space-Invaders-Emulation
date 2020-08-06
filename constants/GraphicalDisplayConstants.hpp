#ifndef GRAPHICAL_DISPLAY_CONSTANTS_HPP
#define GRAPHICAL_DISPLAY_CONSTANTS_HPP

#include <cstdint>
#include <string>

namespace GraphicalDisplayConstants {
    const int windowWidth{224};
    const int windowHeight{256};
    const int windowEnlargementFactor{2};
    const int framesPerSecond{60};
    const int interruptsPerSecond{120};
    const int middleOfFrameInterruptHandlerNumber{1};
    const int endOfFrameInterruptHandlerNumber{2};
    const std::string windowTitle{"Space Invaders"};
    const uint16_t frameBufferAddress{0x2400};
}

#endif