#ifndef SINGLE_BIT_DIPSWITCH_HPP
#define SINGLE_BIT_DIPSWITCH_HPP

#include <cstdint>
#include "../Dipswitch/Dipswitch.hpp"

class SingleBitDipswitch : public Dipswitch {
    public:
        SingleBitDipswitch(int bitIndex, bool switchValue);

        virtual uint8_t readByte(uint8_t portNumber, uint8_t accumulatorState) override;
};

#endif