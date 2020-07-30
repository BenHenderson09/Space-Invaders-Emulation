#include <cstdint>
#include <Intel8080Emulator/Intel8080.hpp>
#include "InteractiveDevice.hpp"

InteractiveDevice::InteractiveDevice(uint8_t portNumber, int bitIndex)
    : Intel8080::InputDevice{portNumber}, bitIndex{bitIndex}{}

uint8_t InteractiveDevice::readByte(uint8_t portNumber, uint8_t accumulatorState) {
    if (isActive){
        accumulatorState |= 1 << bitIndex; // Set the bit of the port at the specified index
    }
    else {
        accumulatorState &= ~(1 << bitIndex); // Clear the bit of the port at the specified index
    }

    return accumulatorState;
}

void InteractiveDevice::activate(){
    isActive = true;
}

void InteractiveDevice::deactivate(){
    isActive = false;
}