#include <cstdint>
#include <Intel8080Emulator/Intel8080.hpp>
#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include "KeypressHandler.hpp"
#include "../InteractiveDevices/InteractiveDevices.hpp"

KeypressHandler::KeypressHandler(InteractiveDevices& interactiveDevices)
    : interactiveDevices{interactiveDevices}{}

void KeypressHandler::notifyInstructionHasBeenExecuted(uint8_t opcode){
    handleKeypresses();
}

void KeypressHandler::handleKeypresses(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // Prevent holding down keys
        if (singlePressKeyIsBeingHeldDown(event)) return;

        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym) {
                case 'c':  // Insert coin
                    interactiveDevices.coinSlot.insertCoin();
                    break;

                case 's':  // First player start button
                    interactiveDevices.playerOneStartButton.press();
                    break;
            }
        }
    }
}

bool KeypressHandler::singlePressKeyIsBeingHeldDown(const SDL_Event& event) const {
    SDL_Keycode key{event.key.keysym.sym};
    bool isKeyBeingHeldDown{event.type == SDL_KEYDOWN && event.key.repeat == 1};

    auto iteratorToSinglePressKey{std::find(singlePressKeys.begin(), singlePressKeys.end(), key)};
    bool isKeyOnlySinglePress{iteratorToSinglePressKey != singlePressKeys.end()};

    return isKeyBeingHeldDown && isKeyOnlySinglePress;
}