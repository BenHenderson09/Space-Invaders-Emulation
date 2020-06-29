#include <Intel8080Emulator/Intel8080.hpp>
#include "GraphicalDisplay/GraphicalDisplay.hpp"

int main(){
    Intel8080::Processor processor{"../rom/invaders"};
    
    GraphicalDisplay display{processor};
    display.startVideoOutput();

    processor.attachObserver(display);
    processor.beginEmulation();

    return 0;
}