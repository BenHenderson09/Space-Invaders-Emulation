#include <cstdint>
#include "SingleBitDipswitch.hpp"

SingleBitDipswitch::SingleBitDipswitch(int bitIndex, bool switchValue)
    : Dipswitch{bitIndex, switchValue}{}

uint8_t SingleBitDipswitch::readByte(uint8_t portNumber, uint8_t accumulatorState) {
    // Clear the bit at the index, and then set this bit to the switch value
    accumulatorState = (accumulatorState & ~(1 << bitIndex)) | (switchValue << bitIndex);

    return accumulatorState;
}