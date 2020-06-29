#include <SDL2/SDL.h>
#include <Intel8080Emulator/Intel8080.hpp>
#include "Display.hpp"
#include "../../config/DisplayConfig.hpp"

Display::Display(Intel8080::Processor& processor) : processor{processor}{};

void Display::notifyInstructionHasBeenExecuted(uint8_t opcode){
    cyclesRanThisFrame += Intel8080::findNumberOfCyclesUsedByOpcode(opcode);

    if (cyclesRanThisFrame >= DisplayConfig::cyclesPerFrame / 2){
        if (processor.areInterruptsEnabled()){
            if (lastExecutedInterruptAddress == DisplayConfig::endOfFrameInterruptAddress){
                processor.interrupt(DisplayConfig::middleOfFrameInterruptAddress);
                lastExecutedInterruptAddress = DisplayConfig::middleOfFrameInterruptAddress;
            }
            else {
                processor.interrupt(DisplayConfig::endOfFrameInterruptAddress);
                lastExecutedInterruptAddress = DisplayConfig::endOfFrameInterruptAddress;
            }
        }

        cyclesRanThisFrame = 0;
    }

    if (cyclesRanThisFrame % 1000 == 0){
        drawFrame();
    }
}

void Display::drawFrame(){
    for (int col{0}; col < DisplayConfig::windowWidth; col++){
        for (int row{0}; row < DisplayConfig::windowHeight; row++){
            int bitsDrawn{(col * DisplayConfig::windowHeight) + row};
            int bytesDrawn{bitsDrawn / 8};
            int leftoverBitsDrawn{bitsDrawn % 8};

            if (processor.readByteFromMemory(DisplayConfig::frameBufferAddress+bytesDrawn) & (1 << leftoverBitsDrawn)){
                SDL_RenderDrawPoint(renderer, row, col);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void Display::startVideoOutput(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(DisplayConfig::windowWidth, DisplayConfig::windowWidth, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); // White
}