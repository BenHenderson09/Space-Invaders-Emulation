#include <cstdint>
#include <Intel8080Emulator/Intel8080.hpp>
#include "CoinSlot.hpp"

CoinSlot::CoinSlot() : Intel8080::InputDevice{1}{};

// Alters first bit of port one. This specifies if a coin has been inserted.
uint8_t CoinSlot::readByte(uint8_t portNumber, uint8_t accumulatorState) {
    if (hasCoinBeenInserted){
        accumulatorState |= 1; // Set first bit

        static int numberOfReadsSinceCoinWasInserted{0};

        // Delay clearing the bit for a couple of reads to allow the processor
        // to handle the coin insertion.
        if (numberOfReadsSinceCoinWasInserted == 2){
            hasCoinBeenInserted = false;
            numberOfReadsSinceCoinWasInserted = 0;
        }

        numberOfReadsSinceCoinWasInserted++;
    }
    else {
        accumulatorState &= ~1; // Clear first bit
    }

    return accumulatorState;
}

void CoinSlot::insertCoin(){
    hasCoinBeenInserted = true;
}