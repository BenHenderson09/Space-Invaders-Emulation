#include <Intel8080Emulator/Intel8080.hpp>
#include "Dipswitch.hpp"
#include "../../constants/DipswitchConstants.hpp"

Dipswitch::Dipswitch(int bitIndex, int switchValue)
    : bitIndex{bitIndex}, switchValue{switchValue}, Intel8080::InputDevice{2} {}

Dipswitch::~Dipswitch(){}