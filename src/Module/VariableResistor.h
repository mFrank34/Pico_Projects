#ifndef VARIABLE_RESISTOR_H
#define VARIABLE_RESISTOR_H

#include "pico/types.h"

class VariableResistor
{
protected:
    uint pin;
    uint channel;

public:
    explicit VariableResistor(uint gpio_pin);

    float read_voltage() const;
    float read_percentage() const;
    int read_step(int range) const;
};

#endif //VARIABLE_RESISTOR_H
