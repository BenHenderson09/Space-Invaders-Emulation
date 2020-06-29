#include <Intel8080Emulator/Intel8080.hpp>
#include "Display/Display.hpp"

int main(){
    Intel8080::Processor processor{"../rom/invaders"};
    
    Display display{processor};
    display.startVideoOutput();

    processor.attachObserver(display);
    processor.beginEmulation();

    return 0;
}