#ifndef KEYPRESS_HANDLER_HPP
#define KEYPRESS_HANDLER_HPP

#include <Intel8080Emulator/Intel8080.hpp>
#include <cstdint>
#include "../CoinSlot/CoinSlot.hpp"

class KeypressHandler : public Intel8080::ProcessorObserver {
    public:
        KeypressHandler(CoinSlot& coinSlot);

        virtual void notifyInstructionHasBeenExecuted(uint8_t opcode) override;

    private:
        CoinSlot& coinSlot;
        const std::vector<char> singlePressKeys{'c'};

        void handleKeypresses();
        bool singlePressKeyIsBeingHeldDown(const SDL_Event& event) const;
};

#endif