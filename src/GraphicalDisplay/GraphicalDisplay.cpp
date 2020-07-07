#include <string>
#include <cstdint>
#include <SDL2/SDL.h>
#include <Intel8080Emulator/Intel8080.hpp>
#include "GraphicalDisplay.hpp"
#include "../../config/GraphicalDisplayConfig.hpp"

GraphicalDisplay::GraphicalDisplay(Intel8080::Processor& processor) : processor{processor}{};

void GraphicalDisplay::openWindow(){
    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(
        GraphicalDisplayConfig::windowWidth * GraphicalDisplayConfig::windowEnlargementFactor,
        GraphicalDisplayConfig::windowHeight * GraphicalDisplayConfig::windowEnlargementFactor,
        0,
        &window,
        &renderer
    );

    SDL_SetWindowTitle(window, GraphicalDisplayConfig::windowTitle.c_str());

    SDL_RenderSetScale(
        renderer,
        GraphicalDisplayConfig::windowEnlargementFactor,
        GraphicalDisplayConfig::windowEnlargementFactor
    );
}

void GraphicalDisplay::notifyInstructionHasBeenExecuted(uint8_t opcode){
    cyclesRanThisFrame += Intel8080::findNumberOfCyclesUsedByOpcode(opcode);

    if (cyclesRanThisFrame >= GraphicalDisplayConfig::cyclesPerFrame / 2){
        if (processor.areInterruptsEnabled()){
            if (lastExecutedInterruptAddress == GraphicalDisplayConfig::endOfFrameInterruptAddress){
                processor.interrupt(GraphicalDisplayConfig::middleOfFrameInterruptAddress);
                lastExecutedInterruptAddress = GraphicalDisplayConfig::middleOfFrameInterruptAddress;
            }
            else {
                processor.interrupt(GraphicalDisplayConfig::endOfFrameInterruptAddress);
                lastExecutedInterruptAddress = GraphicalDisplayConfig::endOfFrameInterruptAddress;
            }
        }

        cyclesRanThisFrame = 0;
    }

    if (cyclesRanThisFrame % 1000 == 0){
        drawFrame();
    }
}

void GraphicalDisplay::drawFrame(){
    for (int col{0}; col < GraphicalDisplayConfig::windowWidth; col++){
        for (int row{0}; row < GraphicalDisplayConfig::windowHeight; row++){
            drawPixelWithRotation(row, col);
        }
    }

    SDL_RenderPresent(renderer);
}

void GraphicalDisplay::drawPixelWithRotation(int row, int col){
    if (isPixelColoured(row, col)){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); // White
    }
    else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Black
    }

    // The framebuffer is rotated 90 degrees in memory, so undo that here.
    SDL_RenderDrawPoint(renderer, col, GraphicalDisplayConfig::windowHeight - row);
}

bool GraphicalDisplay::isPixelColoured(int row, int col){
    int bitsDrawn{(col * GraphicalDisplayConfig::windowHeight) + row};
    int bytesDrawn{bitsDrawn / 8};

    uint16_t addressOfByteBeingDrawn{uint16_t(GraphicalDisplayConfig::frameBufferAddress + bytesDrawn)};
    uint8_t byteBeingDrawn {processor.readByteFromMemory(addressOfByteBeingDrawn)};
    int bitsDrawnFromCurrentByte{bitsDrawn % 8};

    return byteBeingDrawn & (1 << bitsDrawnFromCurrentByte); // Extract value of next pixel
}
