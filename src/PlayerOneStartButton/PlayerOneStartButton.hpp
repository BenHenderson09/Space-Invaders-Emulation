#ifndef PLAYER_ONE_START_BUTTON_HPP
#define PLAYER_ONE_START_BUTTON_HPP

#include <Intel8080Emulator/Intel8080.hpp>
#include <cstdint>

class PlayerOneStartButton : public Intel8080::InputDevice {
    public:
        PlayerOneStartButton();

        virtual uint8_t readByte(uint8_t portNumber, uint8_t accumulatorState) override;

        void press();

    private:
        bool pressed{false};
};

#endif