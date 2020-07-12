#include <Intel8080Emulator/Intel8080.hpp>
#include "InteractiveDevices/InteractiveDevices.hpp"
#include "Dipswitches/Dipswitches.hpp"
#include "GraphicalDisplay/GraphicalDisplay.hpp"
#include "ShiftRegister/ShiftRegister.hpp"
#include "KeypressHandler/KeypressHandler.hpp"

int main(){
    // Hardware representations
    Intel8080::Processor processor{"../rom/invaders"};
    GraphicalDisplay display{processor};
    ShiftRegister shiftRegister;
    InteractiveDevices interactiveDevices;
    Dipswitches dipswitches;
  
    // Mapping keyboard inputs to the original controls
    KeypressHandler keypressHandler{interactiveDevices};

    // Linking the devices up to the processor
    processor.attachObserver(display);
    processor.attachObserver(keypressHandler);
    processor.attachInputDevice(shiftRegister);
    processor.attachOutputDevice(shiftRegister);
    processor.attachInputDevice(interactiveDevices.coinSlot);
    processor.attachInputDevice(interactiveDevices.playerOneStartButton);
    processor.attachInputDevice(interactiveDevices.playerOneShootButton);
    processor.attachInputDevice(interactiveDevices.playerOneLeft);
    processor.attachInputDevice(interactiveDevices.playerOneRight);
    processor.attachInputDevice(interactiveDevices.playerTwoStartButton);
    processor.attachInputDevice(interactiveDevices.playerTwoShootButton);
    processor.attachInputDevice(interactiveDevices.playerTwoLeft);
    processor.attachInputDevice(interactiveDevices.playerTwoRight);
    processor.attachInputDevice(dipswitches.coinInfoHidden);
    processor.attachInputDevice(dipswitches.numberOfLives);

    // Starting up the game
    display.openWindow();
    processor.beginEmulation();

    return 0;
}