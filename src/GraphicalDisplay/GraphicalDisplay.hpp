#ifndef GRAPHICAL_DISPLAY_HPP
#define GRAPHICAL_DISPLAY_HPP

#include <cstdint>
#include <chrono>
#include <SDL2/SDL.h>
#include <Intel8080Emulator/Intel8080.hpp>

class GraphicalDisplay : public Intel8080::ProcessorObserver {
    public:
        GraphicalDisplay(Intel8080::Processor& processor);

        virtual void notifyInstructionHasBeenExecuted() override;
        void startVideoOutput();

    private:
        Intel8080::Processor& processor;
        bool hasVideoOutputStarted{false};

        // SDL objects for working with graphics
        SDL_Event event;
        SDL_Renderer *renderer;
        SDL_Window *window;

        // Timekeeping
        std::chrono::time_point<std::chrono::steady_clock> timeWhenPreviousInterruptWasSent;
        std::chrono::time_point<std::chrono::steady_clock> timeWhenPreviousFrameWasDrawn;
        int totalMicrosecondsBehindSchedule{0};

        // We use this to know when to send interrupts
        // to the processor and which interrupts to send
        uint16_t previousInterruptHandlerNumber;

        void openWindow();
        void drawFramesContinuously();
        void handleFrameDelay();
        void sleepUntilNextFrame(int microsecondsUntilNextFrame);
        int calculateMicrosecondsUntilNextFrame();
        int calculateFrameDelayInMicroseconds(int microsecondsUntilNextFrame);
        void handleFrameInterrupt();
        void sendWhicheverFrameInterruptIsDue();
        void drawFrame();
        void drawPixelWithRotation(int row, int col);
        bool isPixelColoured(int row, int col);
};

#endif