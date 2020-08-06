#ifndef DIPSWITCH_HPP
#define DIPSWITCH_HPP

#include <Intel8080Emulator/Intel8080.hpp>

class Dipswitch : public Intel8080::InputDevice {
    public:
        Dipswitch(int bitIndex, int switchValue);
        virtual ~Dipswitch() = 0;

    protected:
        const int bitIndex;
        const int switchValue;
};

#endif