#ifndef GraphicalDisplay_HPP
#define GraphicalDisplay_HPP

#include <SDL2/SDL.h>
#include <Intel8080Emulator/Intel8080.hpp>
#include "../../config/GraphicalDisplayConfig.hpp"

class GraphicalDisplay : public Intel8080::ProcessorObserver {
    public:
        GraphicalDisplay(Intel8080::Processor& processor);

        virtual void notifyInstructionHasBeenExecuted(uint8_t opcode) override;
        void startVideoOutput();

    private:
        Intel8080::Processor& processor;

        // SDL objects for working with graphics
        SDL_Event event;
        SDL_Renderer *renderer;
        SDL_Window *window;

        // We use this to know when to send interrupts to the processor and which interrupts to send
        int cyclesRanThisFrame{0};
        uint16_t lastExecutedInterruptAddress{GraphicalDisplayConfig::endOfFrameInterruptAddress};

        void drawFrame();
        void drawPixelWithRotation(int row, int col);
        bool isPixelColoured(int row, int col);
};

#endif