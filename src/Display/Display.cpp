#include <SDL2/SDL.h>
#include <Intel8080Emulator/Intel8080.hpp>
#include "Display.hpp"

Display::Display(Intel8080::Processor& processor) : processor{processor}{};

void Display::notifyInstructionHasBeenExecuted(uint8_t opcode){
    cyclesThisFrame += Intel8080::findNumberOfCyclesUsedByOpcode(opcode);

    if (cyclesThisFrame >= cyclesPerFrame / 2){
        if (processor.areInterruptsEnabled()){
            if (lastExecutedInterruptAddress == endOfFrameInterruptAddress){
                processor.interrupt(middleOfFrameInterruptAddress);
                lastExecutedInterruptAddress = middleOfFrameInterruptAddress;
            }
            else {
                processor.interrupt(endOfFrameInterruptAddress);
                lastExecutedInterruptAddress = endOfFrameInterruptAddress;
            }
        }

        cyclesThisFrame = 0;
    }

    if (cyclesThisFrame % 1000 == 0){
        drawFrame();
    }
}

void Display::drawFrame(){
    for (int col{0}; col < windowWidth; col++){
        for (int row{0}; row < windowHeight; row++){
            int bitsDrawn{(col * windowHeight) + row};
            int bytesDrawn{bitsDrawn / 8};
            int leftoverBitsDrawn{bitsDrawn % 8};

            if (processor.readByteFromMemory(frameBufferAddress+bytesDrawn) & (1 << leftoverBitsDrawn)){
                SDL_RenderDrawPoint(renderer, row, col);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void Display::startVideoOutput(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(windowWidth, windowWidth, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); // White
}