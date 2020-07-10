#ifndef COIN_SLOT_HPP
#define COIN_SLOT_HPP

#include <Intel8080Emulator/Intel8080.hpp>
#include <cstdint>

class CoinSlot : public Intel8080::InputDevice {
    public:
        CoinSlot();

        virtual uint8_t readByte(uint8_t portNumber, uint8_t accumulatorState) override;

        void insertCoin();

    private:
        bool hasCoinBeenInserted{false};
};

#endif