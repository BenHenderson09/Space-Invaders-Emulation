#ifndef SHIFT_REGISTER
#define SHIFT_REGISTER

#include <cstdint>
#include <Intel8080Emulator/Intel8080.hpp>

// The shift register is a piece of external hardware in the Space Invaders arcade machine which is responsible
// for bitwise shifting. The 8080 can shift only by one bit at a time, but the shift register can shift many bits.
class ShiftRegister : public Intel8080::InputDevice, public Intel8080::OutputDevice {
    public:
        ShiftRegister();

        virtual uint8_t readByte(uint8_t portNumber) const override;
        virtual void writeByte(uint8_t portNumber, uint8_t byte) override;

    private:
        uint16_t valueHeldInRegister{0};
        int bitsToRemainUnshifted{0};
};

#endif