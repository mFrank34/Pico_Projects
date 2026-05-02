/*
* File: AnalogInput
 * Author: Michael Franks
 * Description: Base class for analog input devices
 */

#include "AnalogInput.h"

AnalogInput::AnalogInput(uint gpio_pin)
    : pin(gpio_pin), channel(gpio_pin - 26)
{
    adc_init();
    adc_gpio_init(pin);
    if (channel > 2)
        channel = 0;
}

float AnalogInput::read_voltage() const
{
    adc_select_input(channel);
    float sum = 0.0f;
    for (int i = 0; i < SAMPLE_COUNT; i++)
        sum += adc_read();

    const float raw_avg = sum / SAMPLE_COUNT;
    return (raw_avg / ADC_MAX) * VOLTAGE;
}

float AnalogInput::read_percentage() const
{
    return (read_voltage() / VOLTAGE) * 100.0f;
}

int AnalogInput::read_step(int range) const
{
    if (range <= 0)
        return 0;

    const float normalized = read_voltage() / VOLTAGE;
    int step = static_cast<int>(normalized * (range - 1));

    if (step >= range)
        step = range - 1;
    return step;
}
