#include <chrono>
#include <Intel8080Emulator/Intel8080.hpp>
#include <SDL2/SDL.h>
#include "KeypressHandler.hpp"
#include "../InteractiveDevices/InteractiveDevices.hpp"
#include "../../constants/KeypressHandlerConstants.hpp"

KeypressHandler::KeypressHandler(InteractiveDevices& interactiveDevices)
        : interactiveDevices{interactiveDevices}{
    timeWhenLastKeypressHandled = std::chrono::steady_clock::now();
}

void KeypressHandler::notifyInstructionHasBeenExecuted(){
    double elapsedTimeSinceKeypressHandledInSeconds {
        (std::chrono::steady_clock::now() - timeWhenLastKeypressHandled).count() / 1e9
    };

    bool isKeypressHandleDue {
        elapsedTimeSinceKeypressHandledInSeconds >
        KeypressHandlerConstants::delayBetweenKeypressHandlesInSeconds
    };

    if (isKeypressHandleDue){
        handleKeypresses();
    }
}

void KeypressHandler::handleKeypresses(){
    SDL_Event event;
    timeWhenLastKeypressHandled = std::chrono::steady_clock::now();

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN){
            handleKeydown(event.key.keysym.sym);
        }
        else if (event.type == SDL_KEYUP){
            handleKeyup(event.key.keysym.sym);
        }
        else if (event.type == SDL_QUIT){
            std::exit(0);
        }
    }
}

void KeypressHandler::handleKeydown(const SDL_Keycode& key){
    switch (key) {
        case SDLK_c: interactiveDevices.coinSlot.activate(); break;
        case SDLK_1: interactiveDevices.playerOneStartButton.activate(); break;
        case SDLK_UP: interactiveDevices.playerOneShootButton.activate(); break;
        case SDLK_RIGHT: interactiveDevices.playerOneRight.activate(); break;
        case SDLK_LEFT: interactiveDevices.playerOneLeft.activate(); break;
        case SDLK_2: interactiveDevices.playerTwoStartButton.activate(); break;
        case SDLK_w: interactiveDevices.playerTwoShootButton.activate(); break;
        case SDLK_d: interactiveDevices.playerTwoRight.activate(); break;
        case SDLK_a: interactiveDevices.playerTwoLeft.activate(); break;
    }
}

void KeypressHandler::handleKeyup(const SDL_Keycode& key){
    switch (key) {
        case SDLK_c: interactiveDevices.coinSlot.deactivate(); break;
        case SDLK_1: interactiveDevices.playerOneStartButton.deactivate(); break;
        case SDLK_UP: interactiveDevices.playerOneShootButton.deactivate(); break;
        case SDLK_RIGHT: interactiveDevices.playerOneRight.deactivate(); break;
        case SDLK_LEFT: interactiveDevices.playerOneLeft.deactivate(); break;
        case SDLK_2: interactiveDevices.playerTwoStartButton.deactivate(); break;
        case SDLK_w: interactiveDevices.playerTwoShootButton.deactivate(); break;
        case SDLK_d: interactiveDevices.playerTwoRight.deactivate(); break;
        case SDLK_a: interactiveDevices.playerTwoLeft.deactivate(); break;
    }
}