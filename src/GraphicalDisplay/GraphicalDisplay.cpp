#include <stdexcept>
#include <cstdint>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>
#include <Intel8080Emulator/Intel8080.hpp>
#include "GraphicalDisplay.hpp"
#include "../../constants/GraphicalDisplayConstants.hpp"

GraphicalDisplay::GraphicalDisplay(Intel8080::Processor& processor) : processor{processor}{
    timeWhenPreviousFrameWasDrawn = std::chrono::steady_clock::now();
    timeWhenPreviousInterruptWasSent = std::chrono::steady_clock::now();
}

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
    while (true) {
        timeWhenPreviousFrameWasDrawn = std::chrono::steady_clock::now();
        drawFrame();
        handleFrameDelay();
    }
}

void GraphicalDisplay::handleFrameDelay(){
    int microsecondsUntilNextFrame{calculateMicrosecondsUntilNextFrame()};
    bool areWeBehindScheduleThisFrame{microsecondsUntilNextFrame < 0};

    if (!areWeBehindScheduleThisFrame){
        sleepUntilNextFrame(microsecondsUntilNextFrame);
    }
    else {
        // If we are behind schedule, "microsecondsUntilNextFrame" will be negative.
        // Therefore, convert how far we're behind to a positive value and add this
        // to "totalMicrosecondsBehindSchedule"
        int microsecondsBehindScheduleThisFrame{-microsecondsUntilNextFrame};

        totalMicrosecondsBehindSchedule += microsecondsBehindScheduleThisFrame;
    }
}

void GraphicalDisplay::sleepUntilNextFrame(int microsecondsUntilNextFrame){
    int delayInMicroseconds{calculateFrameDelayInMicroseconds(microsecondsUntilNextFrame)};

    // i.e how many microseconds has the maximum delay been reduced by to account for being
    // behind schedule   
    int microsecondsBehindScheduleAccountedFor{microsecondsUntilNextFrame - delayInMicroseconds};

    totalMicrosecondsBehindSchedule -= microsecondsBehindScheduleAccountedFor;
    std::this_thread::sleep_for (std::chrono::microseconds(delayInMicroseconds));
}

int GraphicalDisplay::calculateMicrosecondsUntilNextFrame(){
    double secondsPerFrame{1.0 / GraphicalDisplayConstants::framesPerSecond};

    double elapsedTimeSincePreviousFrameDrawnInSeconds {
        (std::chrono::steady_clock::now() - timeWhenPreviousFrameWasDrawn).count() / 1e9
    };    

    double secondsUntilNextFrame {
        secondsPerFrame - elapsedTimeSincePreviousFrameDrawnInSeconds
    };

    return static_cast<int>(secondsUntilNextFrame * 1e6);
}

int GraphicalDisplay::calculateFrameDelayInMicroseconds(int microsecondsUntilNextFrame){
    // Reduce the delay to make up for how long we are behind schedule
    int delayInMicroseconds{microsecondsUntilNextFrame - totalMicrosecondsBehindSchedule};

    if (delayInMicroseconds < 0) delayInMicroseconds = 0; // Delay can't be negative

    return delayInMicroseconds;
}

void GraphicalDisplay::notifyInstructionHasBeenExecuted(){
    double elapsedTimeSincePreviousInterruptSentInSeconds {
        (std::chrono::steady_clock::now() - timeWhenPreviousInterruptWasSent).count() / 1e9
    };    

    double secondsPerInterrupt{1.0 / GraphicalDisplayConstants::interruptsPerSecond};

    bool isAnInterruptDue {
        elapsedTimeSincePreviousInterruptSentInSeconds >= secondsPerInterrupt
    };

    if (isAnInterruptDue){
        handleFrameInterrupt();
    }
}

void GraphicalDisplay::handleFrameInterrupt(){
    timeWhenPreviousInterruptWasSent = std::chrono::steady_clock::now();

    // Alternate between interrupts for the end and middle of the frame
    if (processor.areInterruptsEnabled()){ 
        sendWhicheverFrameInterruptIsDue();
    }
}

void GraphicalDisplay::sendWhicheverFrameInterruptIsDue(){
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
