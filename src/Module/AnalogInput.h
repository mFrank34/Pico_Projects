/*
* File: AnalogInput
 * Author: Michael Franks
 * Description: Base class for analog input devices
 */

#pragma once
#include "hardware/adc.h"

class AnalogInput
{
public:
    explicit AnalogInput(uint gpio_pin);

    virtual ~AnalogInput() = default;

protected:
    uint pin;
    uint channel;

    float read_voltage() const;
    float read_percentage() const;
    int read_step(int range) const;

private:
    static constexpr float ADC_MAX = 4095.0f;
    static constexpr float VOLTAGE = 3.3f;
    static constexpr int SAMPLE_COUNT = 16;
};
