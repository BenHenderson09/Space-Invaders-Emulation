#ifndef GRAPHICAL_DISPLAY_CONFIG
#define GRAPHICAL_DISPLAY_CONFIG

#include <cstdint>
#include <string>

namespace GraphicalDisplayConfig {
    const int windowWidth{224};
    const int windowHeight{256};
    const int windowEnlargementFactor{2};
    const std::string windowTitle{"Space Invaders"};
    const int cyclesPerFrame{20000};

    // Memory locations for reading video data and executing interrupts
    const uint16_t frameBufferAddress{0x2400};
    const uint16_t middleOfFrameInterruptAddress{0x8};
    const uint16_t endOfFrameInterruptAddress{0x10};
}

#endif