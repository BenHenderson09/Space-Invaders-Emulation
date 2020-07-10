#include <Intel8080Emulator/Intel8080.hpp>
#include "InteractiveDevices/InteractiveDevices.hpp"
#include "GraphicalDisplay/GraphicalDisplay.hpp"
#include "ShiftRegister/ShiftRegister.hpp"
#include "KeypressHandler/KeypressHandler.hpp"

int main(){
    // Hardware representations
    Intel8080::Processor processor{"../rom/invaders"};
    GraphicalDisplay display{processor};
    ShiftRegister shiftRegister;
    InteractiveDevices interactiveDevices;
  
    // Mapping keyboard inputs to the original controls
    KeypressHandler keypressHandler{interactiveDevices};

    // Linking the devices up to the processor
    processor.attachObserver(display);
    processor.attachObserver(keypressHandler);
    processor.attachInputDevice(shiftRegister);
    processor.attachOutputDevice(shiftRegister);
    processor.attachInputDevice(interactiveDevices.coinSlot);
    processor.attachInputDevice(interactiveDevices.playerOneStartButton);

    // Starting up the game
    display.openWindow();
    processor.beginEmulation();

    return 0;
}