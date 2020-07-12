#ifndef TWO_BIT_DIPSWITCH_HPP
#define TWO_BIT_DIPSWITCH_HPP

#include <cstdint>
#include "../Dipswitch/Dipswitch.hpp"

class TwoBitDipswitch : public Dipswitch {
    public:
        TwoBitDipswitch(int bitIndex, int switchValue);

        virtual uint8_t readByte(uint8_t portNumber, uint8_t accumulatorState) override;
};

#endif