/*
* File: Battery
 * Author: Michael Franks
 * Description: Li-ion battery monitor
 */

#include "Battery.h"

bool Battery::isUsbConnected() const
{
    return gpio_get(_vbus_pin); // GP24 = V_BUS sense on Pico W
}

float Battery::voltage() const
{
    return read_voltage() * DIVIDER_RATIO;
}

float Battery::percentage() const
{
    if (isUsbConnected()) return 100.0f;

    const float v = voltage();

    if (v >= V_MAX) return 100.0f;
    if (v <= V_MIN) return 0.0f;

    static constexpr float curve[][2] = {
        {4.20f, 100.0f},
        {4.10f, 90.0f},
        {4.00f, 80.0f},
        {3.90f, 70.0f},
        {3.80f, 60.0f},
        {3.70f, 50.0f},
        {3.60f, 35.0f},
        {3.50f, 20.0f},
        {3.40f, 10.0f},
        {3.30f, 5.0f},
        {3.00f, 0.0f},
    };

    constexpr int points = sizeof(curve) / sizeof(curve[0]);

    for (int i = 0; i < points - 1; i++)
    {
        if (v <= curve[i][0] && v >= curve[i + 1][0])
        {
            const float v_high = curve[i][0];
            const float v_low = curve[i + 1][0];
            const float p_high = curve[i][1];
            const float p_low = curve[i + 1][1];

            const float t = (v - v_low) / (v_high - v_low);
            return p_low + t * (p_high - p_low);
        }
    }

    return 0.0f;
}
