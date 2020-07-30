#include <cstdint>
#include <Intel8080Emulator/Intel8080.hpp>
#include "ShiftRegister.hpp"

ShiftRegister::ShiftRegister() : Intel8080::InputDevice{3}, Intel8080::OutputDevice{2, 4}{}

uint8_t ShiftRegister::readByte(uint8_t portNumber, uint8_t accumulatorState) {
    // Don't shift the specified number of bits out of range
    return valueHeldInRegister >> (8 - bitsToRemainUnshifted);
}

void ShiftRegister::writeByte(uint8_t portNumber, uint8_t byte){
    if (portNumber == 2){
        // This is a way to specify how many bits of the value in the register will be shifted
        // out of range, causing those bits to be deleted, when reading from port 3.
        // By default, the register value will be shifted 8 bits to the right,
        // but here we can set how many bits shouldn't get shifted out of range.
        bitsToRemainUnshifted = byte;
    }
    else if (portNumber == 4){
        // Shift the register 8 places right, replacing the low order byte.
        // The high order byte is then loaded with the new byte.
        valueHeldInRegister = (valueHeldInRegister >> 8) | (byte << 8);
    }
}