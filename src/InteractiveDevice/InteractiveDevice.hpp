#ifndef INTERACTIVE_DEVICE_HPP
#define INTERACTIVE_DEVICE_HPP

#include <Intel8080Emulator/Intel8080.hpp>
#include <cstdint>

class InteractiveDevice : public Intel8080::InputDevice {
    public:
        InteractiveDevice(uint8_t portNumber, int bitIndex);

        virtual uint8_t readByte(uint8_t portNumber, uint8_t accumulatorState) override;

        void activate();

    private:
        void deactivate();

        bool isActive{false};
        int numberOfReadsSinceActivated{0};
        int bitIndex;
};

#endif
