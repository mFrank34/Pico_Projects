#include <iostream>

#include "hardware/adc.h"
#include "pico/stdlib.h"
#include "Module/ShiftRegister.h"
#include "Module/VariableResistor.h"

// Pin definitions (change if needed)
const uint DATA_PIN = 11; // DS
const uint CLOCK_PIN = 12; // SH_CP
const uint LATCH_PIN = 8; // ST_CP

const uint BUTTON = 14;

// Common Anode (LOW = ON)
const uint8_t digits[10] = {
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000 // 9
};


[[noreturn]] int main()
{
    stdio_init_all();
    adc_init();

    // Init pins
    gpio_init(DATA_PIN);
    gpio_set_dir(DATA_PIN, GPIO_OUT);

    gpio_init(CLOCK_PIN);
    gpio_set_dir(CLOCK_PIN, GPIO_OUT);

    gpio_init(LATCH_PIN);
    gpio_set_dir(LATCH_PIN, GPIO_OUT);

    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);

    gpio_put(DATA_PIN, 0);
    gpio_put(CLOCK_PIN, 0);
    gpio_put(LATCH_PIN, 0);

    ShiftRegister sr(DATA_PIN, CLOCK_PIN, LATCH_PIN);
    VariableResistor vr(26);

    while (true)
    {
        int index = vr.read_step(sizeof(digits));
        sleep_ms(100);
        sr.writeRegister(digits[index]);
        sleep_ms(100);

    }

}
