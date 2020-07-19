#ifndef KEYPRESS_HANDLER_HPP
#define KEYPRESS_HANDLER_HPP

#include <Intel8080Emulator/Intel8080.hpp>
#include <cstdint>
#include <chrono>
#include "../InteractiveDevices/InteractiveDevices.hpp"

class KeypressHandler : public Intel8080::ProcessorObserver {
    public:
        KeypressHandler(InteractiveDevices& interactiveDevices);

        virtual void notifyInstructionHasBeenExecuted(uint8_t opcode) override;

    private:
        InteractiveDevices& interactiveDevices;
        std::chrono::time_point<std::chrono::system_clock> timeWhenLastKeypressHandled;

        void handleKeypresses();
};

#endif