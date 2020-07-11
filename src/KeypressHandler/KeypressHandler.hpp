#ifndef KEYPRESS_HANDLER_HPP
#define KEYPRESS_HANDLER_HPP

#include <Intel8080Emulator/Intel8080.hpp>
#include <cstdint>
#include "../InteractiveDevices/InteractiveDevices.hpp"

class KeypressHandler : public Intel8080::ProcessorObserver {
    public:
        KeypressHandler(InteractiveDevices& interactiveDevices);

        virtual void notifyInstructionHasBeenExecuted(uint8_t opcode) override;

    private:
        InteractiveDevices& interactiveDevices;
        const std::vector<SDL_KeyCode> singlePressKeys{SDLK_c, SDLK_1};

        void handleKeypresses();
        bool singlePressKeyIsBeingHeldDown(const SDL_Event& event) const;
};

#endif