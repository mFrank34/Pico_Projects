/*
* File: Motor
 * Author: Michael Franks
 * Description: Single DC motor control via TB6612FNG
 */

#include "Motor.h"

Motor::Motor(uint pwm_pin, uint in1_pin, uint in2_pin)
    : _pwm_pin(pwm_pin), _in1_pin(in1_pin), _in2_pin(in2_pin)
{
}

void Motor::begin()
{
    // Init direction pins
    gpio_init(_in1_pin);
    gpio_init(_in2_pin);
    gpio_set_dir(_in1_pin, GPIO_OUT);
    gpio_set_dir(_in2_pin, GPIO_OUT);

    // Init PWM pin
    gpio_set_function(_pwm_pin, GPIO_FUNC_PWM);
    _pwm_slice = pwm_gpio_to_slice_num(_pwm_pin);
    _pwm_channel = pwm_gpio_to_channel(_pwm_pin);

    pwm_set_wrap(_pwm_slice, PWM_WRAP);
    pwm_set_chan_level(_pwm_slice, _pwm_channel, 0);
    pwm_set_enabled(_pwm_slice, true);

    coast(); // start in safe state
}

void Motor::forward(float speed)
{
    gpio_put(_in1_pin, 1);
    gpio_put(_in2_pin, 0);
    setSpeed(speed);
}

void Motor::backward(float speed)
{
    gpio_put(_in1_pin, 0);
    gpio_put(_in2_pin, 1);
    setSpeed(speed);
}

void Motor::brake()
{
    gpio_put(_in1_pin, 1);
    gpio_put(_in2_pin, 1);
    setSpeed(0);
}

void Motor::coast()
{
    gpio_put(_in1_pin, 0);
    gpio_put(_in2_pin, 0);
    setSpeed(0);
}

void Motor::setSpeed(float speed)
{
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;
    pwm_set_chan_level(_pwm_slice, _pwm_channel, static_cast<uint>(speed * PWM_WRAP));
}
