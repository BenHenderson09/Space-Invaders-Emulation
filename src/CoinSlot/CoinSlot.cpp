#include <cstdint>
#include <Intel8080Emulator/Intel8080.hpp>
#include "CoinSlot.hpp"

CoinSlot::CoinSlot() : Intel8080::InputDevice{1}{};

uint8_t CoinSlot::readByte(uint8_t portNumber, uint8_t accumulatorState) {
    if (hasCoinBeenInserted){
        accumulatorState |= 1; // First bit of port one. Specifies if coin has been inserted.
        hasCoinBeenInserted = false;
    }

    return accumulatorState;
}

void CoinSlot::insertCoin(){
    hasCoinBeenInserted = true;
}