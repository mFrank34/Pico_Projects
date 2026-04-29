#include "VariableResistor.h"
#include "hardware/adc.h"

constexpr float ADC_MAX = 4095.0f;
constexpr float VOLTAGE = 3.3f;
constexpr int SAMPLE_COUNT = 16;

VariableResistor::VariableResistor(const uint gpio_pin)
    : pin(gpio_pin), channel(gpio_pin - 26)
{
    adc_gpio_init(pin);
    if (channel > 2)
        channel = 0;
}

float VariableResistor::read_voltage() const
{
    adc_select_input(channel);
    float sum = 0.0f;
    for (int i = 0; i < SAMPLE_COUNT; i++)
        sum += adc_read();

    const float raw_avg = sum / SAMPLE_COUNT;
    return (raw_avg / ADC_MAX) * VOLTAGE;
}

float VariableResistor::read_percentage() const
{
    return (read_voltage() / VOLTAGE) * 100.0f;
}

int VariableResistor::read_step(const int range) const
{
    if (range <= 0)
        return 0;

    const float voltage = read_voltage();
    const float normalized = voltage / VOLTAGE;
    int step = normalized * (range - 1);

    if (step >= range)
        step = range - 1;
    return step;
}
