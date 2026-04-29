/*
 * File: ShiftRegister
 * Author: Michael Franks 
 * Description:
 */

#include "ShiftRegister.h"

ShiftRegister::ShiftRegister(const uint& DATA, const uint& CLOCK, const uint& LATCH)
    : DATA(DATA), CLOCK(CLOCK), LATCH(LATCH)
{
    gpio_put(DATA, 0);
    gpio_put(CLOCK, 0);
    gpio_put(LATCH, 0);

    init();
}

void ShiftRegister::shiftOut(const uint8_t& data)
{
    for (int i = 7; i >= 0; i--) // MSB first
    {
        gpio_put(CLOCK, 0);

        bool bit = (data >> i) & 1;
        gpio_put(DATA, bit);

        gpio_put(CLOCK, 1);
    }
}

void ShiftRegister::init()
{
    gpio_init(DATA);
    gpio_set_dir(DATA, GPIO_OUT);

    gpio_init(CLOCK);
    gpio_set_dir(CLOCK, GPIO_OUT);

    gpio_init(LATCH);
    gpio_set_dir(LATCH, GPIO_OUT);
}

void ShiftRegister::writeRegister(const uint8_t& data)
{
    gpio_put(LATCH, 0);
    shiftOut(data);
    gpio_put(LATCH, 1);
}
