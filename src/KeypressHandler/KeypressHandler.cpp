#include <cstdint>
#include <chrono>
#include <vector>
#include <algorithm>
#include <Intel8080Emulator/Intel8080.hpp>
#include <SDL2/SDL.h>
#include "KeypressHandler.hpp"
#include "../InteractiveDevices/InteractiveDevices.hpp"

KeypressHandler::KeypressHandler(InteractiveDevices& interactiveDevices)
    : interactiveDevices{interactiveDevices}{}

void KeypressHandler::notifyInstructionHasBeenExecuted(){
    std::chrono::duration<double> elapsedTimeSinceKeypressHandledInSeconds {
        std::chrono::steady_clock::now() - timeWhenLastKeypressHandled
    };

    if (elapsedTimeSinceKeypressHandledInSeconds.count() > 0.01){
        handleKeypresses();
    }
}

void KeypressHandler::handleKeypresses(){
    SDL_Event event;
    timeWhenLastKeypressHandled = std::chrono::steady_clock::now();

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym) {
                case SDLK_c:
                    interactiveDevices.coinSlot.activate();
                    break;

                case SDLK_1:
                    interactiveDevices.playerOneStartButton.activate();
                    break;

                case SDLK_UP:
                    interactiveDevices.playerOneShootButton.activate();
                    break;

                case SDLK_RIGHT:
                    interactiveDevices.playerOneRight.activate();
                    break;

                case SDLK_LEFT:
                    interactiveDevices.playerOneLeft.activate();
                    break;

                case SDLK_2:
                    interactiveDevices.playerTwoStartButton.activate();
                    break;
                
                case SDLK_w:
                    interactiveDevices.playerTwoShootButton.activate();
                    break;

                case SDLK_d:
                    interactiveDevices.playerTwoRight.activate();
                    break;

                case SDLK_a:
                    interactiveDevices.playerTwoLeft.activate();
                    break;
            }
        }
        else if (event.type == SDL_KEYUP){
            switch (event.key.keysym.sym) {
                case SDLK_c:
                    interactiveDevices.coinSlot.deactivate();
                    break;

                case SDLK_1:
                    interactiveDevices.playerOneStartButton.deactivate();
                    break;

                case SDLK_UP:
                    interactiveDevices.playerOneShootButton.deactivate();
                    break;

                case SDLK_RIGHT:
                    interactiveDevices.playerOneRight.deactivate();
                    break;

                case SDLK_LEFT:
                    interactiveDevices.playerOneLeft.deactivate();
                    break;

                case SDLK_2:
                    interactiveDevices.playerTwoStartButton.deactivate();
                    break;
                
                case SDLK_w:
                    interactiveDevices.playerTwoShootButton.deactivate();
                    break;

                case SDLK_d:
                    interactiveDevices.playerTwoRight.deactivate();
                    break;

                case SDLK_a:
                    interactiveDevices.playerTwoLeft.deactivate();
                    break;
            }
        }
        else if (event.type == SDL_QUIT){
            std::exit(0);
        }
    }
}