#ifndef DISPLAY_CONFIG
#define DISPLAY_CONFIG

#include <cstdint>

namespace DisplayConfig {
    const int windowWidth{224};
    const int windowHeight{256};
    const int cyclesPerFrame{4000};

    // Memory locations for reading video data and executing interrupts
    const uint16_t frameBufferAddress{0x2400};
    const uint16_t middleOfFrameInterruptAddress{0x8};
    const uint16_t endOfFrameInterruptAddress{0x10};
}

#endif