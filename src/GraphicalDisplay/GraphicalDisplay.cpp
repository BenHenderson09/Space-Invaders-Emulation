#include <stdexcept>
#include <cstdint>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>
#include <Intel8080Emulator/Intel8080.hpp>
#include "GraphicalDisplay.hpp"
#include "../../constants/GraphicalDisplayConstants.hpp"

GraphicalDisplay::GraphicalDisplay(Intel8080::Processor& processor) : processor{processor}{}

void GraphicalDisplay::startVideoOutput(){
    if (!hasVideoOutputStarted){
        openWindow();
        
        // Run in a separate detached thread
        std::thread(&GraphicalDisplay::drawFramesContinuously, this).detach();
        
        hasVideoOutputStarted = true;
    }
    else {
        throw std::runtime_error{"The graphical display window is already open."};
    }
}

void GraphicalDisplay::openWindow(){
    int width {
        GraphicalDisplayConstants::windowWidth * GraphicalDisplayConstants::windowEnlargementFactor
    };

    int height {
        GraphicalDisplayConstants::windowHeight * GraphicalDisplayConstants::windowEnlargementFactor
    };

    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetWindowTitle(window, GraphicalDisplayConstants::windowTitle.c_str());
    SDL_RenderSetScale(
        renderer,
        GraphicalDisplayConstants::windowEnlargementFactor,
        GraphicalDisplayConstants::windowEnlargementFactor
    );
}

void GraphicalDisplay::drawFramesContinuously(){
    double secondsPerFrame{1.0 / GraphicalDisplayConstants::framesPerSecond};
    int processingTimeToDeductInMicroseconds{0};

    timeWhenPreviousFrameWasDrawn = std::chrono::steady_clock::now();

    while (true) {
        std::chrono::duration<double> elapsedTimeSincePreviousFrameDrawnInSeconds {
            std::chrono::steady_clock::now() - timeWhenPreviousFrameWasDrawn
        };

        int timeDelayInMicroseconds { // Wait time necessary to reach the specified fps
            int((secondsPerFrame - elapsedTimeSincePreviousFrameDrawnInSeconds.count()) * 1e6)
        };

        handleFrameDelay(timeDelayInMicroseconds, processingTimeToDeductInMicroseconds);

        timeWhenPreviousFrameWasDrawn = std::chrono::steady_clock::now();
        drawFrame();
    }
}

void GraphicalDisplay::handleFrameDelay(int timeDelayInMicroseconds,
        int& processingTimeToDeductInMicroseconds){
    if (timeDelayInMicroseconds >= 0){
        int originalDelayInMicroseconds{timeDelayInMicroseconds};
        timeDelayInMicroseconds -= processingTimeToDeductInMicroseconds;

        if (timeDelayInMicroseconds < 0) timeDelayInMicroseconds = 0;

        processingTimeToDeductInMicroseconds -=
            originalDelayInMicroseconds - timeDelayInMicroseconds;

        std::this_thread::sleep_for (std::chrono::microseconds(timeDelayInMicroseconds));
    }
    else {
        // The time delay would be negative if the frame is getting drawn too slowly
        processingTimeToDeductInMicroseconds += -timeDelayInMicroseconds;
    }
}

void GraphicalDisplay::notifyInstructionHasBeenExecuted(){
    auto currentTime{std::chrono::steady_clock::now()};

    std::chrono::duration<double> elapsedTimeSincePreviousInterruptSentInSeconds {
        currentTime - timeWhenPreviousInterruptWasSent
    };

    // Alternate between two interrupts 120 times per
    // second, meaning each interrupt operates at 60Hz
    if (elapsedTimeSincePreviousInterruptSentInSeconds.count() >= 1.0 / GraphicalDisplayConstants::interruptsPerSecond){
        timeWhenPreviousInterruptWasSent = std::chrono::steady_clock::now();

        if (processor.areInterruptsEnabled()){
            bool wasLastInterruptForEndOfFrame {
                previousInterruptHandlerNumber ==
                GraphicalDisplayConstants::endOfFrameInterruptHandlerNumber
            };

            if (wasLastInterruptForEndOfFrame){
                processor.interrupt(GraphicalDisplayConstants::middleOfFrameInterruptHandlerNumber);
                previousInterruptHandlerNumber =
                    GraphicalDisplayConstants::middleOfFrameInterruptHandlerNumber;
            }
            else {
                processor.interrupt(GraphicalDisplayConstants::endOfFrameInterruptHandlerNumber);
                previousInterruptHandlerNumber =
                    GraphicalDisplayConstants::endOfFrameInterruptHandlerNumber;
            }
        }
    }
}

void GraphicalDisplay::drawFrame(){
    for (int col{0}; col < GraphicalDisplayConstants::windowWidth; col++){
        for (int row{0}; row < GraphicalDisplayConstants::windowHeight; row++){
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
    SDL_RenderDrawPoint(renderer, col, GraphicalDisplayConstants::windowHeight - row);
}

bool GraphicalDisplay::isPixelColoured(int row, int col){
    int numberOfBitsDrawn{(col * GraphicalDisplayConstants::windowHeight) + row};
    int numberOfBytesDrawn{numberOfBitsDrawn / 8};

    uint16_t addressOfByteBeingDrawn{static_cast<uint16_t>(
        GraphicalDisplayConstants::frameBufferAddress + numberOfBytesDrawn
    )};

    uint8_t byteBeingDrawn {processor.readByteFromMemory(addressOfByteBeingDrawn)};
    int bitsDrawnFromCurrentByte{numberOfBitsDrawn % 8};

    return byteBeingDrawn & (1 << bitsDrawnFromCurrentByte); // Extract value of next pixel
}
