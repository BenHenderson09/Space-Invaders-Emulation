#ifndef KEYPRESS_HANDLER_HPP
#define KEYPRESS_HANDLER_HPP

#include <chrono>
#include <Intel8080Emulator/Intel8080.hpp>
#include "../InteractiveDevices/InteractiveDevices.hpp"

class KeypressHandler : public Intel8080::ProcessorObserver {
    public:
        KeypressHandler(InteractiveDevices& interactiveDevices);

        virtual void notifyInstructionHasBeenExecuted() override;

    private:
        InteractiveDevices& interactiveDevices;
        std::chrono::time_point<std::chrono::steady_clock> timeWhenLastKeypressHandled;

        void handleKeypresses();
        void handleKeydown(const SDL_Keycode& key);
        void handleKeyup(const SDL_Keycode& key);
};

#endif