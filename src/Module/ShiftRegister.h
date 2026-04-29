/*
 * File: ShiftRegister
 * Author: Michael Franks 
 * Description: shift register code.
 */

#ifndef SHIFT_REGISTER_H
#define SHIFT_REGISTER_H
#include "pico/stdlib.h"

class ShiftRegister
{
private:
    const uint& DATA;
    const uint& CLOCK;
    const uint& LATCH;

    void shiftOut(const uint8_t& data);
    void init();

public:
    ShiftRegister(const uint& DATA, const uint& CLOCK, const uint& LATCH);
    void writeRegister(const uint8_t& data);
};

#endif //SHIFT_REGISTER_H
