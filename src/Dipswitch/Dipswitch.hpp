#ifndef DIPSWITCH_HPP
#define DIPSWITCH_HPP

#include <Intel8080Emulator/Intel8080.hpp>
#include <cstdint>

class Dipswitch : public Intel8080::InputDevice {
    public:
        Dipswitch(int bitIndex, int switchValue);
        virtual ~Dipswitch() = 0;

    protected:
        int switchValue;
        int bitIndex;
};

#endif