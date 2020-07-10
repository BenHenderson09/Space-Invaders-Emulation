#include <Intel8080Emulator/Intel8080.hpp>
#include <cstdint>
#include "PlayerOneStartButton.hpp"

PlayerOneStartButton::PlayerOneStartButton(): InputDevice{1} {}

// Alters third bit of port one. This specifies if the button has been pressed.
uint8_t PlayerOneStartButton::readByte(uint8_t portNumber, uint8_t accumulatorState) {
    if (pressed){
        accumulatorState |= 0b100; // Set third bit
        pressed = false;
    }
    else {
        accumulatorState &= ~0b100; // Clear third bit
    }

    return accumulatorState;
}

void PlayerOneStartButton::press(){
    pressed = true;
}