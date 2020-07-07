#include <Intel8080Emulator/Intel8080.hpp>
#include "GraphicalDisplay/GraphicalDisplay.hpp"
#include "ShiftRegister/ShiftRegister.hpp"

int main(){
    Intel8080::Processor processor{"../rom/invaders"};
    
    GraphicalDisplay display{processor};
    display.openWindow();

    ShiftRegister shiftRegister;

    processor.attachObserver(display);
    processor.attachInputDevice(shiftRegister);
    processor.beginEmulation();
    
    return 0;
}