#include <Intel8080Emulator/Intel8080.hpp>
#include <SDL2/SDL.h>
#include "InteractiveDevices/InteractiveDevices.hpp"
#include "Dipswitches/Dipswitches.hpp"
#include "GraphicalDisplay/GraphicalDisplay.hpp"
#include "ShiftRegister/ShiftRegister.hpp"
#include "SoundCircuitry/SoundCircuitry.hpp"
#include "KeypressHandler/KeypressHandler.hpp"

int main(){
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    // Hardware representations
    Intel8080::Processor processor{"../rom/invaders"};
    GraphicalDisplay display{processor};
    ShiftRegister shiftRegister;
    SoundCircuitry soundCircuitry;
    InteractiveDevices interactiveDevices;
    Dipswitches dipswitches;
  
    // Mapping keyboard inputs to the original controls
    KeypressHandler keypressHandler{interactiveDevices};

    // Linking the devices up to the processor
    processor.attachObserver(display);
    processor.attachObserver(keypressHandler);
    processor.attachInputDevice(shiftRegister);
    processor.attachOutputDevice(shiftRegister);
    processor.attachOutputDevice(soundCircuitry);
    processor.attachInputDevice(interactiveDevices.coinSlot);
    processor.attachInputDevice(interactiveDevices.playerOneStartButton);
    processor.attachInputDevice(interactiveDevices.playerOneShootButton);
    processor.attachInputDevice(interactiveDevices.playerOneLeft);
    processor.attachInputDevice(interactiveDevices.playerOneRight);
    processor.attachInputDevice(interactiveDevices.playerTwoStartButton);
    processor.attachInputDevice(interactiveDevices.playerTwoShootButton);
    processor.attachInputDevice(interactiveDevices.playerTwoLeft);
    processor.attachInputDevice(interactiveDevices.playerTwoRight);
    processor.attachInputDevice(dipswitches.numberOfLivesSwitch);
    processor.attachInputDevice(dipswitches.bonusLifeSwitch);
    processor.attachInputDevice(dipswitches.coinInfoHiddenSwitch);

    // Starting up the game
    display.startVideoOutput();

    processor.beginEmulation();

    return 0;
}