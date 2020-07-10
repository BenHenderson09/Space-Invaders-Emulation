#include <Intel8080Emulator/Intel8080.hpp>
#include "GraphicalDisplay/GraphicalDisplay.hpp"
#include "ShiftRegister/ShiftRegister.hpp"
#include "CoinSlot/CoinSlot.hpp"
#include "KeypressHandler/KeypressHandler.hpp"

int main(){
    Intel8080::Processor processor{"../rom/invaders"};
    
    GraphicalDisplay display{processor};
    CoinSlot coinSlot;
    ShiftRegister shiftRegister;

    display.openWindow();

    KeypressHandler keypressHandler{coinSlot};

    processor.attachObserver(keypressHandler);
    processor.attachObserver(display);
    processor.attachInputDevice(coinSlot);
    processor.attachInputDevice(shiftRegister);
    processor.attachOutputDevice(shiftRegister);
    processor.beginEmulation();
    
    return 0;
}