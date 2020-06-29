#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <SDL2/SDL.h>
#include <Intel8080Emulator/Intel8080.hpp>

class Display : public Intel8080::ProcessorObserver {
    public:
        Display(Intel8080::Processor& processor);

        virtual void notifyInstructionHasBeenExecuted(uint8_t opcode) override;

        void startVideoOutput();

    private:
        Intel8080::Processor& processor;

        // Configurations for video output
        const int windowWidth{224}, windowHeight{256}, cyclesPerFrame{4000};

        // SDL objects for working with graphics
        SDL_Event event;
        SDL_Renderer *renderer;
        SDL_Window *window;

        // We use this to know when to send interrupts to the processor
        int cyclesThisFrame{0};

        // Memory locations for reading video data and executing interrupts
        const uint16_t frameBufferAddress{0x2400};
        const uint16_t middleOfFrameInterruptAddress{0x8};
        const uint16_t endOfFrameInterruptAddress{0x10};
        uint16_t lastExecutedInterruptAddress{endOfFrameInterruptAddress};

        void drawFrame();
};

#endif