#include <Intel8080Emulator/Intel8080.hpp>
#include "GraphicalDisplay/GraphicalDisplay.hpp"
#include "ShiftRegister/ShiftRegister.hpp"
#include "CoinSlot/CoinSlot.hpp"

int main(){
    Intel8080::Processor processor{"../rom/invaders"};
    
    ShiftRegister shiftRegister;
    CoinSlot coinSlot;

    GraphicalDisplay display{processor};
    display.openWindow();

    processor.attachObserver(display);
    processor.attachInputDevice(coinSlot);
    processor.attachInputDevice(shiftRegister);
    processor.attachOutputDevice(shiftRegister);
    processor.beginEmulation();
    
    return 0;
}