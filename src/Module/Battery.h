/*
* File: Battery
 * Author: Michael Franks
 * Description: Li-ion battery monitor
 */

#pragma once
#include "AnalogInput.h"
#include "hardware/gpio.h"

class Battery : public AnalogInput
{
public:
    explicit Battery(uint gpio_pin, uint vbus_pin = 24)
        : AnalogInput(gpio_pin), _vbus_pin(vbus_pin)
    {
        gpio_init(_vbus_pin);
        gpio_set_dir(_vbus_pin, GPIO_IN);
    }

    float voltage() const;
    float percentage() const;
    bool isUsbConnected() const;

private:
    uint _vbus_pin;

    static constexpr float V_MAX = 4.2f;
    static constexpr float V_MIN = 3.0f;
    static constexpr float DIVIDER_RATIO = 2.0f;
};
