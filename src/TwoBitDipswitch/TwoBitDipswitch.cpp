#include <cstdint>
#include "TwoBitDipswitch.hpp"

TwoBitDipswitch::TwoBitDipswitch(int bitIndex, int switchValue)
    : Dipswitch{bitIndex, switchValue}{}

uint8_t TwoBitDipswitch::readByte(uint8_t portNumber, uint8_t accumulatorState) {
    if (switchValue >= 0 && switchValue <= 3){
        bool firstBit{switchValue & 1};
        bool secondBit{switchValue & (1 << 1)};
        
        // Clear the bit at the index, and then set this bit to the switch value
        accumulatorState = (accumulatorState & ~(1 << bitIndex)) | (firstBit << bitIndex);
        accumulatorState = (accumulatorState & ~(1 << (bitIndex+1))) | (secondBit << (bitIndex+1));
    }
    else {
        throw std::out_of_range{"Two bit dipswitch value must have a range from 0 to 3."};
    }

    return accumulatorState;
}